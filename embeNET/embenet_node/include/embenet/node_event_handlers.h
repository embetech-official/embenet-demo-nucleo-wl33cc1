/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET API
 * @brief     Definition of event handlers for node
 */
#pragma once
#ifndef EMBENET_NODE_EVENT_HANDLERS_H_
#define EMBENET_NODE_EVENT_HANDLERS_H_

#include <embenet/node_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/**
 * @addtogroup embenet_node_api
 * @{
 */

/**
 * @brief Event handler called when the node has successfully joined a network.
 *
 * Called when the node joins a network, regardless of whether the process was started by @ref EMBENET_NODE_Join
 * or @ref EMBENET_NODE_QuickJoin. At the point of this call the node is fully connected to the network identified by @p panId.
 *
 * The provided @p quickJoinCredentials can be stored by the application and passed to @ref EMBENET_NODE_QuickJoin on the next
 * boot to speed up rejoining. The pointer is valid only for the duration of this callback; copy the structure if it needs to be retained.
 *
 * @param[in] panId PAN ID of the network the node has joined.
 * @param[in] quickJoinCredentials pointer to the credentials negotiated with the border router; valid only during this callback.
 */
typedef void (*EMBENET_NODE_OnJoined)(EMBENET_PANID panId, EMBENET_NODE_QuickJoinCredentials const *quickJoinCredentials);

/**
 * @brief Event handler called when the node has left the network.
 *
 * Called when the node leaves a network, either because @ref EMBENET_NODE_Leave was called or because the network connection
 * was lost. To rejoin the network the application must call @ref EMBENET_NODE_Join or @ref EMBENET_NODE_QuickJoin.
 */
typedef void (*EMBENET_NODE_OnLeft)(void);

/**
 * @brief Event handler called when the node attempts to join a network.
 *
 * Called each time the stack makes a join attempt towards a particular network identified by @p panId.
 * This is informational; no action is required from the application.
 *
 * @param[in] panId PAN ID of the network the node is attempting to join.
 * @param[in] panData optional data broadcast by the root node; may be NULL. Valid only for the duration of this callback.
 * @param[in] panDataSize size of @p panData in bytes; 0 if @p panData is NULL.
 */
typedef void (*EMBENET_NODE_OnJoinAttempt)(EMBENET_PANID panId, uint8_t const *panData, size_t panDataSize);

/**
 * @brief Event handler called when the quick join credentials have become obsolete.
 *
 * Called when the stack detects that previously issued @ref EMBENET_NODE_QuickJoinCredentials are no longer valid.
 * The application should discard any stored copy of the credentials and fall back to a full join via @ref EMBENET_NODE_Join.
 */
typedef void (*EMBENET_NODE_OnQuickJoinCredentialsObsolete)(void);

/**
 * @brief Event handler called when a UDP datagram is received on an unregistered port.
 *
 * Called when a UDP datagram arrives for a port that has no registered socket.
 *
 * @param[in] port port number on which the unexpected datagram was received.
 */
typedef void (*EMBENET_NODE_DataOnUnregisteredPort)(uint16_t port);

/// Structure holding embeNET Node stack event handlers
typedef struct {
  /// Event handler that is called when the node joins a given network
  EMBENET_NODE_OnJoined onJoined;
  /// Event handler that is called when the node leaves the network
  EMBENET_NODE_OnLeft onLeft;
  /// Event handler that is called when the node tries to join a network
  EMBENET_NODE_OnJoinAttempt onJoinAttempt;
  /// Event handler that is called when the quick join credentials become obsolete
  EMBENET_NODE_OnQuickJoinCredentialsObsolete onQuickJoinCredentialsObsolete;
  /// Event handler that is called when a UDP datagram was received on an unregistered port
  EMBENET_NODE_DataOnUnregisteredPort onDataOnUnregisteredPort;
} EMBENET_NODE_EventHandlers;

/** @} */

#ifdef __cplusplus
}
#endif

#endif
