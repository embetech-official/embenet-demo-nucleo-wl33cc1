/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     Implementation of the memory allocator for embeNET Node
 */

#include <embenet_port/allocator.h>
#include <stdalign.h>
#include <stdint.h>

static alignas(max_align_t) uint8_t pool[16008];

void *EMBENET_ALLOCATOR_Alloc(size_t size) {
  // demo configuration xxxxB
  // 1000 nodes configuration 15368B
  if(sizeof(pool) >= size)
    return pool;
  else
    return NULL;
}

void EMBENET_ALLOCATOR_Free(void *pool) { (void)pool; }
