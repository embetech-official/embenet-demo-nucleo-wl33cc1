/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
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
 * @brief Opaque stack configuration structure. Defined internally by the stack; do not access directly.
 */
typedef struct EMBENET_Config EMBENET_Config;

/**
 * @brief Returns the port-specific stack configuration.
 *
 * Called exactly once during @ref EMBENET_NODE_Init. The returned pointer must remain valid for the
 * lifetime of the stack (until @ref EMBENET_NODE_Deinit). Pre-defined configuration templates are
 * available as an alternative to writing a custom implementation (see below).
 *
 * @return Pointer to the configuration structure; must not be NULL.
 */
EMBENET_Config const *EMBENET_CAPABILITIES_Init(void);

/// Template configuration for networks of up to ~250 nodes operating in the 863–870 MHz band using SUN PHY OM1.
extern EMBENET_Config const *const embenetNodeConfigTemplate_863_870Mhz_250nodes;
/// Template configuration for demo networks of up to ~10 nodes operating in the 863–870 MHz band using SUN PHY OM1.
extern EMBENET_Config const *const embenetNodeConfigTemplate_863_870Mhz_10nodes_demo;
/// Template configuration for networks of up to ~1000 nodes operating in the 2400–2480 MHz band using BLE PHY.
extern EMBENET_Config const *const embenetNodeConfigTemplate_2400_2480Mhz_BLE_PHY_1000nodes;
/// Template configuration for demo networks of up to ~10 nodes operating in the 2400–2480 MHz band using BLE PHY.
extern EMBENET_Config const *const embenetNodeConfigTemplate_2400_2480Mhz_BLE_PHY_10nodes_demo;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* EMBENET_NODE_PORT_INTERFACE_EMBENET_PORT_CAPABILITIES_H_ */
