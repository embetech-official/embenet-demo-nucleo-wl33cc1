/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET API
 * @brief     embeNET Node API
 *
 * Acronyms:
 *    - PANID		Personal Area Network Identifier, it is assigned by the Border Router, it differentiates logically wireless networks.
 *    - JRC		Join Registrar Coordinator.
 *    - CJ		Constrained Join.
 *    - K1		Pre-shared 16B authentication key which is the same among all nodes in the same network. Its scope can vary from a
 * single network identified by PANID to all nodes in multiple networks. K1 is assigned by application.
 *    - K2		Key obtained during Constrained Join process, assigned automatically by JRC. Ensures network-level security.
 *    - PSK		Pre-shared Constrained Join key. Should be unique and shared with destined Join Registrar Coordinator.
 */

#ifndef EMBENET_NODE_H_
#define EMBENET_NODE_H_

#include <embenet/node_defs.h>
#include <embenet/node_event_handlers.h>
#include <embenet/udp.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @addtogroup embenet_node_api embeNET Node API
 *
 * This page documents the embeNET Node C API. The API consists of the following parts:
 *
 * Stack management                         ||
 * -----------------------------------------|------------------------------------------------------
 * @ref EMBENET_NODE_Init                   | Initializes the node network process.
 * @ref EMBENET_NODE_Deinit                 | Deinitializes the node network process.
 * @ref EMBENET_NODE_Proc                   | Advances (runs) the node network process.
 *
 * Network management                       ||
 * -----------------------------------------|------------------------------------------------------
 * @ref EMBENET_NODE_Join                   | Makes the node join the network.
 * @ref EMBENET_NODE_QuickJoin              | Makes the join the network using previously negotiated credentials for quicker join.
 * @ref EMBENET_NODE_Leave                  | Makes the node leave the network.
 * @ref EMBENET_NODE_GetUID                 | Gets own unique identifier.
 * @ref EMBENET_NODE_SetUID                 | Sets own unique identifier.
 * @ref EMBENET_NODE_GetBorderRouterAddress | Gets the IPv6 address of the border router.
 * @ref EMBENET_NODE_GetParentAddress       | Gets the IPv6 link-local address of the parent node.
 * @ref EMBENET_NODE_GetOwnAddress          | Gets the IPv6 unicast address of the own node.
 * @ref EMBENET_NODE_ForceParentChange      | Forces parent change.
 * @ref EMBENET_NODE_RootStart              | Starts operation as a root node.
 *
 * Group management                         ||
 * -----------------------------------------|------------------------------------------------------
 * @ref EMBENET_NODE_JoinGroup              | Makes the node join a specific group.
 * @ref EMBENET_NODE_LeaveGroup             | Makes the node leave a specific group.
 * @ref EMBENET_NODE_GetGroupCount          | Gets the number of groups the node belongs to.
 * @ref EMBENET_NODE_GetGroupByIndex        | Gets the group number by index.
 *
 * Task management                          ||
 * -----------------------------------------|------------------------------------------------------
 * @ref EMBENET_NODE_TaskCreate             | Creates a task that can be scheduled.
 * @ref EMBENET_NODE_TaskDestroy            | Destroys a previously created task.
 * @ref EMBENET_NODE_TaskSchedule           | Schedules a task.
 * @ref EMBENET_NODE_TaskCancel             | Cancels a scheduled task.
 * @ref EMBENET_NODE_GetLocalTime           | Gets current local node time.
 * @ref EMBENET_NODE_GetNetworkTime         | Gets current network time.
 * @ref EMBENET_NODE_GetNetworkAsn          | Gets current Absolute Slot Offset
 *
 * Utility functions                        ||
 * -----------------------------------------|------------------------------------------------------
 * @ref EMBENET_NODE_GetRandomValue         | Gets a random value
 * @ref EMBENET_NODE_GetVersion             | Gets embeNET stack version
 *
 * The section below explains the stack states that groups the usage scope of functions mentioned above:
 *
 * @anchor UNINITIALIZED
 * **UNINITIALIZED** - stack inactive, no operation permitted:
 *    - Enter condition:
 *      - Default state at a start of the system.
 *      - @ref EMBENET_NODE_Deinit
 *    - Available transition:
 *      - @ref INITIALIZED
 *        - @ref EMBENET_NODE_Init
 *
 * @anchor INITIALIZED
 * **INITIALIZED** - stack inactive, entry point to begin the operations:
 *    - Enter condition:
 *      - @ref EMBENET_NODE_Init
 *      - @ref EMBENET_NODE_Leave
 *    - Available transition:
 *      - @ref JOINING
 *        - @ref EMBENET_NODE_Join
 *        - @ref EMBENET_NODE_QuickJoin
 *      - @ref UNINITIALIZED
 *        - @ref EMBENET_NODE_Deinit
 *
 * @anchor JOINING
 * **JOINING** - node attempts to join a network
 *    - On-enter:
 *      - @ref EMBENET_NODE_OnLeft is called, only from @ref JOINED state
 *    - Enter condition:
 *      - @ref EMBENET_NODE_Join
 *      - @ref EMBENET_NODE_QuickJoin
 *      - self-prompted when node for some reason left the previous network or previous connection attempt failed
 *    - Available transition:
 *      - @ref SYNCHRONIZED
 *        - self-prompted when node has found a network and synchronizes to it
 *      - @ref UNINITIALIZED
 *        - @ref EMBENET_NODE_Deinit
 *      - @ref INITIALIZED
 *        - @ref EMBENET_NODE_Leave
 *
 * @anchor SYNCHRONIZED
 * **SYNCHRONIZED** - node synchronized, node performs initial maintenance operations
 *    - On enter:
 *      - @ref EMBENET_NODE_OnJoinAttempt is called
 *    - Enter condition:
 *      - self-prompted when node automatically synchronizes to a network
 *    - Available transition:
 *      - @ref JOINING
 *        - self-prompted when node cannot successfully become fully operable
 *      - @ref JOINED
 *        - self-prompted when node autonomously becomes fully operable
 *      - @ref UNINITIALIZED
 *        - @ref EMBENET_NODE_Deinit
 *      - @ref INITIALIZED
 *        - @ref EMBENET_NODE_Leave
 *
 * @anchor JOINED
 * **JOINED** - node fully operable
 *    - On enter:
 *      - @ref EMBENET_NODE_OnJoined is called
 *    - Enter condition:
 *      - self-prompted when node automatically becomes fully operable
 *    - Available transition:
 *      - @ref JOINING
 *        - self-prompted when node loses the network
 *      - @ref UNINITIALIZED
 *        - @ref EMBENET_NODE_Deinit
 *      - @ref INITIALIZED
 *        - @ref EMBENET_NODE_Leave
 *
 * List of correct API function calls with respect to the stack state:
 * - @ref EMBENET_NODE_Init - @ref UNINITIALIZED
 * - @ref EMBENET_NODE_Deinit - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_Proc - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_Join - @ref INITIALIZED
 * - @ref EMBENET_NODE_QuickJoin - @ref INITIALIZED
 * - @ref EMBENET_NODE_Leave - @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_GetUID - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_SetUID - @ref UNINITIALIZED
 * - @ref EMBENET_NODE_GetBorderRouterAddress - @ref JOINED
 * - @ref EMBENET_NODE_GetParentAddress - @ref JOINED
 * - @ref EMBENET_NODE_GetOwnAddress - @ref JOINED
 * - @ref EMBENET_NODE_ForceParentChange - @ref JOINED
 * - @ref EMBENET_NODE_RootStart - @ref INITIALIZED
 * - @ref EMBENET_NODE_JoinGroup - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_LeaveGroup - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_GetGroupCount - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_GetGroupByIndex - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_TaskCreate - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_TaskDestroy - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_TaskSchedule - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_TaskCancel - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_GetLocalTime - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_GetNetworkTime - @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_GetNetworkAsn - @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_GetRandomValue - @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 * - @ref EMBENET_NODE_GetVersion - @ref UNINITIALIZED, @ref INITIALIZED, @ref JOINING, @ref SYNCHRONIZED, @ref JOINED
 *
 * Refer to @ref embenet_node_user_guide for information on how to use the API.
 *
 * @{
 */

/** Structure defining the network configuration */
typedef struct {
  EMBENET_K1 k1;   ///< Common network key. This key must be the same for all nodes and border router joining the same network.
  EMBENET_PSK psk; ///< Pre-shared key
} EMBENET_NODE_JoinConfig;

typedef uint32_t EMBENET_TaskId; ///< Identifier of an application-level task running within the stack

#define EMBENET_TASKID_INVALID UINT32_MAX ///< Special value of EMBENET_TaskId that informs that the task is invalid

/** Possible time sources for task scheduling */
typedef enum {
  /// Local node time
  EMBENET_NODE_TIME_SOURCE_LOCAL = 0,
  /// Network time
  EMBENET_NODE_TIME_SOURCE_NETWORK = 1
} EMBENET_NODE_TimeSource;

/**
 * Prototype of user task function that can be scheduled in either local, or network time.
 *
 * @param[in] taskId id of the running task
 * @param[in] timeSource time source for the scheduled task
 * @param[in] t time at which the task was expected to run
 * @param[in] context context as provided when the task was created
 */
typedef void (*EMBENET_NODE_TaskFunction)(EMBENET_TaskId taskId, EMBENET_NODE_TimeSource timeSource, uint64_t t, void *context);

/**
 * @brief Initializes the embeNET networking stack for node.
 *
 * This function initializes the embeNET networking stack in the node. It reserves and initializes the resources needed for the stack operation.
 * It also initializes the underlying port (hardware).
 * This call starts the local clock in the node so that the time returned through a call to @ref EMBENET_NODE_GetLocalTime starts to flow.
 *
 * After initialization @ref EMBENET_NODE_Proc should be called periodically.
 * Must be called before any other API function, except @ref EMBENET_NODE_SetUID and @ref EMBENET_NODE_GetVersion.
 *
 * @note For more information refer to @ref embenet_node_stack_handling.
 *
 * @param[in] eventHandlers pointer to the event handler structure; all desired handlers must be set before calling this function.
 *                          The pointed-to structure must remain valid until @ref EMBENET_NODE_Deinit is called.
 *                          May be NULL if no event handlers are needed.
 *
 * @retval EMBENET_RESULT_OK if initialization completed successfully
 * @retval EMBENET_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 */
EMBENET_Result EMBENET_NODE_Init(EMBENET_NODE_EventHandlers const *eventHandlers);

/**
 * @brief Deinitializes the embeNET networking stack.
 *
 * This function deinitializes the embeNET networking stack. Once called, all activities within the stack are stopped and all dynamically
 * allocated resources (if any) are freed. In order to use the stack again, @ref EMBENET_NODE_Init must be called.
 *
 * @note If the stack is operational (e.g. a node is joining or performing any other operation), calling this function immediately terminates
 *       all those operations.
 * @note For more information refer to @ref embenet_node_stack_handling.
 */
void EMBENET_NODE_Deinit(void);

/**
 * @brief Runs the networking process of the embeNET stack for node.
 *
 * This function should be called periodically within the main loop of a program (or a thread) after a call to @ref EMBENET_NODE_Init.
 * It advances the networking process that is running in the stack which is responsible for all networking activities.
 * In particular, many event callbacks registered in the stack are called from within the context of this function.
 * This function performs time-invariant operations that may be processed in a non-ISR, non-privileged MCU routine.
 *
 * @note For more information refer to @ref embenet_node_stack_handling.
 *
 * @warning Aborts when called on an uninitialized stack.
 */
void EMBENET_NODE_Proc(void);

/**
 * @brief Starts the network joining process as a node.
 *
 * This function starts the process of joining the node to the network. To join the network the application must provide the
 * configuration structure (see @ref EMBENET_NODE_JoinConfig) containing:
 * - k1 - common network key
 * - psk - pre-shared device-specific key
 *
 * @note For more information on joining the network refer to @ref embenet_node_network_handling.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] config pointer to the network configuration structure; must not be NULL.
 *
 * @retval EMBENET_RESULT_OK if the joining process has begun successfully
 * @retval EMBENET_RESULT_WRONG_STATE if not called in @ref INITIALIZED state
 * @retval EMBENET_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 */
EMBENET_Result EMBENET_NODE_Join(EMBENET_NODE_JoinConfig const *config);

/**
 * @brief Starts the network joining process as a node using previously stored @ref EMBENET_NODE_QuickJoinCredentials for a quicker join.
 *
 * This function starts the process of joining the node to the network using the credentials (@ref EMBENET_NODE_QuickJoinCredentials)
 * established during the previous join. Re-using these credentials allows the node to speed up the joining process.
 *
 * @note For more information on joining the network refer to @ref embenet_node_network_handling and specifically @ref
 * embenet_node_network_quick_join.
 *
 * @param[in] quickJoinCredentials pointer to the credentials returned by the @ref EMBENET_NODE_OnJoined callback; must not be NULL.
 *
 * @retval EMBENET_RESULT_OK if the quick joining process has begun successfully
 * @retval EMBENET_RESULT_WRONG_STATE if not called in @ref INITIALIZED state
 * @retval EMBENET_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval EMBENET_RESULT_INVALID_CREDENTIALS if the provided credentials were invalid
 */
EMBENET_Result EMBENET_NODE_QuickJoin(EMBENET_NODE_QuickJoinCredentials const *quickJoinCredentials);

/**
 * @brief Disconnects the node from the network.
 *
 * This function causes the node to go back to the @ref INITIALIZED state, stopping all network activity.
 * If the node was joined to the network, all tasks scheduled in network time are canceled.
 * This call can also be used to stop an ongoing joining process.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @retval EMBENET_RESULT_OK if the leave process was triggered successfully
 * @retval EMBENET_RESULT_WRONG_STATE if the node is not in @ref JOINING, @ref SYNCHRONIZED or @ref JOINED state
 */
EMBENET_Result EMBENET_NODE_Leave(void);

/**
 * @brief Starts operation as a root node.
 *
 * This function causes the node to act as a root node in the network. Once started, such a node is controlled
 * exclusively by an external entity called border router.
 *
 * During network formation and operation the root node can broadcast additional data to all nodes wishing to join the network.
 * This data is set by the border router and is available in joining nodes through the @ref EMBENET_NODE_OnJoinAttempt event handler.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @retval EMBENET_RESULT_OK if the root operation has started successfully
 * @retval EMBENET_RESULT_WRONG_STATE if the node is not in @ref INITIALIZED state
 * @retval EMBENET_RESULT_ROOT_CAPABILITIES_DISABLED if root capabilities were not built in
 */
EMBENET_Result EMBENET_NODE_RootStart(void);

/**
 * @brief Makes the node join the given multicast group.
 *
 * The node can belong to many multicast groups. This call is used to join the group with a specific group identifier.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] groupId identifier of the group that the node should join
 *
 * @retval true if the node successfully joined the group
 * @retval false if the group could not be joined (e.g. the group registry is full)
 */
bool EMBENET_NODE_JoinGroup(EMBENET_GroupId groupId);

/**
 * @brief Makes the node leave the given multicast group.
 *
 * The node can belong to many multicast groups. This call is used to leave the group with a specific group identifier.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] groupId identifier of the group that the node should leave
 *
 * @retval true if the node successfully left the group
 * @retval false if the group was not found in the node's group registry
 */
bool EMBENET_NODE_LeaveGroup(EMBENET_GroupId groupId);

/**
 * @brief Gets the number of groups the node belongs to.
 *
 * The node can belong to many multicast groups. Each time @ref EMBENET_NODE_JoinGroup or @ref EMBENET_NODE_LeaveGroup
 * is called, the number of groups the node belongs to may change. This call allows to get the current number of groups
 * the node belongs to. The individual groups can then be enumerated using @ref EMBENET_NODE_GetGroupByIndex.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Current number of groups the node belongs to.
 */
size_t EMBENET_NODE_GetGroupCount(void);

/**
 * @brief Gets the group identifier the node belongs to, by index.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] index group index in the range [0, @ref EMBENET_NODE_GetGroupCount() - 1]
 *
 * @return Group identifier, or `EMBENET_GROUPID_INVALID` if the index is outside the valid range.
 */
EMBENET_GroupId EMBENET_NODE_GetGroupByIndex(size_t index);

/**
 * @brief Registers an application-level task.
 *
 * This function registers a new application-level task within the networking stack.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] taskFunction pointer to the function that will be run as the task; must not be NULL.
 * @param[in] userContext optional context pointer that will be passed to @p taskFunction when it is called; may be NULL.
 *
 * @return Task identifier that can be used in subsequent calls to @ref EMBENET_NODE_TaskSchedule, @ref EMBENET_NODE_TaskCancel
 *         and @ref EMBENET_NODE_TaskDestroy, or @ref EMBENET_TASKID_INVALID if the task could not be created
 *         (e.g. the maximum number of tasks has been reached).
 */
EMBENET_TaskId EMBENET_NODE_TaskCreate(EMBENET_NODE_TaskFunction taskFunction, void *userContext);

/**
 * @brief Destroys a previously created task.
 *
 * If the task is currently scheduled, it is canceled before being destroyed.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] taskId task identifier as returned by @ref EMBENET_NODE_TaskCreate
 *
 * @retval EMBENET_RESULT_OK if the task was destroyed successfully
 * @retval EMBENET_RESULT_INVALID_ARGUMENT if @p taskId does not refer to a valid task
 */
EMBENET_Result EMBENET_NODE_TaskDestroy(EMBENET_TaskId taskId);

/**
 * @brief Schedules a task at the given time, or reschedules it if already scheduled.
 *
 * @note If called more than once before the task executes, the task is rescheduled to the latest provided time.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] taskId task identifier as returned by @ref EMBENET_NODE_TaskCreate
 * @param[in] timeSource time source for the scheduled task
 * @param[in] t absolute time at which the task should run, expressed in milliseconds
 *
 * @retval EMBENET_RESULT_OK if the task was scheduled successfully
 * @retval EMBENET_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval EMBENET_RESULT_UNABLE_TO_SCHEDULE_IN_THE_PAST if the requested time is in the past
 * @retval EMBENET_RESULT_NOT_SYNCHRONIZED if @ref EMBENET_NODE_TIME_SOURCE_NETWORK was requested but the node is not synchronized to the network
 */
EMBENET_Result EMBENET_NODE_TaskSchedule(EMBENET_TaskId taskId, EMBENET_NODE_TimeSource timeSource, uint64_t t);

/**
 * @brief Cancels a previously scheduled task.
 *
 * @note Safe to call even when the task is not currently scheduled; in that case there is no effect.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] taskId task identifier as returned by @ref EMBENET_NODE_TaskCreate
 *
 * @retval EMBENET_RESULT_OK if the task was canceled successfully or was not scheduled
 * @retval EMBENET_RESULT_INVALID_ARGUMENT if @p taskId does not refer to a valid task
 */
EMBENET_Result EMBENET_NODE_TaskCancel(EMBENET_TaskId taskId);

/**
 * @brief Gets own UID which is an EUI-64 address.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return UID of the node, or `EMBENET_EUI64_INVALID` if the UID was not set by the underlying hardware nor by the user.
 */
EMBENET_EUI64 EMBENET_NODE_GetUID(void);

/**
 * @brief Sets own UID which is an EUI-64 address.
 *
 * This function sets the UID used to identify the node in the network.
 * In most cases calling this function directly is not needed, as the UID is normally taken from the underlying hardware platform.
 *
 * @note In rare cases the application may want to control how UIDs are generated. In such scenarios extreme care must be taken to
 *       ensure that UIDs are truly unique across all nodes in the deployment.
 * @warning Must be called after @ref EMBENET_NODE_Init and before @ref EMBENET_NODE_Join or @ref EMBENET_NODE_RootStart.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] uid the EUI-64 address to assign to this node
 *
 * @retval EMBENET_RESULT_OK if the UID was set successfully
 * @retval EMBENET_RESULT_WRONG_STATE if the node is not in @ref INITIALIZED state
 */
EMBENET_Result EMBENET_NODE_SetUID(EMBENET_EUI64 uid);

/**
 * @brief Forces a parent change.
 *
 * This function should be used when QoS significantly exceeds the expected level, e.g. when multicast traffic does not work
 * despite all other services operating correctly.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @retval EMBENET_RESULT_OK if the parent change procedure was started successfully
 * @retval EMBENET_RESULT_WRONG_STATE if the node is not in @ref JOINED state
 */
EMBENET_Result EMBENET_NODE_ForceParentChange(void);

/**
 * @brief Gets the IPv6 address of the border router, if reachable.
 *
 * This function gets the IPv6 address of the border router that started the network the node has joined.
 *
 * @note In the vast majority of cases the border router address becomes valid immediately after joining.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[out] ipv6 pointer to the location where the IPv6 address will be stored; must not be NULL.
 *
 * @retval EMBENET_RESULT_OK if the border router IPv6 address was stored successfully
 * @retval EMBENET_RESULT_WRONG_STATE if the node is not in @ref JOINED state
 * @retval EMBENET_RESULT_INVALID_ARGUMENT if @p ipv6 is NULL
 * @retval EMBENET_RESULT_UNSPECIFIED_ERROR if the border router address is not yet available
 */
EMBENET_Result EMBENET_NODE_GetBorderRouterAddress(EMBENET_IPV6 *ipv6);

/**
 * @brief Gets the link-local IPv6 address of the parent node.
 *
 * @note In the vast majority of cases the parent address is valid immediately after joining. The parent address may change over time.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[out] ipv6 pointer to the location where the IPv6 address will be stored; must not be NULL.
 *
 * @retval EMBENET_RESULT_OK if the parent IPv6 address was stored successfully
 * @retval EMBENET_RESULT_WRONG_STATE if the node is not in @ref JOINED state
 * @retval EMBENET_RESULT_INVALID_ARGUMENT if @p ipv6 is NULL
 * @retval EMBENET_RESULT_UNSPECIFIED_ERROR if the parent address is not available
 */
EMBENET_Result EMBENET_NODE_GetParentAddress(EMBENET_IPV6 *ipv6);

/**
 * @brief Gets the node's own unicast IPv6 address.
 *
 * @note This address is valid only after the node has joined the network, as it is formed from the network prefix and the node's UID.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[out] ipv6 pointer to the location where the IPv6 address will be stored; must not be NULL.
 *
 * @retval EMBENET_RESULT_OK if the own IPv6 address was stored successfully
 * @retval EMBENET_RESULT_WRONG_STATE if the node is not in @ref JOINED state
 * @retval EMBENET_RESULT_INVALID_ARGUMENT if @p ipv6 is NULL
 */
EMBENET_Result EMBENET_NODE_GetOwnAddress(EMBENET_IPV6 *ipv6);

/**
 * @brief Gets the current local time since the networking stack was initialized.
 *
 * @note Returns a monotonic clock value that starts at 0 when @ref EMBENET_NODE_Init is called and stops when @ref EMBENET_NODE_Deinit is called.
 * @note The clock is local to this node and is NOT synchronized with other nodes in the network.
 * @note The 64-bit range is large enough that overflow need not be considered in practice.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Local time expressed in milliseconds.
 */
uint64_t EMBENET_NODE_GetLocalTime(void);

/**
 * @brief Gets the current network time.
 *
 * @note Network time is the elapsed duration since ASN 0, shared by all nodes in the network. It has no fixed epoch and may start at a large value.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Network time expressed in milliseconds, or 0 if the node is not in @ref SYNCHRONIZED or @ref JOINED state.
 */
uint64_t EMBENET_NODE_GetNetworkTime(void);

/**
 * @brief Gets the current network time expressed as an Absolute Slot Number (ASN).
 *
 * @note The ASN has no fixed start point and may begin at a large value.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Current ASN, or 0 if the node is not in @ref SYNCHRONIZED or @ref JOINED state.
 */
uint64_t EMBENET_NODE_GetNetworkAsn(void);

/**
 * @brief Gets a random unsigned integer value from a given inclusive range.
 *
 * @warning @p stop must be greater than or equal to @p start; violating this aborts the stack.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] start lowest value in the range (inclusive)
 * @param[in] stop highest value in the range (inclusive)
 *
 * @return Random value in the range [@p start, @p stop].
 */
uint32_t EMBENET_NODE_GetRandomValue(uint32_t start, uint32_t stop);

/**
 * @brief Gets the embeNET stack version.
 *
 * This function may be called at any time, including before @ref EMBENET_NODE_Init.
 *
 * @return Structure describing the stack version.
 */
EMBENET_Version EMBENET_NODE_GetVersion(void);


/**
 * Returns the semantic version string of this component.
 * @return char const*
 */
char const *EMBENET_NODE_GetVersionString(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // EMBENET_NODE_H_
