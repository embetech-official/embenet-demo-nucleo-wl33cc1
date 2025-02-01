/**
 * @file
 * @license   commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.0.4
 * @purpose   embeNET PORT API
 * @brief     Interface for stack buffers allocation
 */

#ifndef EMBENET_NODE_PORT_ALLOCATOR_H_
#define EMBENET_NODE_PORT_ALLOCATOR_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup embenet_node_port_alloc
 *
 * This is interface to the memory allocation. This interface does not enforce the use of dynamically allocated memory. The memory pool may be
 * provided as static buffer.
 * @{
 */

/**
 * @brief Memory allocation function for stack buffers.
 *
 * This function is called ONCE on initialization stage @ref EMBENET_NODE_Init.
 *
 * @param[in] size size of memory to allocate
 * @return pointer to memory with alignment of alignof(max_align_t)
 */
void *EMBENET_ALLOCATOR_Alloc(size_t size);

/**
 * @brief Memory deallocation function for stack buffers.
 *
 * This function is called ONCE on stack deinitialization stage @ref EMBENET_NODE_Deinit
 *
 * @param[in] pool memory pool pointer, value returned by @ref EMBENET_ALLOCATOR_Alloc
 */
void EMBENET_ALLOCATOR_Free(void *pool);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // EMBENET_NODE_PORT_ALLOCATOR_H_
