/**
@file
@copyright $Copyright$
@version   $Revision$
@purpose   embeNET demo
@brief     Exemplary MQTT-SN client service
*/

#include "embenet/mqttsn_client.h"
#include "embenet/node.h"
#include "stm32wl3x_hal.h"
#include "stm32wl3x_nucleo.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>



// MQTT-SN Gateway port number
const uint16_t gatewayPortNo = 1885;
// MQTT-SN Client port number
const uint16_t clientPortNo = gatewayPortNo;

// How often a button press can be reported through MQTTSN
#define MQTTSN_BUTTON_DELAY_MS 1000

// Enumeration describing the state of the MQTT-SN service
enum mqttsnServiceState {
    // In the process of connecting
    CONNECTING = 0,
    // In the process of registering an uptime topic
    REGISTER_UPTIME_TOPIC,
    // In the process of registering a button state topic
    REGISTER_BUTTON_STATE_TOPIC,
    // In the process of subscribing to topic
    SUBSCRIBE_TO_TOPIC,
    // Normal state of operation
    RUNNING
} serviceState = CONNECTING;

// Descriptor of the MQTT-SN client
static MQTTSNClient mqttsnClient;
// MQTT-SN service task id
static EMBENET_TaskId mqttsnTaskId = EMBENET_TASKID_INVALID;
// This will be the MQTT topic that the client publishes to, pushing uptime information
static char uptimeTopic[MQTTSN_MAX_TOPIC_NAME_LENGTH];
// This will be the MQTT topic that the client publishes to, pushing button state information
static char buttonTopic[MQTTSN_MAX_TOPIC_NAME_LENGTH];
// This will be the MQTT topic that the client subscribes to, in order to receive control messages
static const char* ledControlTopic = "ledcontrol";

// Prototypes of event handlers
static void onMQTTConnected(MQTTSNClient* client);
static void onMQTTDisconnected(MQTTSNClient* client, MQTTSNClientDisconnectionReason disconnectionReason);

// Structure holding event handlers
const MQTTSNClientEventHandlers mqttEventHandlers = {
    .onConnected = onMQTTConnected,
    .onDisconnected = onMQTTDisconnected,
    .onTopicRegisteredByGateway = NULL
};


/**
 * This callback function is called when the MQTT-SN client connects to the gateway.
 *
 * @param[in] client MQTT-SN client descriptor
 *
 */
static void onMQTTConnected(MQTTSNClient* client) {
    printf("MQTT-SN: Connected to gateway\n\r");
    // Move to another state and reschedule the service task
    serviceState = REGISTER_UPTIME_TOPIC;
    EMBENET_NODE_TaskSchedule(mqttsnTaskId, EMBENET_NODE_TIME_SOURCE_LOCAL, EMBENET_NODE_GetLocalTime());
}


/**
 * This callback function is called when the MQTT-SN client disconnects from the gateway.
 * It tries to reconnect over and over again.
 *
 * @param[in] client MQTT-SN client descriptor
 * @param[in] disconnectionReason reason for the disconnection
 *
 */
static void onMQTTDisconnected(MQTTSNClient* client, MQTTSNClientDisconnectionReason disconnectionReason) {
	switch (disconnectionReason) {
	case MQTTSN_CLIENT_DISCONNECTED_DUE_TO_OWN_REQUEST:
	    printf("MQTT-SN: Client disconnected due to own request. Will try to reconnect in 5s\n\r");
		break;
	case MQTTSN_CLIENT_DISCONNECTED_BY_GATEWAY:
		printf("MQTT-SN: Client disconnected by gateway. Will try to reconnect in 5s\n\r");
	  break;
	case MQTTSN_CLIENT_DISCONNECTED_DUE_TO_TIMEOUT:
		printf("MQTT-SN: Client disconnected due to gateway communication timeout. Will try to reconnect in 5s\n\r");
		break;
	}
    // Cancel the service task
    EMBENET_NODE_TaskCancel(mqttsnTaskId);
    // Re-initialize the client
    MQTTSN_CLIENT_Deinit(&mqttsnClient);
    // Use the UID of the node as part of the client ID
    char          clientId[32];
    sprintf(clientId, "Client%x%08x", (unsigned)(EMBENET_NODE_GetUID()>>32), (unsigned)(EMBENET_NODE_GetUID()));
    MQTTSN_CLIENT_Init(&mqttsnClient, clientPortNo, clientId, &mqttEventHandlers);
    // Re-initialize and restart the service task
    serviceState = CONNECTING;
    EMBENET_NODE_TaskSchedule(mqttsnTaskId, EMBENET_NODE_TIME_SOURCE_LOCAL, EMBENET_NODE_GetLocalTime() + 5000);
}


/**
 * This callback function is called when a topic is registered in the gateway.
 *
 * @param[in] client MQTT-SN client descriptor
 * @param[in] topicId id of the registered topic
 * @param[in] topicName registered topic name (string)
 *
 */
static void onMQTTTopicRegistered(const struct MQTTSNClient* client, MQTTSNTopicId topicId, const char* topicName) {
    printf("MQTT-SN: Topic '%s' registered in gateway with id %d\n\r", topicName, (int)topicId);
    // Move to next state
    if (serviceState == REGISTER_UPTIME_TOPIC) {
        serviceState = REGISTER_BUTTON_STATE_TOPIC;
    } else {
        serviceState = SUBSCRIBE_TO_TOPIC;
    }
    // Reschedule immediately
    EMBENET_NODE_TaskSchedule(mqttsnTaskId, EMBENET_NODE_TIME_SOURCE_LOCAL, EMBENET_NODE_GetLocalTime());
}


/**
 * This callback function is called when the client successfully subscribes to a topic.
 *
 * @param[in] client MQTT-SN client descriptor
 * @param[in] topicId ID of the MQTT-SN topic
 * @param[in] topicName name of the topic (string)
 *
 */
static void onMQTTTopicSubscribed(const struct MQTTSNClient *client, MQTTSNTopicId topicId, char const *topicName) {
	printf("MQTT-SN: Subscribed to the '%s' topic\n\r", topicName);
	// Move to next state
	serviceState = RUNNING;
	// Reschedule immediately
	EMBENET_NODE_TaskSchedule(mqttsnTaskId, EMBENET_NODE_TIME_SOURCE_LOCAL, EMBENET_NODE_GetLocalTime());
}


/**
 * This callback function is called when message on the control topic is received.
 *
 * @param[in] client MQTT-SN client descriptor
 * @param[in] topicId ID of the MQTT-SN topic
 * @param[in] data message data
 * @param[in] dataSize message data size
 *
 */
static void onLedcontrolUpdate(struct MQTTSNClient* client, MQTTSNTopicId topicId, const void* data, size_t dataSize) {
    char* msg = (char*)data;

    printf("MQTT-SN: Got message on control topic: %s\n\r", msg);

    if (0 == strncmp(msg, "led1on", 6)) {
        printf("MQTT-SN: Led 1 on\n\r");
        BSP_LED_On(LED_RED);
    } else if (0 == strncmp(msg, "led1off", 7)) {
    	printf("MQTT-SN: Led 1 off\n\r");
        BSP_LED_Off(LED_RED);
    } else if (0 == strncmp(msg, "led2on", 6)) {
    	printf("MQTT-SN: Led 2 on\n\r");
        BSP_LED_On(LED_GREEN);
    } else if (0 == strncmp(msg, "led2off", 7)) {
    	printf("MQTT-SN: Led 2 off\n\r");
        BSP_LED_Off(LED_GREEN);
    } else if (0 == strncmp(msg, "led3on", 6)) {
    	printf("MQTT-SN: Led 3 on\n\r");
        BSP_LED_On(LED_BLUE);
    } else if (0 == strncmp(msg, "led3off", 7)) {
    	printf("MQTT-SN: Led 3 off\n\r");
        BSP_LED_Off(LED_BLUE);
    } else {
    	printf("MQTT-SN: Unknown command, ignoring\n\r");
    }
}


/**
 * Implementation of a service task, using a state machine.
 *
 * @param[in] taskId id of the embeNET Node task
 * @param[in] timeSource clock over which the task was scheduled
 * @param[in] t time at which the task was scheduled to run
 * @param[in] context user defined context
 */
static void mqttsnServiceTask(EMBENET_TaskId taskId, EMBENET_NODE_TimeSource timeSource, uint64_t t, void *context) {
    switch (serviceState) {
        case CONNECTING:
        	printf("MQTT-SN: Connecting to gateway\n\r");
            // Get border router address. We assume that the MQTT-SN gateway runs on the border router IP.
            EMBENET_IPV6 addr;
            EMBENET_NODE_GetBorderRouterAddress(&addr);
            // Perform a clean connect - you can tweak the timings here
            MQTTSN_CLIENT_Connect(&mqttsnClient, &addr, gatewayPortNo, 30000, 5000, NULL, NULL, 2);
            // Reschedule the task to try again after 10s if failed to connect
            EMBENET_NODE_TaskSchedule(mqttsnTaskId, timeSource, t + 10000);
            break;
        case REGISTER_UPTIME_TOPIC:
        	printf("MQTT-SN: Registering uptime topic\n\r");
            MQTTSN_CLIENT_RegisterTopic(&mqttsnClient, uptimeTopic, onMQTTTopicRegistered);
            break;
        case REGISTER_BUTTON_STATE_TOPIC:
        	printf("MQTT-SN: Registering button state topic\n\r");
            MQTTSN_CLIENT_RegisterTopic(&mqttsnClient, buttonTopic, onMQTTTopicRegistered);
            // Reschedule the task to try again after 5s if acknowledgment is not received
            EMBENET_NODE_TaskSchedule(mqttsnTaskId, timeSource, t + 5000);
            break;
        case SUBSCRIBE_TO_TOPIC:
            printf("MQTT-SN: Subscribing to topic: '%s'\n\r", ledControlTopic);
            MQTTSN_CLIENT_Subscribe(&mqttsnClient, ledControlTopic, MQTTSN_QOS0, onMQTTTopicSubscribed, onLedcontrolUpdate);
            // Reschedule the task to try again after 5s if acknowledgment is not received
            EMBENET_NODE_TaskSchedule(mqttsnTaskId, timeSource, t + 5000);
            break;
        case RUNNING: {
            // Get current local time
            uint64_t uptime = EMBENET_NODE_GetLocalTime();
            // Construct a simple JSON
            char uptimeStr[80];
            sprintf(uptimeStr, "{\"uptime\":%u}", (unsigned)(uptime / 1000U));
            // Publish the message
            printf("MQTT-SN: Publishing on topic '%s' message: %s QoS: 0\n\r", uptimeTopic, uptimeStr);
            MQTTSN_CLIENT_PublishMessage(&mqttsnClient, uptimeTopic, MQTTSN_QOS0, uptimeStr, strlen(uptimeStr), NULL);
            // Reschedule the task
            EMBENET_NODE_TaskSchedule(taskId, timeSource, t + 10000);
        } break;
        default:
        	printf("MQTT-SN: Unknown service state\n\r");
            break;
    }
}


void mqttsn_client_service_init(void) {
    // Prepare clientId - use the UID of the node as part of the client ID
    EMBENET_EUI64 uid = EMBENET_NODE_GetUID();
    char          clientId[32];
    sprintf(clientId, "Client%x%08x", (unsigned)(uid>>32), (unsigned)(uid));
    // Prepare topics
    sprintf(uptimeTopic, "uptime/%x%08x", (unsigned)(uid>>32), (unsigned)(uid));
    sprintf(buttonTopic, "button/%x%08x", (unsigned)(uid>>32), (unsigned)(uid));
    // Initialize the MQTT-SN client
    if (MQTTSN_CLIENT_RESULT_OK == MQTTSN_CLIENT_Init(&mqttsnClient, clientPortNo, clientId, &mqttEventHandlers)) {
        // Create the service task
        mqttsnTaskId = EMBENET_NODE_TaskCreate(mqttsnServiceTask, &mqttsnClient);
        if (EMBENET_TASKID_INVALID == mqttsnTaskId) {
            MQTTSN_CLIENT_Deinit(&mqttsnClient);
            printf("MQTT-SN: Unable to create task. Service aborted.\n\r");
        } else {
            printf("MQTT-SN: Service initialized with clientId: %s\n\r", clientId);
        }
    } else {
    	printf("MQTT-SN: Unable to initialize MQTT-SN client. Service aborted.\n\r");
    }
}


void mqttsn_client_service_start(void) {
    printf("MQTT-SN: Starting service\n\r");
    serviceState = CONNECTING;
    EMBENET_NODE_TaskSchedule(mqttsnTaskId, EMBENET_NODE_TIME_SOURCE_LOCAL, EMBENET_NODE_GetLocalTime());
}


void mqttsn_client_service_stop(void) {
	printf("MQTT-SN: Stopping service\n\r");
    // Cancel the service task
    EMBENET_NODE_TaskCancel(mqttsnTaskId);
    // Re-initialize the client
    MQTTSN_CLIENT_Deinit(&mqttsnClient);
    // Use the UID of the node as part of the client ID
    char          clientId[32];
    sprintf(clientId, "Client%x%08x", (unsigned)(EMBENET_NODE_GetUID()>>32), (unsigned)(EMBENET_NODE_GetUID()));
    MQTTSN_CLIENT_Init(&mqttsnClient, clientPortNo, clientId, &mqttEventHandlers);
}


static void onPublishSent(struct MQTTSNClient *client, MQTTSNTopicId topicId, void const *data, size_t dataSize) {
	BSP_LED_Off(LED_BLUE);
	printf("MQTT-SN: Publish successful\n\r");
}

static uint64_t publishButtonTopic(int buttonId) {
	// Prepare message to be published
	char payloadStr[32];
	sprintf(payloadStr, "{\"button\":%d}", buttonId);
	// Publish message
	printf("MQTT-SN: Publishing on topic '%s' message: %s QoS: 2\n\r", buttonTopic, payloadStr);
	MQTTSN_CLIENT_PublishMessage(&mqttsnClient, buttonTopic, MQTTSN_QOS2, payloadStr, strlen(payloadStr), onPublishSent);
	BSP_LED_On(LED_BLUE);
	// return publish timestamp
	return EMBENET_NODE_GetLocalTime();
}


void mqttsn_client_service_proc(void) {
    // Holds the last timestamp at which gateway was notified
    static uint64_t lastPublishTimestamp;
    // Check if service is running
    if ((serviceState == RUNNING) && (lastPublishTimestamp + MQTTSN_BUTTON_DELAY_MS < EMBENET_NODE_GetLocalTime())) {
        // Check if button is pressed
    	if (BSP_PB_GetState(B1)) {
        	lastPublishTimestamp = publishButtonTopic(1);
    	} else if (BSP_PB_GetState(B2)) {
        	lastPublishTimestamp = publishButtonTopic(2);
    	} else if (BSP_PB_GetState(B3)) {
        	lastPublishTimestamp = publishButtonTopic(3);
        }
    }
}

