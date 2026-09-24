/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.2.1
 * @brief     EMBENET UDP API
 */

#ifndef EMBENET_UDP_H_
#define EMBENET_UDP_H_

#include <embenet/ipv6.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup embenet_udp_api embeNET UDP C API
 *
 * C API for sending and receiving UDP datagrams over embeNET: registering/unregistering sockets
 * (@ref EMBENET_UDP_RegisterSocket, @ref EMBENET_UDP_UnregisterSocket) and sending data through them
 * (@ref EMBENET_UDP_GetMaxDataSize, @ref EMBENET_UDP_Send).
 *
 * To get more information on how to use this API refer to: @ref embenet_udp_using_sockets
 * To write a new port, or to understand @c EMBENET_UDP_OS_DEPENDENT, refer to: @ref embenet_udp_porting
 *
 *  @{
 */

/** @brief Convenience alias for @ref EMBENET_UDP_SocketDescriptor that SHALL be used in user's code */
typedef struct EMBENET_UDP_SocketDescriptor EMBENET_UDP_SocketDescriptor;

/**
 * @brief Data reception handler called when a UDP datagram is received on a registered port.
 *
 * During socket registration (see @ref EMBENET_UDP_RegisterSocket) the user is expected to pass the callback function that will be called
 * each time a UDP datagram is received through this socket. This typedef defines the format of such function.
 *
 * @note This handler callback is called in non-privileged mode. It is called from a thread or main loop and not from an interrupt service routine.
 * @note All of the pointer parameters are not NULL, even if the data size is 0 (empty datagram).
 *
 * @param[in] socket Pointer to @ref EMBENET_UDP_SocketDescriptor structure that describes the socket that received the data
 * @param[in] sourceAddress IPv6 address of the sender
 * @param[in] sourcePort source port number that was used in the sender to send the data
 * @param[in] data Pointer to memory region that holds the received data
 * @param[in] dataSize Size of the received data (in number of bytes)
 */
typedef void (*EMBENET_UDP_RxDataHandler)(EMBENET_UDP_SocketDescriptor const *socket, EMBENET_IPV6 const *sourceAddress, uint16_t sourcePort,
                                          void const *data, size_t dataSize);

/**
 * @brief Possible types of a UDP socket describing its listening IPv6 address.
 */
typedef enum {
  EMBENET_UDP_TRAFFIC_UNICAST = 0,   ///< The socket only listens on node's unicast address
  EMBENET_UDP_TRAFFIC_MULTICAST = 1, ///< The socket only listens on multicast address of given group
  EMBENET_UDP_TRAFFIC_ALL = 2,       ///< The socket listens both on nodes unicast address or any matching multicast address - equivalent to IPv6 [::]
} EMBENET_UDP_Traffic;

/// @brief Possible result codes.
typedef enum {
  EMBENET_UDP_RESULT_OK = 0,
  EMBENET_UDP_RESULT_UNSPECIFIED_ERROR, ///< Unspecified error
  EMBENET_UDP_RESULT_INVALID_ARGUMENT,  ///< Function arguments are invalid
  EMBENET_UDP_RESULT_NOT_SYNCHRONIZED,  ///< The node is not synchronized to the network
  // UDP specific
  EMBENET_UDP_RESULT_MAX_DATA_SIZE_EXCEEDED, ///< Data size beyond limit
  EMBENET_UDP_RESULT_QUEUE_FULL,             ///< Device's packet queue is full
  EMBENET_UDP_RESULT_FORWARDING_ERROR,       ///< Forwarding error
  EMBENET_UDP_RESULT_SOCKET_UNREGISTERED,    ///< UDP socket was not registered
  EMBENET_UDP_RESULT_ALREADY,                ///< The socket is already registered
} EMBENET_UDP_Result;

/**
 * @brief Structure describing a UDP socket.
 *
 * This structure describes a single registered UDP socket. When registering a socket through a call to @ref EMBENET_UDP_RegisterSocket
 * the user is expected to fill all the structure fields EXCEPT the 'next' field, which is used internally by the embeNET stack.
 */
struct EMBENET_UDP_SocketDescriptor {
  /**
   * Field reserved for the network stack.
   * When registering new socket set this field to NULL. Once the socket is registered this field MUST NOT be changed.
   */
  EMBENET_UDP_SocketDescriptor *next;

  /**
   * A mandatory user-defined callback function that will be called every time an UDP datagram is received on the socket.
   * This field must not be NULL.
   */
  EMBENET_UDP_RxDataHandler rxDataHandler;

  /**
   * An optional user-defined context pointer that will be passed to the rxDataHandler when it is called.
   */
  void *userContext;

  /**
   * UDP port number to bind to. This parameter may be in the range of 1 to 65535.
   */
  uint16_t port;

  /**
   * Multicast group identifier used only when handledTraffic is set to @ref EMBENET_UDP_TRAFFIC_MULTICAST.
   * In such case this identifier determines the multicast group address that the socket will listen to.
   * In other cases this field is ignored and should be set to 0.
   */
  EMBENET_GroupId groupId;

  /**
   * Traffic that will be handled by the socket. Possible options:
   *  - @ref EMBENET_UDP_TRAFFIC_UNICAST - the socket will only receive data sent to the node using unicast destination address
   *  - @ref EMBENET_UDP_TRAFFIC_MULTICAST - the socket will only receive data sent to the node using matching multicast group address
   *  - @ref EMBENET_UDP_TRAFFIC_ALL - the socket will receive data sent to the node using unicast or matching multicast address
   */
  EMBENET_UDP_Traffic handledTraffic : 8;
};

/**
 * @brief Register a new UDP socket for data reception.
 *
 * This function registers a new UDP socket, enabling data reception on the resulting address/port combination.
 *
 * @param[in] socket Pointer to @ref EMBENET_UDP_SocketDescriptor structure that describes the socket to be registered
 *
 * @note The provided socket descriptor instance MUST be valid and accessible until EMBENET_UDP_UnregisterSocket. In particular, the descriptor
 * SHALL NOT have automatic storage duration.
 * @note The user MAY register socket with EMBENET_UDP_TRAFFIC_MULTICAST==handledTraffic and group not joined by the node. The user will not receive
 * messages on this socket until the node joins the required group
 * @note All of the pointer parameters MUST be not NULL, otherwise the behaviour is UNDEFINED
 *
 * @return EMBENET_UDP_RESULT_OK if socket was properly registered, or error status when the registration failed
 */
EMBENET_UDP_Result EMBENET_UDP_RegisterSocket(EMBENET_UDP_SocketDescriptor *socket);

/**
 * @brief Unregister a UDP socket from the interface.
 *
 * @note All of the pointer parameters MUST be not NULL, otherwise the behaviour is UNDEFINED
 *
 * @param[in] socket Pointer to @ref EMBENET_UDP_SocketDescriptor structure that describes the socket to be unregistered
 *
 * @retval EMBENET_UDP_RESULT_OK if socket was successfully unregistered
 * @retval EMBENET_UDP_RESULT_SOCKET_UNREGISTERED if the given socket has not been registered
 */
EMBENET_UDP_Result EMBENET_UDP_UnregisterSocket(EMBENET_UDP_SocketDescriptor *socket);

/**
 * @brief Get the maximum size of a single UDP payload.
 *
 * This function returns the maximum size of data that can be sent in a single UDP datagram. This is the maximum allowed size of the data to be sent
 * by a call to @ref EMBENET_UDP_Send.
 *
 * @note All of the pointer parameters MUST be not NULL, otherwise the behaviour is UNDEFINED
 *
 * @param[in] socket Pointer to @ref EMBENET_UDP_SocketDescriptor structure that describes the socket to be queried
 *
 * @return Maximum size of data that can be sent in a single UDP datagram (in number of bytes)
 */
size_t EMBENET_UDP_GetMaxDataSize(EMBENET_UDP_SocketDescriptor const *socket);

/**
 * @brief Send a UDP datagram from the given socket.
 *
 * This function schedules a UDP datagram to be sent.
 *
 * @note A UDP datagram can be sent only from a registered port.
 * @note The source address of the resulting IPv6 packet will always resolve to the node's UNICAST address
 * @note All of the pointer parameters MUST be not NULL (even if data size is 0), otherwise the behaviour is UNDEFINED
 *
 * @param[in] socket Pointer to @ref EMBENET_UDP_SocketDescriptor structure that describes the socket to be used for sending
 * @param[in] destinationAddress Pointer to IPv6 destination address
 * @param[in] destinationPort UDP destination port number, >0
 * @param[in] data Pointer to memory address storing UDP payload data
 * @param[in] dataSize Size of data in bytes in range [0, @ref EMBENET_UDP_GetMaxDataSize]
 *
 * @retval EMBENET_UDP_RESULT_OK if datagram was scheduled properly for sending
 * @retval EMBENET_UDP_RESULT_INVALID_ARGUMENT if at least one of the input arguments was invalid
 * @retval EMBENET_UDP_RESULT_MAX_DATA_SIZE_EXCEEDED if the size of the data to be sent is too large (see @ref EMBENET_UDP_GetMaxDataSize)
 * @retval EMBENET_UDP_RESULT_QUEUE_FULL if there is not enough space to buffer the data to send
 * @retval EMBENET_UDP_RESULT_SOCKET_UNREGISTERED if the given socket has not been registered
 */
EMBENET_UDP_Result EMBENET_UDP_Send(EMBENET_UDP_SocketDescriptor const *socket, EMBENET_IPV6 const *destinationAddress, uint16_t destinationPort,
                                    void const *data, size_t dataSize);

/**
 * @brief Get library version as a NUL-terminated string.
 *
 * @return Pointer to a read-only, statically-allocated string in semantic version format (e.g., "1.2.3"). Must not be freed or modified.
 */
char const *EMBENET_UDP_GetVersionString(void);

/**
 * @brief Report whether this port requires @ref EMBENET_UDP_Proc.
 *
 * @see @ref embenet_udp_porting for the @c EMBENET_UDP_OS_DEPENDENT contract this function reports on.
 *
 * @return true if @ref EMBENET_UDP_Proc must be called periodically, false otherwise
 */
bool EMBENET_UDP_IsOsDependent(void);

// EMBENET_UDP_OS_DEPENDENT: set by the port to 1 or 0, declaring whether it requires EMBENET_UDP_Proc.
// See @ref embenet_udp_porting for the full contract.
#ifndef EMBENET_UDP_OS_DEPENDENT
#define EMBENET_UDP_OS_DEPENDENT 0
#endif

#if 1 == EMBENET_UDP_OS_DEPENDENT
/**
 * @brief Set the unicast address of the node.
 *
 * @note All of the pointer parameters MUST be not NULL, otherwise the behaviour is UNDEFINED
 * @note Declared only when @c EMBENET_UDP_OS_DEPENDENT is 1
 * @param[in] addr Pointer to a string containing the IPv6 address, e.g.: "2001:0db8:0000:0000:0000:0000:0000:0001" or "2001:0db8::1"
 *
 * @return true when the address was set successfully, false otherwise
 */
bool EMBENET_SetSourceAddress(char const *addr);

/**
 * @brief Process UDP reception events.
 *
 * This function should be called periodically to process the UDP reception.
 * Each call to this function will check if there is any data received on the registered sockets and will call the corresponding
 * data reception handler. Only one data reception handler will be called per call to this function.
 *
 * @note Declared only when @c EMBENET_UDP_OS_DEPENDENT is 1
 *
 * @return true if some data was received and processed, false otherwise
 */
bool EMBENET_UDP_Proc(void);
#endif

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* EMBENET_UDP_H_ */
