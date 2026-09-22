/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
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
 * @addtogroup embenet_node_port_alloc Memory Allocator Interface
 *
 * Interface for stack buffer allocation. Implementations are not required to use dynamic memory;
 * a static buffer is a valid and common approach.
 * @{
 */

/**
 * @brief Allocates the stack's internal memory buffer.
 *
 * Called exactly once during @ref EMBENET_NODE_Init. The returned pointer must remain valid until
 * @ref EMBENET_ALLOCATOR_Free is called.
 *
 * @param[in] size number of bytes to allocate
 *
 * @return Pointer to a memory block of at least @p size bytes with alignment of @c alignof(max_align_t);
 *         must not be NULL.
 */
void *EMBENET_ALLOCATOR_Alloc(size_t size);

/**
 * @brief Releases the stack's internal memory buffer.
 *
 * Called exactly once during @ref EMBENET_NODE_Deinit with the pointer previously returned by
 * @ref EMBENET_ALLOCATOR_Alloc.
 *
 * @param[in] pool pointer returned by @ref EMBENET_ALLOCATOR_Alloc; must not be NULL.
 */
void EMBENET_ALLOCATOR_Free(void *pool);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // EMBENET_NODE_PORT_ALLOCATOR_H_
