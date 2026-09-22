/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET API
 * @brief     embeNET Node's own realization of the embenet_udp interface's functions - see embenet/udp.h.
 * @note      This is the implementation a udp_port shim (see ../../udp_port) forwards EMBENET_UDP_* to when
 *            selected as embenet::udp_port; embeNET Node itself no longer defines EMBENET_UDP_* directly, so
 *            that name stays free for whichever backend a consumer actually links (e.g. a different node
 *            instance's own shim, or another repository entirely).
 */
#pragma once
#ifndef EMBENET_NODE_UDP_H_
#define EMBENET_NODE_UDP_H_

#include <embenet/udp.h>

#ifdef __cplusplus
extern "C" {
#endif

EMBENET_UDP_Result EMBENET_NODE_RegisterSocket(EMBENET_UDP_SocketDescriptor *descriptor);

EMBENET_UDP_Result EMBENET_NODE_UnregisterSocket(EMBENET_UDP_SocketDescriptor *descriptor);

EMBENET_UDP_Result EMBENET_NODE_Send(EMBENET_UDP_SocketDescriptor const *socket, EMBENET_IPV6 const *dstAddress, uint16_t dstPort,
                                         void const *data, size_t dataSize);

size_t EMBENET_NODE_GetMaxDataSize(EMBENET_UDP_SocketDescriptor const *socket);

#ifdef __cplusplus
}
#endif

#endif // EMBENET_NODE_UDP_H_
