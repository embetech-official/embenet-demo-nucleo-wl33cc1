/**
 * @file
 * @license   commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   ENMS service
 * @brief     ENMS BR service API
 */

#ifndef ENMS_BR_H_
#define ENMS_BR_H_

#include <embenet/enms_common.h>
#include <embenet/udp.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup enms_br ENMS BorderRouter API
 *
 * @{ */

/// Structure with user-defined callbacks that handle received information
typedef struct {
  /// Callback that will be called when ENMS-BASIC-INFO is received
  void (*onBasicNodeInfoReceived)(const EMBENET_IPV6 *senderAddr, ENMS_BasicNodeInfo const *basicNodeInfo);
  /// Callback that will be called when ENMS-SERVICE-INFO is received
  void (*onServiceInfoReceived)(const EMBENET_IPV6 *senderAddr, ENMS_ServiceInfo const *serviceInfo, uint8_t serviceCount);
  /// Callback that will be called when ENMS-STATUS is received
  void (*onStatusReceived)(const EMBENET_IPV6 *senderAddr, ENMS_StatusInfo const *status, uint16_t const *groups, size_t groupsCount);
  /// Callback that will be called when ENMS-NEIGHBORHOOD is received
  void (*onNeighborhoodReceived)(const EMBENET_IPV6 *senderAddr, ENMS_NeighborInfo const *neighbors, size_t neighborsCount, size_t packetNumber,
                                 size_t packetsTotal);
  /// Callback that will be called when ENMS-CELLS is received
  void (*onCellsReceived)(const EMBENET_IPV6 *senderAddr, ENMS_CellInfo const *cellInfo, size_t cellsCount, size_t packetNumber, size_t packetsTotal);
} EnmsBrEventHandlers;

/** Structure defining the ENMS BorderRouter service instance */
typedef struct {
  /// UDP socket descriptor
  EMBENET_UDP_SocketDescriptor udpSocket;
  /// Structure with user-defined callbacks that handle received information
  EnmsBrEventHandlers eventHandlers;
} EnmsBr;

/**
 * Initializes the ENMS BorderRouter service.
 *
 * @param[in] enmsBr ENMS BorderRouter service instance
 * @param[in] port UDP port number over which the service will communicate, provide 0 to use default port value 0xF0B1
 * @param[in] eventHandlers structure holding callbacks that will be called on specific ENMS events (see @ref EnmsBrEventHandlers)
 *
 * @retval ENMS_RESULT_OK if the service was initialized successfully
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval ENMS_RESULT_FAILED_TO_REGISTER_UDP_SOCKET if the service failed to register and UDP socket and thus was unable to start
 */
EnmsResult ENMS_BR_Init(EnmsBr *enmsBr, uint16_t port, EnmsBrEventHandlers const *eventHandlers);

/**
 * Deinitializes the ENMS BorderRouter service
 *
 * @param[in] enmsBr ENMS BorderRouter service instance
 *
 * @retval ENMS_RESULT_OK if the service was deinitialized successfully
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 */
EnmsResult ENMS_BR_Deinit(EnmsBr *enmsBr);

/**
 * Queries the remote node for basic information
 *
 * @param[in] enmsBr ENMS BorderRouter service instance
 * @param[in] destinationAddress IPv6 address of the destination node (can be a multicast address)
 *
 * @retval ENMS_RESULT_OK if the query was sent
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval ENMS_RESULT_FAILED_TO_SEND_PACKET if the service failed to send out a query packet through UDP
 */
EnmsResult ENMS_BR_QueryBasicInfo(EnmsBr *enmsBr, const EMBENET_IPV6 *destinationAddress);

/**
 * Queries the remote node for information about a given service
 *
 * @param[in] enmsBr ENMS BorderRouter service instance
 * @param[in] destinationAddress IPv6 address of the destination node (can be a multicast address)
 * @param[in] serviceNo service number
 *
 * @retval ENMS_RESULT_OK if the query was sent
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval ENMS_RESULT_FAILED_TO_SEND_PACKET if the service failed to send out a query packet through UDP
 */
EnmsResult ENMS_BR_QueryServiceInfo(EnmsBr *enmsBr, const EMBENET_IPV6 *destinationAddress, uint8_t serviceNo);

/**
 * Queries the remote node for status
 *
 * @param[in] enmsBr ENMS BorderRouter service instance
 * @param[in] destinationAddress IPv6 address of the destination node (can be a multicast address)
 *
 * @retval ENMS_RESULT_OK if the query was sent
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval ENMS_RESULT_FAILED_TO_SEND_PACKET if the service failed to send out a query packet through UDP
 */
EnmsResult ENMS_BR_QueryStatus(EnmsBr *enmsBr, const EMBENET_IPV6 *destinationAddress);

/**
 * Queries the remote node for neighborhood info
 *
 * @param[in] enmsBr ENMS BorderRouter service instance
 * @param[in] destinationAddress IPv6 address of the destination node (can be a multicast address)
 *
 * @retval ENMS_RESULT_OK if the query was sent
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval ENMS_RESULT_FAILED_TO_SEND_PACKET if the service failed to send out a query packet through UDP
 */
EnmsResult ENMS_BR_QueryNeighborhood(EnmsBr *enmsBr, const EMBENET_IPV6 *destinationAddress);

/**
 * Queries the remote node for cells info
 *
 * @param[in] enmsBr ENMS BorderRouter service instance
 * @param[in] destinationAddress IPv6 address of the destination node (can be a multicast address)
 *
 * @retval ENMS_RESULT_OK if the query was sent
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval ENMS_RESULT_FAILED_TO_SEND_PACKET if the service failed to send out a query packet through UDP
 */
EnmsResult ENMS_BR_QueryCells(EnmsBr *enmsBr, const EMBENET_IPV6 *destinationAddress);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* ENMS_BR_H_ */
