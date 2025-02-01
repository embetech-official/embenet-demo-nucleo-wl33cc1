/**
 * @file
 * @license   commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.0.4
 * @purpose   embeNET PORT API
 * @brief     Border router communication interface for the EMBENET NODE Port
 */

#ifndef EMBENET_NODE_PORT_BORDER_ROUTER_COMMUNICATION_H_
#define EMBENET_NODE_PORT_BORDER_ROUTER_COMMUNICATION_H_

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup embenet_node_port_brt Border Router Communication Interface
 *
 * This interface is only used for root instances of the embeNET Node. It provides means to communicate with the embeNET Border Router.
 * The communication is usually done using UART or other serial connection.
 * @{
 */

/**
 * @brief Module initialization.
 */
void EMBENET_BRT_Init(void);

/**
 * @brief Module deinitialization.
 */
void EMBENET_BRT_Deinit(void);

/**
 * @brief 		Sends data packet to LBR.
 * @param[in] 	packet data as byte-oriented buffer
 * @param[in] 	packetLength in bytes
 */
void EMBENET_BRT_Send(void const *packet, size_t packetLength);

/**
 * @brief 		Receives data, non-polling function.
 * @param[out] 	packetBuffer to store data to
 * @param[in] 	packetBufferSize
 * @return 		size of packet in bytes, if provided buffer is to short, 0 is returned and no data is copied
 */
size_t EMBENET_BRT_Receive(void *packetBuffer, size_t packetBufferSize);

/**
 * @brief 		Sends raw data to LBR.
 * @param[in] 	data data as byte-oriented buffer
 * @param[in] 	dataLength data length in bytes
 */
void EMBENET_BRT_SendRaw(void const *data, size_t dataLength);

/**
 * @brief 		Receives raw data, non-polling function.
 * @param[out] 	data buffer to store data to
 * @param[in] 	dataBufferSize
 * @return 		size of packet in bytes, if provided buffer is to short, 0 is returned and no data is copied
 */
size_t EMBENET_BRT_ReceiveRaw(void *data, size_t dataBufferSize);

/**
 * @brief Called by BRT module to reset device.
 */
void EMBENET_BRT_Reset(void);

/**
 * @brief Called by BRT module to check if device is busy.
 * @return true if device is busy, false otherwise
 */
bool EMBENET_BRT_IsBusy(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
