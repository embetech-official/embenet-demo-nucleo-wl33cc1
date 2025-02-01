/**
 * @file
 * @license   commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.0.4
 * @purpose   embeNET PORT API
 * @brief     Capabilities of the EMBENET NODE Port
 */

#ifndef EMBENET_NODE_PORT_CAPABILITIES_H_
#define EMBENET_NODE_PORT_CAPABILITIES_H_

#ifdef __cplusplus
#include <cstdint>
#include <cstdlib>
#else
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#endif

#include "embenet_port/timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup embenet_node_port_capabilities Port Capabilities
 *
 * This interface allows to fetch port capabilities that the embeNET Node stack uses.
 *
 * @{
 */

/**
 * Forward declaration
 */
typedef struct EMBENET_Config EMBENET_Config;

/**
 * Capabilities getter, called ONCE at initialization.
 *
 * Capabilities templates are available.
 *
 * @return Not NULL, capability structure pointer.
 */
EMBENET_Config const *EMBENET_CAPABILITIES_Init(void);

/// @brief Template configuration structure for ~250 nodes topologies working in 863-870MHz band using SUN PHY OM1.
extern EMBENET_Config const *const embenetNodeConfigTemplate_863_870Mhz_250nodes;
/// @brief Template configuration structure for demos working in 863-870 band using SUN PHY OM1.
extern EMBENET_Config const *const embenetNodeConfigTemplate_863_870Mhz_10nodes_demo;
/// @brief Template configuration structure for ~1000 nodes topologies working in 2400-2480MHz band using BLE PHY.
extern EMBENET_Config const *const embenetNodeConfigTemplate_2400_2480Mhz_BLE_PHY_1000nodes;
/// @brief Template configuration structure for demos working in 2400-2480MHz band using BLE PHY.
extern EMBENET_Config const *const embenetNodeConfigTemplate_2400_2480Mhz_BLE_PHY_10nodes_demo;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* EMBENET_NODE_PORT_INTERFACE_EMBENET_PORT_CAPABILITIES_H_ */
