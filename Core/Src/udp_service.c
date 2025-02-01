/**
@file
@copyright $Copyright$
@version   $Revision$
@purpose   embeNET demo
@brief     Exemplary UDP-based client service
*/

#include "udp_service.h"
#include "main.h"
#include <embenet/node.h>
#include <embenet/enms_node.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

/// Socket descriptor for exemplary, user-defined custom service
static EMBENET_UDP_SocketDescriptor udpServiceSocket;
/// Id of the task running the custom service
static EMBENET_TaskId udpServiceTaskId = EMBENET_TASKID_INVALID;

/**
 * @brief User-defined function that will be invoked as a periodically scheduled task
 *
 * @param[in] taskId id of the task
 * @param[in] timeSource time source (local time or network time)
 * @param[in] t time at which the task was scheduled to run
 * @param[in] context generic, user-defined context
 */
static void udpServiceTask(EMBENET_TaskId taskId, EMBENET_NODE_TimeSource timeSource, uint64_t t, void *context) {
    static int counter;

    // make a simple message with counter
    char message[32];
    int messageLength = snprintf(message, sizeof(message), "Custom message no %d", counter++);
    // get border router address
    EMBENET_IPV6 borderRouterAddress;
    EMBENET_NODE_GetBorderRouterAddress(&borderRouterAddress);
    // send UDP packet using port 1234
    if (EMBENET_UDP_RESULT_OK != EMBENET_UDP_Send(&udpServiceSocket, &borderRouterAddress, 1234, message, messageLength)) {
        printf("UDP_SERVICE: Failed to send UDP packet\n\r");
    }

    // Schedule next invocation of this task after 5 seconds
    EMBENET_NODE_TaskSchedule(taskId, timeSource, t + 5000);
}

/**
 * @brief User-defined function that will be invoked upon datagram reception on udpServiceSocket
 *
 * @param[in] socket pointer to socket descriptor (facilitates binding same reception handler with multiple sockets; also socket descriptor stores user context)
 * @param[in] sourceAddress IPv6 Address of the packet originator
 * @param[in] sourcePort UDP source port
 * @param[in] data pointer to datagram's payload
 * @param[in] dataSize size of datagram's payload
 */
static void udpServiceReceptionHandler(EMBENET_UDP_SocketDescriptor const *socket,
        EMBENET_IPV6 const *sourceAddress, uint16_t sourcePort,
        void const *data, size_t dataSize) {
    // Retrieve command from datagram's payload
    char const *msg = (char const*) data;

    if (dataSize >= 6) {
        // Perform action based on received command
        if (0 == strncmp(msg, "led1on", 6)) {
            printf("UDP_SERVICE: Led 1 on\n\r");
            BSP_LED_On(LED_RED);
        } else if (0 == strncmp(msg, "led1off", 7)) {
            printf("UDP_SERVICE: Led 1 off\n\r");
            BSP_LED_Off(LED_RED);
        } else if (0 == strncmp(msg, "led2on", 6)) {
            printf("UDP_SERVICE: Led 2 on\n\r");
            BSP_LED_On(LED_GREEN);
        } else if (0 == strncmp(msg, "led2off", 7)) {
            printf("UDP_SERVICE: Led 2 off\n\r");
            BSP_LED_Off(LED_GREEN);
        } else if (0 == strncmp(msg, "led3on", 6)) {
            printf("UDP_SERVICE: Led 3 on\n\r");
            BSP_LED_On(LED_BLUE);
        } else if (0 == strncmp(msg, "led3off", 7)) {
            printf("UDP_SERVICE: Led 3 off\n\r");
            BSP_LED_Off(LED_BLUE);
        } else {
            printf("UDP_SERVICE: Unrecognized command with size: %d\n\r", (int)dataSize);
        }
    } else {
        printf("UDP_SERVICE: Unrecognized command with size: %d\n\r", (int)dataSize);
    }
}

void udp_service_init(void) {
    // Initialize UDP socket on node's unicast address, and port 1234. Upon datagram reception, udpServiceReceptionHandler will be called)
    udpServiceSocket = (EMBENET_UDP_SocketDescriptor ) {
        .port = 1234,
        .groupId = 0, // GroupId is ignored, when using EMBENET_UDP_TRAFFIC_UNICAST
        .handledTraffic = EMBENET_UDP_TRAFFIC_UNICAST,
        .rxDataHandler = udpServiceReceptionHandler,
        .userContext = NULL // userContext is not needed in this example, however user may pass it to callback invocation
    };

    // Register UDP socket. Registering socket enables datagram reception/transmission
    EMBENET_Result udpServiceSocketRegistrationStatus = EMBENET_UDP_RegisterSocket(&udpServiceSocket);
    if (EMBENET_RESULT_OK == udpServiceSocketRegistrationStatus) {
        printf("UDP_SERVICE: Socket %d registered successfully\n\r", (int)udpServiceSocket.port);
        // Create a task using built-in scheduler
        udpServiceTaskId = EMBENET_NODE_TaskCreate(udpServiceTask, NULL);
        if (EMBENET_TASKID_INVALID == udpServiceTaskId) {
            printf("UDP_SERVICE: Unable to create task\n\r");
        } else {
            printf("UDP_SERVICE: Service initialized\n\r");
        }
    } else {
        printf("UDP_SERVICE: Registering socket failed with status %d\n\r", (int)udpServiceSocketRegistrationStatus);
    }
}

void udp_service_start(void) {
    printf("UDP_SERVICE: Starting service\n\r");
    // Get current time
    uint64_t current_time = EMBENET_NODE_GetLocalTime();
    // Schedule task using node's local time (invoke it after 2 seconds)
    EMBENET_NODE_TaskSchedule(udpServiceTaskId, EMBENET_NODE_TIME_SOURCE_LOCAL, current_time + 2000);
}

void udp_service_stop(void) {
    printf("UDP_SERVICE: Stopping service\n\r");
    // Cancel scheduled task
    EMBENET_NODE_TaskCancel(udpServiceTaskId);
}
