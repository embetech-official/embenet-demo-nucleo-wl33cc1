/**
 * @file
 * @license   commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.0.4
 * @purpose   embeNET API
 * @brief     embeNET IPv6 related utilities
*/

#ifndef EMBENET_IPV6_H_
#define EMBENET_IPV6_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup embenet_common embeNET common definitions
 *  @{
 */
typedef uint64_t EMBENET_NetworkPrefix; ///< Network prefix - common first 8 bytes of nodes IPv6 Address in case of unicast address

typedef uint64_t EMBENET_EUI64;           ///< Unique identifier of the node
#define EMBENET_EUI64_INVALID UINT64_C(0) ///< Invalid value of EMBENET_GroupId used as an error indication

typedef uint16_t EMBENET_GroupId;                     ///< Multicast group ID
#define EMBENET_GROUPID_INVALID (EMBENET_GroupId)(0U) ///< Invalid value of EMBENET_GroupId used as an error indication

/// IPv6 address
typedef struct {
  uint8_t value[16]; ///< Stored value
} EMBENET_IPV6;

/* Address conversion helper API */

/**
 * @brief Assembles Network prefix and Node's UID into IPv6 Address
 * @param nwkPrefix Network prefix
 * @param uid Unique Identifier (UID) of the node
 * @return IPv6 address
 */
EMBENET_IPV6 EMBENET_AssembleUnicastIpv6(EMBENET_NetworkPrefix nwkPrefix, EMBENET_EUI64 uid);

/**
 * @brief Assembles Network prefix and Multicast group ID into IPv6 Address
 * @param nwkPrefix Network prefix
 * @param gid Multicast group ID
 * @return IPv6 address
 */
EMBENET_IPV6 EMBENET_AssembleMulticastIpv6(EMBENET_NetworkPrefix nwkPrefix, EMBENET_GroupId gid);

/**
 * @brief Extracts UID from IPv6
 * @param ipv6 IPv6 address
 * @return UID
 */
EMBENET_EUI64 EMBENET_GetUidFromIpv6(EMBENET_IPV6 const *ipv6);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // EMBENET_DEFS_H_
