/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.2.1
 * @brief     EMBENET UDP IPv6 Abstraction
 */

#ifndef EMBENET_IPV6_H_
#define EMBENET_IPV6_H_

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup embenet_common embeNET common definitions
 *
 * IPv6 address types and helpers shared by embeNET components. For an explanation of the addressing scheme these
 * helpers implement, see @ref embenet_ipv6_addressing.
 *
 *  @{
 */

/**
 * @brief IPv6 network prefix.
 *
 * Common first 8 bytes of a node's IPv6 address in case of a unicast address.
 */
typedef uint64_t EMBENET_NetworkPrefix;

/**
 * @brief Unique identifier of the node.
 *
 * Last 8 bytes of a node's IPv6 address in case of a unicast address.
 */
typedef uint64_t EMBENET_EUI64;

/// @brief Invalid value of EMBENET_EUI64 used as an error indication.
#define EMBENET_EUI64_INVALID UINT64_C(0)

/// @brief Multicast group ID.
typedef uint16_t EMBENET_GroupId;

/// @brief Invalid value of EMBENET_GroupId used as an error indication.
#define EMBENET_GROUPID_INVALID ((EMBENET_GroupId)0U)

/// @brief IPv6 address representation.
typedef struct {
  /// @brief Stored value.
  uint8_t value[16]; // NOLINT(readability-magic-numbers) - fixed size array
} EMBENET_IPV6;

/**
 * @brief Assembles a unicast IPv6 address from a network prefix and node UID.
 *
 * @param[in] nwkPrefix Network prefix (upper 64 bits)
 * @param[in] uid       Unique Identifier of the node (lower 64 bits)
 *
 * @return Assembled unicast IPv6 address
 */
static inline EMBENET_IPV6 EMBENET_AssembleUnicastIpv6(EMBENET_NetworkPrefix nwkPrefix, EMBENET_EUI64 uid);

/**
 * @brief Assembles a multicast IPv6 address from a network prefix and group ID.
 *
 * The resulting address follows the RFC 3306 embedded-RP format:
 * @c FF34:0040:[prefix]:0000:[gid]
 *
 * @param[in] nwkPrefix Network prefix (embedded in the multicast address)
 * @param[in] gid       Multicast group ID
 *
 * @return Assembled multicast IPv6 address
 */
static inline EMBENET_IPV6 EMBENET_AssembleMulticastIpv6(EMBENET_NetworkPrefix nwkPrefix, EMBENET_GroupId gid);

/**
 * @brief Extracts the node UID from a unicast IPv6 address.
 *
 * @param[in] ipv6 Pointer to an IPv6 address
 *
 * @return Node UID (lower 64 bits of the address)
 */
static inline EMBENET_EUI64 EMBENET_GetUidFromIpv6(EMBENET_IPV6 const *ipv6);

/** @} */

/// @cond INTERNAL

/* Detect host byte order at compile time using well-known predefined macros. */
#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define EMBENET_UDP_BIG_ENDIAN_HOST 1
#endif
#elif defined(__BIG_ENDIAN__) || defined(_BIG_ENDIAN) || defined(__ARMEB__) || defined(__MIPSEB__)
#define EMBENET_UDP_BIG_ENDIAN_HOST 1
#endif

/* Use compiler builtins for byte-swap when available — generates a single instruction on most targets. */
#if defined(__has_builtin)
#if __has_builtin(__builtin_bswap64)
#define EMBENET_UDP_HAVE_BSWAP64 1
#endif
#if __has_builtin(__builtin_bswap16)
#define EMBENET_UDP_HAVE_BSWAP16 1
#endif
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
#define EMBENET_UDP_HAVE_BSWAP64 1
#define EMBENET_UDP_HAVE_BSWAP16 1
#endif

// NOLINTNEXTLINE(readability-magic-numbers)
enum {
  EMBENET_UDP_IPV6_IID_OFFSET = 8, /* byte offset of the Interface ID (EUI-64) within a 16-byte IPv6 address */
  EMBENET_UDP_MC_BYTE0 = 0xFF,     /* multicast prefix marker */
  EMBENET_UDP_MC_BYTE1 = 0x34,     /* flags=0011 (R=0,P=1,T=1), scope=4 (admin-local) */
  EMBENET_UDP_MC_BYTE3 = 0x40,     /* prefix length = 64 */
  EMBENET_UDP_MC_OFF_B0 = 0,
  EMBENET_UDP_MC_OFF_B1 = 1,
  EMBENET_UDP_MC_OFF_B3 = 3,
  EMBENET_UDP_MC_OFF_PFX = 4,
  EMBENET_UDP_MC_OFF_GID = 14,
};

static inline void EMBENET_UDP_hton64(uint8_t *dst, uint64_t val) {
#if defined(EMBENET_UDP_BIG_ENDIAN_HOST)
  memcpy(dst, &val, sizeof(val));
#elif defined(EMBENET_UDP_HAVE_BSWAP64)
  uint64_t swapped = __builtin_bswap64(val);
  memcpy(dst, &swapped, sizeof(swapped));
#else
  dst[0] = (uint8_t)(val >> 56u);
  dst[1] = (uint8_t)(val >> 48u);
  dst[2] = (uint8_t)(val >> 40u);
  dst[3] = (uint8_t)(val >> 32u);
  dst[4] = (uint8_t)(val >> 24u);
  dst[5] = (uint8_t)(val >> 16u);
  dst[6] = (uint8_t)(val >> 8u);
  dst[7] = (uint8_t)(val);
#endif
}

static inline uint64_t EMBENET_UDP_ntoh64(uint8_t const *src) {
#if defined(EMBENET_UDP_BIG_ENDIAN_HOST)
  uint64_t val;
  memcpy(&val, src, sizeof(val));
  return val;
#elif defined(EMBENET_UDP_HAVE_BSWAP64)
  uint64_t val;
  memcpy(&val, src, sizeof(val));
  return __builtin_bswap64(val);
#else
  return ((uint64_t)src[0] << 56u) | ((uint64_t)src[1] << 48u) | ((uint64_t)src[2] << 40u) | ((uint64_t)src[3] << 32u) | ((uint64_t)src[4] << 24u) |
         ((uint64_t)src[5] << 16u) | ((uint64_t)src[6] << 8u) | (uint64_t)src[7];
#endif
}

static inline void EMBENET_UDP_hton16(uint8_t *dst, uint16_t val) {
#if defined(EMBENET_UDP_BIG_ENDIAN_HOST)
  memcpy(dst, &val, sizeof(val));
#elif defined(EMBENET_UDP_HAVE_BSWAP16)
  uint16_t swapped = __builtin_bswap16(val);
  memcpy(dst, &swapped, sizeof(swapped));
#else
  dst[0] = (uint8_t)(val >> 8u);
  dst[1] = (uint8_t)(val);
#endif
}

static inline EMBENET_IPV6 EMBENET_AssembleUnicastIpv6(EMBENET_NetworkPrefix nwkPrefix, EMBENET_EUI64 uid) {
  EMBENET_IPV6 address;
  EMBENET_UDP_hton64(address.value, nwkPrefix);
  EMBENET_UDP_hton64(address.value + EMBENET_UDP_IPV6_IID_OFFSET, uid);
  return address;
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
static inline EMBENET_IPV6 EMBENET_AssembleMulticastIpv6(EMBENET_NetworkPrefix nwkPrefix, EMBENET_GroupId gid) {
  /*
   * Multicast address format:
   * FF34:0040:[prefix 64]:0000:[group 16]
   * byte[0]=0xFF, byte[1]=0x34 (flags=0011, scope=4 admin-local),
   * byte[3]=0x40 (plen=64), bytes[4..11]=prefix, bytes[14..15]=gid
   */
  EMBENET_IPV6 address = {0};
  address.value[EMBENET_UDP_MC_OFF_B0] = (uint8_t)EMBENET_UDP_MC_BYTE0;
  address.value[EMBENET_UDP_MC_OFF_B1] = (uint8_t)EMBENET_UDP_MC_BYTE1;
  address.value[EMBENET_UDP_MC_OFF_B3] = (uint8_t)EMBENET_UDP_MC_BYTE3;
  EMBENET_UDP_hton64(&address.value[EMBENET_UDP_MC_OFF_PFX], nwkPrefix);
  EMBENET_UDP_hton16(&address.value[EMBENET_UDP_MC_OFF_GID], gid);
  return address;
}

static inline EMBENET_EUI64 EMBENET_GetUidFromIpv6(EMBENET_IPV6 const *ipv6) {
  return EMBENET_UDP_ntoh64(ipv6->value + EMBENET_UDP_IPV6_IID_OFFSET);
}

/// @endcond

#ifdef __cplusplus
}
#endif

#endif // EMBENET_IPV6_H_
