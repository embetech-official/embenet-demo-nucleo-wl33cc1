/**
@file
@copyright $Copyright$
@version   $Revision$
@purpose   embeNET demo
@brief     Exemplary UDP-based client service
*/

#ifndef UDP_SERVICE_H_
#define UDP_SERVICE_H_

/**
 * @brief Initializes an exemplary, user-defined UDP service.
 *
 * Opens a UDP socket and initializes a periodic task.
 */
void udp_service_init(void);

/**
 * @brief Starts the exemplary, user-defined UDP service.
 */
void udp_service_start(void);

/**
 * @brief Stops the exemplary, user-defined UDP service.
 */
void udp_service_stop(void);

#endif
