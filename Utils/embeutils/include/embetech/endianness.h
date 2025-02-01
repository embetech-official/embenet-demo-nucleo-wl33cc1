#ifndef EMBEUTILS_ENDIANNESS_H_
#define EMBEUTILS_ENDIANNESS_H_


#include <embetech/compiler_support.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Copies data from src into dst in reverse order
 * @param[in, out] dst pointer to memory region to store resulting data
 * @param[in] src data to be reversed
 * @param[in] length lenght of src
 * @note The memory region that dst points to MUST be at least length long, otherwise the behaviour is undefined
 * @note The memory region that dst points to MUST NOT overlap with memory region that src points to.
 */
static inline void ENDIANNESS_Reverse(void* dst, const void* src, size_t length) EMBEUTILS_INLINE EMBEUTILS_NONNULL();


/**
 * @brief Converts data from native endianness to big endian
 * @param[in, out] dst pointer to memory region to store resulting data
 * @param[in] src data to be converted
 * @param[in] length lenght of src
 * @note The memory region that dst points to MUST be at least length long, otherwise the behaviour is undefined
 * @note The memory region that dst points to MUST NOT overlap with memory region that src points to. *
 */
static inline void ENDIANNESS_NativeToBig(void* dst, const void* src, size_t length) EMBEUTILS_NONNULL();


/**
 * @brief Converts data from native endianness to little endian
 * @param[in, out] dst pointer to memory region to store resulting data
 * @param[in] src data to be converted
 * @param[in] length lenght of src
 * @note The memory region that dst points to MUST be at least length long, otherwise the behaviour is undefined
 * @note The memory region that dst points to MUST NOT overlap with memory region that src points to.
 *  */
static inline void ENDIANNESS_NativeToLittle(void* dst, const void* src, size_t length) EMBEUTILS_NONNULL();


/**
 * @brief Converts data from big endian to native endianness
 * @param[in, out] dst pointer to memory region to store resulting data
 * @param[in] src data to be converted
 * @param[in] length lenght of src
 * @note The memory region that dst points to MUST be at least length long, otherwise the behaviour is undefined
 * @note The memory region that dst points to MUST NOT overlap with memory region that src points to.
 *  */
static inline void ENDIANNESS_BigToNative(void* dst, const void* src, size_t length) EMBEUTILS_NONNULL();


/**
 * @brief Converts data from little endian to native endianness
 * @param[in, out] dst pointer to memory region to store resulting data
 * @param[in] src data to be converted
 * @param[in] length lenght of src
 * @note The memory region that dst points to MUST be at least length long, otherwise the behaviour is undefined
 * @note The memory region that dst points to MUST NOT overlap with memory region that src points to.
 */
static inline void ENDIANNESS_LittleToNative(void* dst, const void* src, size_t length) EMBEUTILS_NONNULL();


/**
 * @brief Converts 16-bit data from native endianness to network endianness
 * @param[in] host data to be converted
 * @return converted data
 */
static inline uint16_t ENDIANNESS_hton16(uint16_t host);


/**
 * @brief Converts 32-bit data from native endianness to network endianness
 * @param[in] host data to be converted
 * @return converted data
 */
static inline uint32_t ENDIANNESS_hton32(uint32_t host);


/**
 * @brief Converts 64-bit data from native endianness to network endianness
 * @param[in] host data to be converted
 * @return converted data
 */
static inline uint64_t ENDIANNESS_hton64(uint64_t host);


/**
 * @brief Converts 16-bit data from network endianness to native endianness
 * @param[in] host data to be converted
 * @return converted data
 */
static inline uint16_t ENDIANNESS_ntoh16(uint16_t network);


/**
 * @brief Converts 32-bit data from network endianness to native endianness
 * @param[in] host data to be converted
 * @return converted data
 */
static inline uint32_t ENDIANNESS_ntoh32(uint32_t network);


/**
 * @brief Converts 64-bit data from network endianness to native endianness
 * @param[in] host data to be converted
 * @return converted data
 */
static inline uint64_t ENDIANNESS_ntoh64(uint64_t network);


static inline void ENDIANNESS_Reverse(void* dst, const void* src, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        ((uint8_t*)dst)[length - 1 - i] = ((const uint8_t*)src)[i];
    }
}


static inline void ENDIANNESS_NativeToBig(void* dst, const void* src, size_t length) {
#ifdef EMBEUTILS_BIG_ENDIAN
    memcpy(dst, src, length);
#else
    ENDIANNESS_Reverse(dst, src, length);
#endif
}


static inline void ENDIANNESS_NativeToLittle(void* dst, const void* src, size_t length) {
#ifdef EMBEUTILS_BIG_ENDIAN
    ENDIANNESS_Reverse(dst, src, length);
#else
    memcpy(dst, src, length);
#endif
}


static inline void ENDIANNESS_BigToNative(void* dst, const void* src, size_t length) {
#ifdef EMBEUTILS_BIG_ENDIAN
    memcpy(dst, src, length);
#else
    ENDIANNESS_Reverse(dst, src, length);
#endif
}


static inline void ENDIANNESS_LittleToNative(void* dst, const void* src, size_t length) {
#ifdef EMBEUTILS_BIG_ENDIAN
    ENDIANNESS_Reverse(dst, src, length);
#else
    memcpy(dst, src, length);
#endif
}


static inline uint8_t ENDIANNESS_hton8(uint8_t host) {
    return host;
}


static inline uint16_t ENDIANNESS_hton16(uint16_t host) {
    uint16_t network;
    ENDIANNESS_NativeToBig(&network, &host, sizeof(host));
    return network;
}


static inline uint32_t ENDIANNESS_hton32(uint32_t host) {
    uint32_t network;
    ENDIANNESS_NativeToBig(&network, &host, sizeof(host));
    return network;
}


static inline uint64_t ENDIANNESS_hton64(uint64_t host) {
    uint64_t network;
    ENDIANNESS_NativeToBig(&network, &host, sizeof(host));
    return network;
}


static inline uint8_t ENDIANNESS_ntonh(uint8_t network) {
    return network;
}


static inline uint16_t ENDIANNESS_ntoh16(uint16_t network) {
    uint16_t host;
    ENDIANNESS_BigToNative(&host, &network, sizeof(host));
    return host;
}


static inline uint32_t ENDIANNESS_ntoh32(uint32_t network) {
    uint32_t host;
    ENDIANNESS_BigToNative(&host, &network, sizeof(host));
    return host;
}


static inline uint64_t ENDIANNESS_ntoh64(uint64_t network) {
    uint64_t host;
    ENDIANNESS_BigToNative(&host, &network, sizeof(host));
    return host;
}


#if __STDC_VERSION__ >= 201112L
#    define ENDIANNESS_hton(X) _Generic((X), uint16_t: ENDIANNESS_hton16, uint32_t: ENDIANNESS_hton32, uint64_t: ENDIANNESS_hton64)(X)

#    define ENDIANNESS_ntoh(X) _Generic((X), uint16_t: ENDIANNESS_ntoh16, uint32_t: ENDIANNESS_ntoh32, uint64_t: ENDIANNESS_ntoh64)(X)
#endif

#ifdef __cplusplus
}
#endif


#endif /* EMBENET_NODE_ENDIANNESS_H_ */
