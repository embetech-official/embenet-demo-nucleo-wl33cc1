/**
 * @file
 * @license   MIT License
 * @copyright Embetech sp. z o.o.
 * @version   1.0.1
 * @purpose   General-purpose ring buffer
 * @brief     Ring Buffer implementation
 *
 * This module implements a basic, general-purpose ring buffer.
 */

#include "embetech/ring_buffer_16bit.h"

bool RingBuffer16Bit_Init(RingBuffer16Bit *ringBuffer, uint16_t *dataBuffer, size_t dataBufferSize) {
  if((ringBuffer) && (dataBuffer) && (dataBufferSize > 0)) {
    ringBuffer->dataBuffer = dataBuffer;
    ringBuffer->dataBufferSize = dataBufferSize;
    ringBuffer->count = 0;
    ringBuffer->head = dataBuffer;
    ringBuffer->tail = dataBuffer;
    return true;
  }

  return false;
}

bool RingBuffer16Bit_Clear(RingBuffer16Bit *ringBuffer) {
  if(ringBuffer) {
    ringBuffer->count = 0;
    ringBuffer->head = ringBuffer->dataBuffer;
    ringBuffer->tail = ringBuffer->dataBuffer;
    return true;
  }
  return false;
}

bool RingBuffer16Bit_IsEmpty(RingBuffer16Bit const *ringBuffer) {
  if(ringBuffer) {
    return (ringBuffer->count == 0);
  }

  return true;
}

size_t RingBuffer16Bit_GetLen(RingBuffer16Bit const *ringBuffer) {
  if(ringBuffer) {
    return ringBuffer->count;
  }
  return 0;
}

size_t RingBuffer16Bit_GetCapacity(RingBuffer16Bit const *ringBuffer) {
  if(ringBuffer) {
    return ringBuffer->dataBufferSize;
  }
  return 0;
}

size_t RingBuffer16Bit_GetSpace(RingBuffer16Bit const *ringBuffer) {
  if(ringBuffer) {
    return ringBuffer->dataBufferSize - ringBuffer->count;
  }
  return 0;
}

bool RingBuffer16Bit_PutChar(RingBuffer16Bit *ringBuffer, uint16_t c) {
  if((ringBuffer) && (ringBuffer->count < ringBuffer->dataBufferSize)) {
    *ringBuffer->head = c;
    ringBuffer->count++;
    ringBuffer->head++;
    if(ringBuffer->head >= ringBuffer->dataBuffer + ringBuffer->dataBufferSize) {
      ringBuffer->head = ringBuffer->dataBuffer;
    }
    return true;
  }
  return false;
}

bool RingBuffer16Bit_GetChar(RingBuffer16Bit *ringBuffer, uint16_t *c) {
  if((ringBuffer) && (c) && (ringBuffer->count)) {
    *c = *ringBuffer->tail;
    ringBuffer->count--;
    ringBuffer->tail++;
    if(ringBuffer->tail >= ringBuffer->dataBuffer + ringBuffer->dataBufferSize) {
      ringBuffer->tail = ringBuffer->dataBuffer;
    }
    return true;
  }
  return false;
}
