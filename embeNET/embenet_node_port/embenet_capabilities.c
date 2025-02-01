/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     Definition of port capabilities for embeNET Node
 *
 * Contains set of parameters for DEMO and FULL version separately. Define EMBENET_NODE_DEMO_MODE=1 to set DEMO values.
 */

#include <embenet_port/capabilities.h>
#include <embenet_port/timer.h>


EMBENET_Config const *EMBENET_CAPABILITIES_Init(void) {
#if 0 != EMBENET_NODE_DEMO_MODE
  return embenetNodeConfigTemplate_863_870Mhz_10nodes_demo;
#else
  return embenetNodeConfigTemplate_863_870Mhz_250nodes;
#endif
}
