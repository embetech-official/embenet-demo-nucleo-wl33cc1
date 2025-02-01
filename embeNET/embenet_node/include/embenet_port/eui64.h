/**
 * @file
 * @license   commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.0.4
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
 * This interface allows to read a hardware-dependent 64-bit extended unique device identifier.
 * @{
 */

/**
 * @brief Reads the 64-bit Extended Unique Identifier (EUI-64) of the device
 *
 * @retval 64-bit Extended Unique Identifier (EUI-64) of the device or zero if the EUI was not read
 */
uint64_t EMBENET_EUI64_Get(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
