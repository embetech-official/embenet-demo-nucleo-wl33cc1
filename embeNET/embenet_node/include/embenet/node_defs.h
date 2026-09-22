/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET API
 * @brief     Common API definitions
 */
#pragma once
#ifndef EMBENET_DEFS_H_
#define EMBENET_DEFS_H_

#include <embenet/udp.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/** @addtogroup embenet_common embeNET common definitions
 *  @{
 */

/// Possible result codes
typedef enum {
  EMBENET_RESULT_OK = 0,
  EMBENET_RESULT_UNSPECIFIED_ERROR,          ///< Unspecified internal error.
  EMBENET_RESULT_INVALID_ARGUMENT,           ///< At least one function argument is invalid.
  EMBENET_RESULT_CALLED_OUTSIDE_A_TASK,      ///< The function was called outside of a running task context.
  EMBENET_RESULT_NOT_SYNCHRONIZED,           ///< The node is not synchronized to the network.
  EMBENET_RESULT_INVALID_CREDENTIALS,        ///< The provided credentials are invalid.
  EMBENET_RESULT_ROOT_CAPABILITIES_DISABLED, ///< The requested operation requires root capabilities that were not compiled in.
  EMBENET_RESULT_WRONG_STATE,                ///< The function was called in an incorrect stack state.
  // UDP specific
  EMBENET_RESULT_UDP_MAX_DATA_SIZE_EXCEEDED, ///< The data size exceeds the maximum allowed UDP payload.
  EMBENET_RESULT_UDP_PACKET_QUEUE_FULL,      ///< The packet queue is full; the packet was dropped.
  EMBENET_RESULT_UDP_FORWARDING_ERROR,       ///< A forwarding error occurred while sending the UDP packet.
  EMBENET_RESULT_UDP_SOCKET_UNREGISTERED,    ///< The UDP socket is not registered.
  // JoinRules specific
  EMBENET_RESULT_JOIN_RULE_ALREADY_EXISTS, ///< Adding the join rule failed because an identical rule already exists.
  EMBENET_RESULT_JOIN_RULE_NOT_FOUND,      ///< The requested join rule was not found in the registry.
  EMBENET_RESULT_JOIN_RULE_REGISTER_FULL,  ///< Adding the join rule failed because the registry is full.
} EMBENET_Result;

/* Network types */
typedef uint64_t EMBENET_NetworkPrefix; ///< Network prefix - common first 8 bytes of a node's IPv6 address.

typedef uint16_t EMBENET_PANID; ///< IEEE 802.15.4e PAN identifier.

/// Possible addressing modes
typedef enum {
  EMBENET_ADDRESSING_MODE_SINGLE, ///< Unicast addressing - the recipient is a single node.
  EMBENET_ADDRESSING_MODE_GROUP,  ///< Multicast addressing - the recipients are all nodes within a group.
} EMBENET_AddressingMode;

/**
 * Initial value of internal random number generators.
 * @warning Using a non-random (predictable) seed is a serious security vulnerability.
 */
typedef uint64_t EMBENET_RandomSeed;

/// 128-bit pre-shared key used to authenticate beacons. Must be identical for all nodes and the border router in the same network.
typedef struct {
  uint8_t val[16]; ///< Key bytes.
} EMBENET_K1;

/// 128-bit constrained join pre-shared key. Must be unique per device and shared with the JRC.
typedef struct {
  uint8_t val[16]; ///< Key bytes.
} EMBENET_PSK;

/**
 * Opaque structure holding the credentials needed for a quick network rejoin.
 *
 * The contents are managed entirely by the stack. The application must store and restore this structure verbatim between
 * power cycles in order to use @ref EMBENET_NODE_QuickJoin. The structure must not be modified by the application.
 */
typedef struct {
  uint8_t reserved[52]; ///< Stack-managed credential data; do not access directly.
} EMBENET_NODE_QuickJoinCredentials;

/// Structure describing the embeNET stack version.
typedef struct {
  uint8_t hi;   ///< Major version number.
  uint8_t lo;   ///< Minor version number.
  uint16_t rev; ///< Revision (patch) number.
} EMBENET_Version;

/** @} */

#ifdef __cplusplus
}
#endif

#endif
