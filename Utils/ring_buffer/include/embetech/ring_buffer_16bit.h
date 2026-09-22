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

#ifndef RING_BUFFER_16BIT_H_
#define RING_BUFFER_16BIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/** @defgroup ring_buffer_16bit This module delivers a basic, general-purpose ring buffer.
 * @{
 */

/**
 * @brief Structure describing the 16-bit ring buffer.
 */
typedef struct {
  /// Pointer to the memory region used to store 16-bit buffer data.
  uint16_t *dataBuffer;

  /// Size of the data buffer in bytes.
  size_t dataBufferSize;

  /// Number of elements currently stored in the buffer.
  size_t count;

  /// Pointer to the next element position to be written.
  uint16_t *head;

  /// Pointer to the next element position to be read.
  uint16_t *tail;
} RingBuffer16Bit;

/**
 * @brief Initialize the given 16-bit ring buffer instance.
 *
 * @param[in] instance Pointer to a @ref RingBuffer16Bit structure.
 * @param[in] dataBuffer Pointer to memory where ring buffer data will be stored.
 * @param[in] dataBufferSize Size of `dataBuffer` in bytes.
 *
 * @return true if arguments are valid and initialization succeeds; false otherwise.
 */
bool RingBuffer16Bit_Init(RingBuffer16Bit *instance, uint16_t *dataBuffer, size_t dataBufferSize);

/**
 * @brief Clear contents of the given ring buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer16Bit structure.
 *
 * @return true if the ring buffer is cleared successfully; false otherwise.
 */
bool RingBuffer16Bit_Clear(RingBuffer16Bit *instance);

/**
 * @brief Check if the given ring buffer is empty.
 *
 * @param[in] instance Pointer to a @ref RingBuffer16Bit structure.
 *
 * @return true if the ring buffer holds no data; false otherwise.
 */
bool RingBuffer16Bit_IsEmpty(RingBuffer16Bit const *instance);

/**
 * @brief Get the length in bytes of data stored in the ring buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer16Bit structure.
 *
 * @return Length in bytes of the data stored in the ring buffer.
 */
size_t RingBuffer16Bit_GetLen(RingBuffer16Bit const *instance);

/**
 * @brief Get the capacity in bytes of the given buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer16Bit structure.
 *
 * @return Capacity in bytes of the ring buffer.
 */
size_t RingBuffer16Bit_GetCapacity(RingBuffer16Bit const *instance);

/**
 * @brief Get the remaining free space in bytes in the buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer16Bit structure.
 *
 * @return Free space in bytes available in the ring buffer.
 */
size_t RingBuffer16Bit_GetSpace(RingBuffer16Bit const *instance);

/**
 * @brief Append a single 16-bit value to the ring buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer16Bit structure.
 * @param[in] data 16-bit value to append.
 *
 * @return true if the value was added successfully; false otherwise.
 */
bool RingBuffer16Bit_PutChar(RingBuffer16Bit *instance, uint16_t data);

/**
 * @brief Retrieve a single 16-bit value from the ring buffer.
 *
 * @param[in] instance Pointer to a @ref RingBuffer16Bit structure.
 * @param[in,out] readData Pointer to where the read 16-bit value will be stored.
 *
 * @return true if the value was retrieved successfully; false otherwise.
 */
bool RingBuffer16Bit_GetChar(RingBuffer16Bit *instance, uint16_t *readData);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
