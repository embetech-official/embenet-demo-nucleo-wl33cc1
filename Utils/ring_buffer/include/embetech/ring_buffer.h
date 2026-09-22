/**
 * @file
 * @license   MIT License
 * @copyright Embetech sp. z o.o.
 * @version   1.0.5
 * @purpose   General-purpose ring buffer
 * @brief     Ring Buffer API
 *
 * This module implements a basic, general-purpose ring buffer.
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/** @defgroup ring_buffer This module delivers a basic, general-purpose ring buffer.
 * @{
 */

/**
 * @brief Structure describing the ring buffer.
 */
typedef struct {
  /// Pointer to the memory region used to store buffer data.
  uint8_t *dataBuffer;

  /// Size of the data buffer in bytes.
  size_t dataBufferSize;

  /// Number of elements currently stored in the buffer.
  size_t count;

  /// Pointer to the next element position to be written.
  uint8_t *head;

  /// Pointer to the next element position to be read.
  uint8_t *tail;
} RingBuffer;

/**
 * @brief Initialize the given ring buffer instance.
 *
 * @param[in] instance Pointer to a @ref RingBuffer structure.
 * @param[in] dataBuffer Pointer to memory where ring buffer data will be stored.
 * @param[in] dataBufferSize Size of `dataBuffer` in bytes.
 *
 * @return true if arguments are valid and initialization succeeds; false otherwise.
 */
bool RingBuffer_Init(RingBuffer *instance, uint8_t *dataBuffer, size_t dataBufferSize);

/**
 * @brief Clear contents of the given ring buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer structure.
 *
 * @return true if the ring buffer is cleared successfully; false otherwise.
 */
bool RingBuffer_Clear(RingBuffer *instance);

/**
 * @brief Check if the given ring buffer is empty.
 *
 * @param[in] instance Pointer to a @ref RingBuffer structure.
 *
 * @return true if the ring buffer holds no data; false otherwise.
 */
bool RingBuffer_IsEmpty(RingBuffer const *instance);

/**
 * @brief Get the length in bytes of data stored in the ring buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer structure.
 *
 * @return Length in bytes of the data stored in the ring buffer.
 */
size_t RingBuffer_GetLen(RingBuffer const *instance);

/**
 * @brief Get the capacity in bytes of the given buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer structure.
 *
 * @return Capacity in bytes of the ring buffer.
 */
size_t RingBuffer_GetCapacity(RingBuffer const *instance);

/**
 * @brief Get the remaining free space in bytes in the buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer structure.
 *
 * @return Free space in bytes available in the ring buffer.
 */
size_t RingBuffer_GetSpace(RingBuffer const *instance);

/**
 * @brief Append a single character to the ring buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer structure.
 * @param[in] data Character to append.
 *
 * @return true if the character was added successfully; false otherwise.
 */
bool RingBuffer_PutChar(RingBuffer *instance, uint8_t data);

/**
 * @brief Retrieve a single character from the ring buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer structure.
 * @param[in,out] readData Pointer to where the read character will be stored.
 *
 * @return true if the character was retrieved successfully; false otherwise.
 */
bool RingBuffer_GetChar(RingBuffer *instance, uint8_t *readData);

/**
 * @brief Get library version as a NUL-terminated string.
 *
 * @return Pointer to a read-only, statically allocated string in semantic version format (e.g., "1.2.3+extra_info"). Must not be freed or modified.
 */
char const *RingBuffer_GetVersionString(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
