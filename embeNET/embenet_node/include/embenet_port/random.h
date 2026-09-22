/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
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
 * Provides an interface to the hardware or software random number generator used by the embeNET Node stack.
 * @{
 */

/**
 * @brief Returns a uniformly distributed random 32-bit value.
 *
 * The implementation should use a hardware TRNG where available. A cryptographically weak or predictable
 * source will degrade network security.
 *
 * @return Random value in the range [0, UINT32_MAX].
 */
uint32_t EMBENET_RANDOM_Get(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
