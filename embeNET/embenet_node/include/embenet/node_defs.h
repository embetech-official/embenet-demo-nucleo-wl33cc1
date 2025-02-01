/**
 * @file
 * @license   commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.0.4
 * @purpose   embeNET API
 * @brief     Common API definitions
 */

#ifndef EMBENET_DEFS_H_
#define EMBENET_DEFS_H_

#include <embenet/udp.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup embenet_common embeNET common definitions
 *  @{
 */

/// Possible result codes
typedef enum {
  EMBENET_RESULT_OK = 0,
  EMBENET_RESULT_UNSPECIFIED_ERROR,              ///< Unspecified error
  EMBENET_RESULT_INVALID_ARGUMENT,               ///< Function arguments are invalid
  EMBENET_RESULT_CALLED_OUTSIDE_A_TASK,          ///< The called function was called outside of a running task
  EMBENET_RESULT_NOT_SYNCHRONIZED,               ///< The node is not synchronized to the network
  EMBENET_RESULT_UNABLE_TO_SCHEDULE_IN_THE_PAST, ///< The task was not scheduled because the requested time is in the past
  EMBENET_RESULT_INVALID_CREDENTIALS,            ///< The provided credentials were invalid
  EMBENET_RESULT_ROOT_CAPABILITIES_DISABLED,     ///< The requested operation requires root capabilities, which were not built in
  EMBENET_RESULT_WRONG_STATE,                    ///< Node during wrong state
  // UDP specific
  EMBENET_RESULT_UDP_MAX_DATA_SIZE_EXCEEDED, ///< Data size beyond limit
  EMBENET_RESULT_UDP_PACKET_QUEUE_FULL,      ///< Device's packet queue is full
  EMBENET_RESULT_UDP_FORWARDING_ERROR,       ///< Forwarding error
  EMBENET_RESULT_UDP_SOCKET_UNREGISTERED,    ///< UDP socket was not registered
  // JoinRules specific
  EMBENET_RESULT_JOIN_RULE_ALREADY_EXISTS, ///< Adding rule failed - the rule already exists
  EMBENET_RESULT_JOIN_RULE_NOT_FOUND,      ///< Rule not found in the register
  EMBENET_RESULT_JOIN_RULE_REGISTER_FULL,  // Adding rule failed - there is no more space to store the rule
} EMBENET_Result;

/* Network types */
typedef uint64_t EMBENET_NetworkPrefix; ///< Network prefix - common first 8 bytes of nodes IPv6 Address

typedef uint16_t EMBENET_PANID; ///< IEEE802.15.4e PAN ID

/// Possible addressing modes
typedef enum {
  EMBENET_ADDRESSING_MODE_SINGLE, ///< Unicast addressing mode - the recipient is a single node
  EMBENET_ADDRESSING_MODE_GROUP,  ///< Multicast addressing mode - the recipients are all nodes within a group
} EMBENET_AddressingMode;

/* Network Encryption types */

typedef uint64_t
    EMBENET_RandomSeed; ///< Initial value of internal random number generators. USING NOT A RANDOM NUMBER WILL CAUSE A SERIOUS SECURITY VULNERABILITY

/// 128 bit pre-shared key used to authenticate Beacons
typedef struct {
  uint8_t val[16]; ///< value
} EMBENET_K1;

/// Constrained join 128-bit pre-shared key. This key should be unique and shared with JRC
typedef struct {
  uint8_t val[16]; ///< value
} EMBENET_PSK;

/// Structure describing the data necessary to perform a quick network rejoin
typedef struct {
  uint8_t reserved[52]; ///< reserved data
} EMBENET_NODE_QuickJoinCredentials;

/// Structure describing the embeNET version
typedef struct {
  uint8_t hi;   ///< High version number
  uint8_t lo;   ///< Low version number
  uint16_t rev; ///< Revision
} EMBENET_Version;

/** @} */

#ifdef __cplusplus
}
#endif

#endif // EMBENET_DEFS_H_
