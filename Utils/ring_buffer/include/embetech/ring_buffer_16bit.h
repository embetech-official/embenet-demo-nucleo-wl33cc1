/**
 * @file
 * @license   MIT License
 * @copyright Embetech sp. z o.o.
 * @version   1.0.1
 * @purpose   General-purpose ring buffer
 * @brief     Ring Buffer API
 * 
 * This module implements a basic, general-purpose ring buffer.
 */

#ifndef RING_BUFFER_16BIT_H_
#define RING_BUFFER_16BIT_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/** @defgroup ring_buffer_16bit This module delivers a basic, general-purpose ring buffer.
 * @{
 */

/** Structure describing the ring buffer. */
typedef struct {
  /// pointer to the area of memory, where data will be stored
  uint16_t *dataBuffer;
  /// size of the data buffer (in bytes)
  size_t dataBufferSize;
  /// number of elements currently stored within the buffer
  size_t count;
  /// pointer to the next element in the buffer that will be written
  uint16_t *head;
  /// pointer to the next element in the buffer that will be read
  uint16_t *tail;
} RingBuffer16Bit;

/**
 * Initializes the given ring buffer structure.
 *
 * @param RingBuffer16Bit pointer to a \ref RingBuffer16Bit structure
 * @param dataBuffer pointer to a location in memory, where the ring buffer data will be stored
 * @param dataBufferSize size in bytes of the dataBuffer
 * @return true if all arguments are valid and the ring buffer is initialized successfully, false otherwise
 */
bool RingBuffer16Bit_Init(RingBuffer16Bit *RingBuffer16Bit, uint16_t *dataBuffer, size_t dataBufferSize);

/**
 * Clears contents of the given ring buffer.
 *
 * @param RingBuffer16Bit pointer to a \ref RingBuffer16Bit structure
 * @return true if the ring buffer is cleared successfully, false otherwise
 */
bool RingBuffer16Bit_Clear(RingBuffer16Bit *RingBuffer16Bit);

/**
 * Checks if the given ring buffer is empty.
 *
 * @param RingBuffer16Bit pointer to a \ref RingBuffer16Bit structure
 * @return true if the ring buffer holds no data, false otherwise
 */
bool RingBuffer16Bit_IsEmpty(RingBuffer16Bit const *RingBuffer16Bit);

/**
 * Gets the length (in bytes) of the data stored in the given ring buffer.
 *
 * @param RingBuffer16Bit pointer to a \ref RingBuffer16Bit structure
 * @return length (in bytes) of the data stored in the ring buffer
 */
size_t RingBuffer16Bit_GetLen(RingBuffer16Bit const *RingBuffer16Bit);

/**
 * Returns the capacity (in bytes) of the given buffer.
 *
 * @param RingBuffer16Bit pointer to a \ref RingBuffer16Bit structure
 * @return capacity (in bytes) of the ring buffer (how much characters can it store)
 */
size_t RingBuffer16Bit_GetCapacity(RingBuffer16Bit const *RingBuffer16Bit);

/**
 * Returns the space (in bytes) left in the given buffer.
 *
 * @param RingBuffer16Bit pointer to a \ref RingBuffer16Bit structure
 * @return space (in bytes) of the ring buffer (how much characters can be still written to it)
 */
size_t RingBuffer16Bit_GetSpace(RingBuffer16Bit const *RingBuffer16Bit);

/**
 * Appends a single character to the ring buffer. The stored data length will be
 * increased by 1.
 *
 * @param RingBuffer16Bit pointer to a \ref RingBuffer16Bit structure
 * @param c character to append
 * @return true if the character was added successfully, false otherwise
 */
bool RingBuffer16Bit_PutChar(RingBuffer16Bit *RingBuffer16Bit, uint16_t c);

/**
 * Pulls out a single character from the ring buffer. The stored data length will be
 * decreased by 1.
 *
 * @param RingBuffer16Bit pointer to a \ref RingBuffer16Bit structure
 * @param c pointer to a place where character will be stored
 * @return true if the character was pulled out successfully, false otherwise
 */
bool RingBuffer16Bit_GetChar(RingBuffer16Bit *RingBuffer16Bit, uint16_t *c);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
