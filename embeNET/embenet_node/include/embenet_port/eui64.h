/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET PORT API
 * @brief     EUI64 interface for the EMBENET NODE Port
 */

#ifndef EMBENET_NODE_PORT_EUI64_H_
#define EMBENET_NODE_PORT_EUI64_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup embenet_node_port_eui64 64-bit Extended Unique Identifier (EUI-64) Interface
 *
 * This interface reads the hardware-assigned 64-bit Extended Unique Identifier (EUI-64) of the device.
 * The value is used as the node's network identity and must be globally unique.
 * @{
 */

/**
 * @brief Returns the device's EUI-64 hardware identifier.
 *
 * @return EUI-64 of the device, or 0 if the identifier could not be read from hardware.
 */
uint64_t EMBENET_EUI64_Get(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
