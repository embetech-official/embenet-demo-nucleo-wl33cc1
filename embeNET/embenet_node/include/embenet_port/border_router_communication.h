/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
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
 * This interface is used only by root instances of the embeNET Node. It provides the means to communicate with the embeNET Border Router,
 * typically over a UART or other serial connection.
 * @{
 */

/**
 * @brief Initializes the border router communication module.
 */
void EMBENET_BRT_Init(void);

/**
 * @brief Deinitializes the border router communication module.
 */
void EMBENET_BRT_Deinit(void);

/**
 * @brief Sends a framed data packet to the border router.
 *
 * @param[in] packet       pointer to the packet data; must not be NULL.
 * @param[in] packetLength length of the packet in bytes; must be greater than 0.
 */
void EMBENET_BRT_Send(void const *packet, size_t packetLength);

/**
 * @brief Receives a framed data packet from the border router (non-blocking).
 *
 * If a complete packet is available and fits in @p packetBuffer, it is copied into the buffer and its size is returned.
 * If the available packet is larger than @p packetBufferSize, no data is copied and 0 is returned.
 * If no packet is available, 0 is returned.
 *
 * @param[out] packetBuffer     buffer to store the received packet; must not be NULL.
 * @param[in]  packetBufferSize size of @p packetBuffer in bytes.
 *
 * @return Number of bytes written into @p packetBuffer, or 0 if no packet was available or the buffer was too small.
 */
size_t EMBENET_BRT_Receive(void *packetBuffer, size_t packetBufferSize);

/**
 * @brief Sends raw (unframed) data to the border router.
 *
 * @param[in] data       pointer to the data buffer; must not be NULL.
 * @param[in] dataLength number of bytes to send; must be greater than 0.
 */
void EMBENET_BRT_SendRaw(void const *data, size_t dataLength);

/**
 * @brief Receives raw (unframed) data from the border router (non-blocking).
 *
 * If data is available and fits in @p data, it is copied and its size is returned.
 * If the available data is larger than @p dataBufferSize, no data is copied and 0 is returned.
 * If no data is available, 0 is returned.
 *
 * @param[out] data           buffer to store the received data; must not be NULL.
 * @param[in]  dataBufferSize size of @p data in bytes.
 *
 * @return Number of bytes written into @p data, or 0 if no data was available or the buffer was too small.
 */
size_t EMBENET_BRT_ReceiveRaw(void *data, size_t dataBufferSize);

/**
 * @brief Requests a device reset via the border router communication module.
 */
void EMBENET_BRT_Reset(void);

/**
 * @brief Checks whether the border router communication module is busy.
 *
 * @retval true  the module is busy (e.g. a transmission is in progress)
 * @retval false the module is idle and ready for a new operation
 */
bool EMBENET_BRT_IsBusy(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
