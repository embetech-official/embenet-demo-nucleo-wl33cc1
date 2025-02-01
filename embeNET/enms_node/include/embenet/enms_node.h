/**
 * @file
 * @license   commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   ENMS service
 * @brief     ENMS Node service API
 */

#ifndef ENMS_NODE_H_
#define ENMS_NODE_H_

#include <embenet/enms_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup enms_node ENMS Node API
 *
 * @{ */

#ifndef ENMS_NODE_MAX_SERVICES
#define ENMS_NODE_MAX_SERVICES 10 ///< Maximum number of services that can be registered
#endif

/**
 * Type capable of storing entire EnmsNode instance.
 * The alignment and size requirements are checked at compile time in appropriate source file.
 */
typedef struct {
  EMBEUTILS_ALIGNAS(8) uint8_t _[321];
} EnmsNode;

/** Structure describing indication sending policy */
typedef struct {
  uint32_t firstBasicInfoSendTimeSec; ///< After what time after ENMS service is started will the first BASIC-INFO.indication be sent
  /// How often will the subsequent BASIC-INFO.indications be sent
  uint32_t basicInfoSendPeriodSec;
  /// After what time after ENMS service is started will the first STATUS.indication be sent
  uint32_t firstStatusSendTimeSec;
  /// How often will the subsequent STATUS.indications be sent
  uint32_t statusSendPeriodSec;
  /// After what time after ENMS service is started will the first SERVICE-INFO.indication be sent
  uint32_t firstServiceInfoSendTimeSec;
  /// How often will the subsequent SERVICE.indications be sent
  uint32_t serviceInfoSendPeriodSec;
  /// After what time after ENMS service is started will the first NEIGHBORHOOD.indication be sent
  uint32_t firstNeighborhoodSendTimeSec;
  /// How often will the subsequent NEIGHBORHOOD.indications be sent
  uint32_t neighborhoodSendPeriodSec;
  /// After what time after ENMS service is started will the first CELLS.indication be sent
  uint32_t firstCellsSendTimeSec;
  /// How often will the subsequent CELLS.indications be sent
  uint32_t cellsSendPeriodSec;
} EnmsIndicationPolicy;

/**
 * @brief Initializes the ENMS Node service.
 *
 * This function initializes the ENMS Node service. It registers a UDP socket for communication with the ENMS BR service running typically in the
 * border router. It also creates a task that is responsible for periodic sending of ENSM-BASIC-INFO messages.
 *
 * @param[in] enmsNode ENMS Node service instance, not NULL
 * @param[in] port UDP port number over which the service will communicate, not 0, use @ref ENMS_NODE_GetDefaultPort to provide default port
 * @param[in] hwId hardware identifier, not NULL
 * @param[in] indicationPolicy indication policy defining when and how often the service messages should be sent. You may implement your own policy or
 * use one of the built-in policies: @ref ENMS_NODE_GetLargeScalePolicy, @ref ENMS_NODE_GetSmallScalePolicy. Not NULL.
 *
 * @retval ENMS_RESULT_OK if the service was initialized successfully
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval ENMS_RESULT_FAILED_TO_REGISTER_UDP_SOCKET if the service failed to register a UDP socket
 * @retval ENMS_RESULT_FAILED_TO_CREATE_TASK if the service failed to create a task
 */
EnmsResult ENMS_NODE_Init(EnmsNode *enmsNode, uint16_t port, uint8_t const hwId[16], EnmsIndicationPolicy const *indicationPolicy);

/**
 * Returns the built-in ENMS Node indication policy for large scale networks.
 *
 * @return pointer to the policy
 */
EnmsIndicationPolicy const *ENMS_NODE_GetLargeScalePolicy(void);

/**
 *  Returns the built-in ENMS Node indication policy for small scale networks.
 *
 * @return pointer to the policy
 */
EnmsIndicationPolicy const *ENMS_NODE_GetSmallScalePolicy(void);

/**
 * Returns default ENMS service port: 0xf0b1 (61617).
 *
 * @return 0xf0b1 (61617)
 */
uint16_t ENMS_NODE_GetDefaultPort(void);

/**
 * Deinitialize the ENMS Node service.
 *
 * The function frees all embeNET Node resources, that were acquired during the service initialization (i.e. sockets, tasks).
 *
 * Calling this function is mandatory before the service instance is destroyed.
 *
 * @param[in] enmsNode ENMS Node service instance
 *
 * @retval ENMS_RESULT_OK if the service was deinitialized successfully
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 */
EnmsResult ENMS_NODE_Deinit(EnmsNode *enmsNode);

/**
 * Start the ENMS Node service.
 *
 * Starts the periodic task of the ENMS Node service.
 * In result, the service will be periodically sending service-specific messages over the network.
 * It is typically called in reaction to the event that the node has joined a network.
 *
 * The service can be stopped using @ref ENMS_NODE_Stop.
 * Calling the function on the already started service is allowed, and will have no effect.
 *
 * The function MUST be called on the initialized service instance. Otherwise, the behavior is undefined.
 *
 * @param[in] enmsNode ENMS Node service instance
 *
 * @retval ENMS_RESULT_OK if the service was started successfully
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval ENMS_RESULT_FAILED_TO_RUN_TASK if the service was unable to run a task. The service remains stopped
 */
EnmsResult ENMS_NODE_Start(EnmsNode *enmsNode);

/**
 * Stop the ENMS Node service.
 *
 * Stops the periodic task of the ENMS Node service.
 * In result, the service will no longer send any messages.
 * This function is typically called in reaction to the event that the node has left a network.
 *
 * The service can be resumed using @ref ENMS_NODE_Start.
 * Calling the function on the already stopped service is allowed, and will have no effect.
 *
 * The function MUST be called on the initialized service instance. Otherwise, the behavior is undefined.
 *
 * @param[in] enmsNode ENMS Node service instance
 *
 * @retval ENMS_RESULT_OK if the service service is stopped
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 */
EnmsResult ENMS_NODE_Stop(EnmsNode *enmsNode);

/**
 * Register a service.
 *
 * Indicates to the ENMS Node service that the service is running in the node.
 * As the result, the internal service descriptor is locked and cannot be reused until the service is deregistered (@ref ENMS_NODE_UnregisterService),
 * or entire component is reinitialized.
 *
 * All of the provided arguments shall be non-null, otherwise the function will return @ref ENMS_RESULT_INVALID_ARGUMENT.
 * Additional restrictions apply to the service name - The service name shall be a non-empty string, not longer than @ref
 * ENMS_NODE_SERVICE_NAME_MAX_LENGTH
 *
 * The service API does not depend on whether the service is started. Calling this function is permitted always, provided the enmsNode is initialized
 *
 * The function will check, whether the service with given name is already registered. If so, the function will return @ref
 * ENMS_RESULT_SERVICE_ALREADY_REGISTERED.
 *
 * @param[in] enmsNode ENMS Node service instance
 * @param[in] serviceName name of the service to be registered
 * @param[in] initialServiceState initial state of the service (the meaning of this field is user-defined)
 *
 * @retval ENMS_RESULT_OK if the service was registered
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval ENMS_RESULT_SERVICE_ALREADY_REGISTERED if the service is already registered
 * @retval ENMS_RESULT_FAILED_TO_REGISTER_SERVICE if the service was not registered (probably exceeded the number of services that can be handled
 * - see @ref ENMS_NODE_MAX_SERVICES)
 */
EnmsResult ENMS_NODE_RegisterService(EnmsNode *enmsNode, char const *serviceName, uint8_t initialServiceState);

/**
 * Unregister a service.
 *
 * Indicates to the ENMS Node service that the service is no longer running in the node.
 * As the result, the internal service descriptor is freed and available for reuse.
 *
 * All of the provided arguments shall be non-null, otherwise the function will return @ref ENMS_RESULT_INVALID_ARGUMENT.
 * Additional restrictions apply to the service name - The service name shall be a non-empty string, not longer than @ref
 * ENMS_NODE_SERVICE_NAME_MAX_LENGTH
 *
 * The service API does not depend on whether the service is started. Calling this function is permitted always, provided the enmsNode is initialized
 *
 * @param[in] enmsNode ENMS Node service instance
 * @param[in] serviceName name of the service to be unregistered
 *
 * @retval ENMS_RESULT_OK if the service was deregistered
 * @retval ENMS_RESULT_INVALID_ARGUMENT - the arguments were invalid  or service was not found
 */
EnmsResult ENMS_NODE_UnregisterService(EnmsNode *enmsNode, char const *serviceName);

/**
 * Set registered service state.
 *
 * This function is used to update the state of a service, previously registered by a call to @ref ENMS_NODE_RegisterService.
 *
 * All of the provided arguments shall be non-null, otherwise the function will return @ref ENMS_RESULT_INVALID_ARGUMENT.
 * Additional restrictions apply to the service name - The service name shall be a non-empty string, not longer than @ref
 * ENMS_NODE_SERVICE_NAME_MAX_LENGTH
 *
 * @param[in] enmsNode ENMS Node service instance
 * @param[in] serviceName name of the service to be updated
 * @param[in] serviceState new state of the service
 *
 * @retval ENMS_RESULT_OK if the service state was updated
 * @retval ENMS_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 */
EnmsResult ENMS_NODE_SetServiceState(EnmsNode *enmsNode, char const *serviceName, uint8_t serviceState);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* ENMS_NODE_H_ */
