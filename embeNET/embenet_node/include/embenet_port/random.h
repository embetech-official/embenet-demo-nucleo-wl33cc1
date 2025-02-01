/**
 * @file
 * @license   commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.0.4
 * @purpose   embeNET PORT API
 * @brief     Random number generator interface for the EMBENET NODE Port
 */

#ifndef EMBENET_NODE_PORT_RANDOM_H_
#define EMBENET_NODE_PORT_RANDOM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup embenet_node_port_random Random Number Generator Interface
 *
 * Provides an interface to the random number generator used by the embeNET Node stack.
 * @{
 */

/**
 * @brief Gets a random number in range [0, UINT32_MAX]
 *
 * This function should return a TRUE random 32-bit number.
 */
uint32_t EMBENET_RANDOM_Get(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
