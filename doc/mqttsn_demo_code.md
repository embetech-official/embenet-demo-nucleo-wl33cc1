# Implementation of MQTT-SN demo service {#mqttsn_demo_code}

@tableofcontents

This document describes the implementation of the MQTT-SN demo service running on **NUCLEO-WL33CC1** boards.
This should also provide information on how to modify and extend it for own purposes.


The MQTT-SN Client for embeNET
==============================

This part of the demo uses [MQTT-SN client](https://embe.net/docs/?q=doxyview/embeNET%20MQTT-SN%20Client) running over the embeNET wireless communication protocol.
The MQTT-SN protocol is a version of the popular Message Queuing Telemetry Transport (MQTT) protocol
but made suitable for Sensor Networks that utilize UDP transport protocol instead of TCP.
This implementation is based on the MQTT-SN specification version 1.2.

This client supports the following functions:
 - connecting and disconnecting to the gateway
 - registering topics
 - subscribing to topics and receiving messages on that topic
 - publishing messages on topics

More information about the client is available [here](https://embe.net/docs/?q=doxyview/embeNET%20MQTT-SN%20Client).
 
Architecture of the service
===========================

The service is implemented as a C module called *mqttsn_client_service.c*. The API of the service consists of 4 functions:
- **mqttsn_client_service_init** which initializes the service and prepares it for operation - it is called from within the main function.
- **mqttsn_client_service_start** which starts the service - it is called from within the **onJoined** embeNET callback when the node joins the network.
- **mqttsn_client_service_stops** which stops the service - it is called from within the **onLeft** embeNET callback when the node leaves the network.
- **mqttsn_client_service_proc** which is a function that should be called periodically - it is called from within the main loop.

The service is mostly event driven and uses a single embeNET Node task implemented by the **mqttsnServiceTask** function, which goes through a series of states, described by **mqttsnServiceState** enumeration.

Functionality of the service
============================

The MQTT-SN demo service initialzes the [MQTT-SN client](https://embe.net/docs/?q=doxyview/embeNET%20MQTT-SN%20Client) and tries to connect to the gateway,
which is assumed to run on the border router. Once connected it registers two topics:
- uptime/UID
- button/UID

where UID is the nodes UID expressed in hex format. The service also subscribes to a topic:
- ledcontrol

When the service is running, every 10 seconds a message is published on the **uptime/UID** topic, which includes node's uptime in seconds in a simple JSON format.
If a user presses a button on the board, a message is published on the **button/UID** topic, including button press counter in a simple JSON format. Such message is sent
upmost once every second.

When a message is published on the **ledcontrol** topic the service tries to match it to one of the following commands: *led1on*, *led1off*, *led2on*, *led2off*, *led3on*, *led3off* to change the state of 3 LEDs present on the board.

If the service notices that it is disconnected from the gateway, it will try to reconnect automatically.

QoS level
=========

Similar to MQTT, the MQTT-SN protocol defines several Quality of Service (QoS) levels.
The current implementation of the [MQTT-SN client](https://embe.net/docs/?q=doxyview/embeNET%20MQTT-SN%20Client) uses only QoS 0.
This means that the message delivery is best-effort only and is not guaranteed. This also means that the client may not be able to detect
when it gets disconnected from the gateway.


Implementation of the service
=============================

We will explain the service operation showing the typical flow of events.

Initialization
--------------

The **mqttsn_client_service_init** does two things: initializes the client and creates a service task.

But first a MQTT-SN clientId is constructed as a string "ClientUID" where UID is the nodes UID expressed in hex.
~~~{.c}
    // Prepare clientId - use the UID of the node as part of the client ID
    EMBENET_EUI64 uid = EMBENET_NODE_GetUID();
    char          clientId[32];
    sprintf(clientId, "Client%x%08x", (unsigned)(uid>>32), (unsigned)(uid));
~~~
Similarly, uptime/UID and button/UID topics are constructed:
~~~{.c}
    // Prepare topics
    sprintf(uptimeTopic, "uptime/%x%08x", (unsigned)(uid>>32), (unsigned)(uid));
    sprintf(buttonTopic, "button/%x%08x", (unsigned)(uid>>32), (unsigned)(uid));
~~~
Next the [MQTT-SN client](https://embe.net/docs/?q=doxyview/embeNET%20MQTT-SN%20Client) is initialized:
~~~{.c}
    // Initialize the MQTT-SN client
    MQTTSN_CLIENT_Init(&mqttsnClient, 1885, clientId, &mqttEventHandlers);
~~~
This initializes the client, listening on port number **1885**.

The **mqttEventHandlers** structure groups several MQTT-SN related event handlers:
- **onMQTTConnected** which is called when the client connects to the gateway
- **onMQTTDisconnected** which is called when the client disconnects from the gateway

Next the embeNET Node task is created:
~~~{.c}
    // Create the service task
    mqttsnTaskId = EMBENET_NODE_TaskCreate(mqttsnServiceTask, &mqttsnClient);
~~~

Service start
-------------

When the node joins the network, the service is started through a call to **mqttsn_client_service_start**.
This simply sets up initial state of the state machine and schedules the service task to run immediatelly.
~~~{.c}
    serviceState = CONNECTING;
    EMBENET_NODE_TaskSchedule(mqttsnTaskId, EMBENET_NODE_TIME_SOURCE_LOCAL, EMBENET_NODE_GetLocalTime());
~~~

Connecting to the gateway
-------------------------

Initially, the service task **mqttsnServiceTask** is in the **CONNECTING** state. 
in thas state, the border router address is gathered.
~~~{.c}
    // Get border router address. We assume that the MQTT-SN gateway runs on the border router IP.
    EMBENET_IPV6 addr;
    EMBENET_NODE_GetBorderRouterAddress(&addr);
~~~
Next we perform a clean connect
~~~{.c}
    // Perform a clean connect - you can tweak the timings here
    MQTTSN_CLIENT_CleanConnect(&mqttsnClient, &addr, 1885, 30, 10, NULL, NULL);
~~~

If successful, the **onMQTTConnected** will be called. However, this will not happen if the gateway is not responding. For such case
we plan the task to try again afer 10 seconds.
~~~{.c}
    // Reschedule the task to try again after 10s if failed to connect
    EMBENET_NODE_TaskSchedule(mqttsnTaskId, timeSource, t + 10000);
~~~

If the client connects to the gateway, the **onMQTTConnected** callback is called. From within this callback we move to the next state
and reschedule the task to run immediatelly.
~~~{.c}
    // Move to another state and reschedule the service task
    serviceState = REGISTER_UPTIME_TOPIC;
    EMBENET_NODE_TaskSchedule(mqttsnTaskId, EMBENET_NODE_TIME_SOURCE_LOCAL, EMBENET_NODE_GetLocalTime());
~~~

Registering topics
------------------

We are now in the **REGISTER_UPTIME_TOPIC** state and the **mqttsnServiceTask** runs again.
Here we register the **uptime/UID** topic in the gateway:
~~~{.c}
MQTTSN_CLIENT_RegisterTopic(&mqttsnClient, uptimeTopic, onMQTTTopicRegistered);
~~~
When the topic is registered, the provided **onMQTTTopicRegistered** will be called.

From within this callback we switch the state to **REGISTER_BUTTON_STATE_TOPIC**:
~~~{.c}
    if (serviceState == REGISTER_UPTIME_TOPIC) {
        serviceState = REGISTER_BUTTON_STATE_TOPIC;
    } else {
        serviceState = SUBSCRIBE_TO_TOPIC;
    }
~~~
and reschedule the service task:
~~~{.c}
    // Reschedule immediately
    EMBENET_NODE_TaskSchedule(mqttsnTaskId, EMBENET_NODE_TIME_SOURCE_LOCAL, EMBENET_NODE_GetLocalTime());
~~~

The same thing happens with the **button/UID** topic and we finally land in the **SUBSCRIBE_TO_TOPIC** state.

Subscribing to topics
---------------------
We are now in the **SUBSCRIBE_TO_TOPIC** state and the **mqttsnServiceTask** runs again.
Here we subscribe to the ledcontrol topic:
~~~{.c}
MQTTSN_CLIENT_Subscribe(&mqttsnClient, ledControlTopic, ledUpdate);
~~~
and move to normal operation state **RUNNING**:
~~~{.c}
    // Move to normal state of operation
    serviceState = RUNNING;
    // Reschedule the task
    EMBENET_NODE_TaskSchedule(mqttsnTaskId, timeSource, EMBENET_NODE_GetLocalTime() + 1000);
~~~

Note, that when subscribing to topic we provided a callback function **onLedcontrolUpdate**.
This function will be called when a message is published on the **ledcontrol** topic.
Within that function we will check if the received string is a predefined command and act accordingly.

Publishing uptime
-----------------
We are now in the **RUNNING** state and the **mqttsnServiceTask** runs again.
We get the local time:
~~~{.c}
    // Get current local time
    uint64_t uptime = EMBENET_NODE_GetLocalTime();
~~~
And construct a simple JSON:
~~~{.c}
    // Construct a simple JSON
    char uptimeStr[80];
    sprintf(uptimeStr, "{\"uptime\":%u}", (unsigned)(uptime / 1000U));
~~~
We next publish it on the **uptime/UID** topic:
~~~{.c}
    // Publish the message
    MQTTSN_CLIENT_PublishMessage(&mqttsnClient, uptimeTopic, uptimeStr, strlen(uptimeStr));
~~~
and reschedule this activity in 10s:
~~~{.c}
    // Reschedule the task
    EMBENET_NODE_TaskSchedule(taskId, timeSource, t + 10000);
~~~

Publishing button counter
-------------------------
This is done from within the **mqttsn_client_service_proc** function that is called periodically.
The function checks for button press. Once detected we prepare a simple JSON message:
~~~{.c}
    // Prepare message to be published
    char payloadStr[80];
    sprintf(payloadStr, "{\"button\":%d}", ++buttonPressCounter);
~~~
and next we publish it:
~~~{.c}
    // Publish message
    MQTTSN_CLIENT_PublishMessage(&mqttsnClient, buttonTopic, payloadStr, strlen(payloadStr));
~~~
The rest of the code is used to limit the number of messages to one per second at most.

Disconnecting from gateway
--------------------------

When the [MQTT-SN client](https://embe.net/docs/?q=doxyview/embeNET%20MQTT-SN%20Client) notices that the gateway disconnected it,
it will call the provided **onMQTTDisconnected** calback. 

Within that callback we cancel the service task.
~~~{.c}
    // Cancel the service task
    EMBENET_NODE_TaskCancel(mqttsnTaskId);
~~~
Next we re-initalize the client:
~~~{.c}
    // Re-initialize the client
    MQTTSN_CLIENT_Deinit(&mqttsnClient);
    // Use the UID of the node as part of the client ID
    char          clientId[32];
    sprintf(clientId, "Client%x%08x", (unsigned)(EMBENET_NODE_GetUID()>>32), (unsigned)(EMBENET_NODE_GetUID()));
    MQTTSN_CLIENT_Init(&mqttsnClient, 1885, clientId, &mqttEventHandlers);
~~~
and restart the task again
~~~{.c}
    // Re-initialize and restart the service task
    serviceState = CONNECTING;
    EMBENET_NODE_TaskSchedule(mqttsnTaskId, EMBENET_NODE_TIME_SOURCE_LOCAL, EMBENET_NODE_GetLocalTime() + 5000);
~~~


Service stop
------------

When the node leaves the network, the **mqttsn_client_service_stop** function is called and the MQTT-SN demo service is stopped.
Here we just cancel the task and re-initalize the client:
~~~{.c}
    // Cancel the service task
    EMBENET_NODE_TaskCancel(mqttsnTaskId);
    // Re-initialize the client
    MQTTSN_CLIENT_Deinit(&mqttsnClient);
    // Use the UID of the node as part of the client ID
    char          clientId[32];
    sprintf(clientId, "Client%x%08x", (unsigned)(EMBENET_NODE_GetUID()>>32), (unsigned)(EMBENET_NODE_GetUID()));
    MQTTSN_CLIENT_Init(&mqttsnClient, 1885, clientId, &mqttEventHandlers);
~~~

The service will be started again once the node joins the network once more.

