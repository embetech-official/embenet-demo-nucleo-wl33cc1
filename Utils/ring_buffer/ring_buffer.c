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

#include "embetech/ring_buffer.h"

bool RingBuffer_Init(RingBuffer *ringBuffer, uint8_t *dataBuffer, size_t dataBufferSize) {
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

bool RingBuffer_Clear(RingBuffer *ringBuffer) {
  if(ringBuffer) {
    ringBuffer->count = 0;
    ringBuffer->head = ringBuffer->dataBuffer;
    ringBuffer->tail = ringBuffer->dataBuffer;
    return true;
  }
  return false;
}

bool RingBuffer_IsEmpty(RingBuffer const *ringBuffer) {
  if(ringBuffer) {
    return (ringBuffer->count == 0);
  }

  return true;
}

size_t RingBuffer_GetLen(RingBuffer const *ringBuffer) {
  if(ringBuffer) {
    return ringBuffer->count;
  }
  return 0;
}

size_t RingBuffer_GetCapacity(RingBuffer const *ringBuffer) {
  if(ringBuffer) {
    return ringBuffer->dataBufferSize;
  }
  return 0;
}

size_t RingBuffer_GetSpace(RingBuffer const *ringBuffer) {
  if(ringBuffer) {
    return ringBuffer->dataBufferSize - ringBuffer->count;
  }
  return 0;
}

bool RingBuffer_PutChar(RingBuffer *ringBuffer, uint8_t c) {
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

bool RingBuffer_GetChar(RingBuffer *ringBuffer, uint8_t *c) {
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
