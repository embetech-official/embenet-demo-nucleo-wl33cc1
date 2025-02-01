/**
@file
@license
@copyright
@version   $Revision$
@purpose   Critical section.
@brief     Needed by toolchain_defs.h.

*/


#ifndef BSP_INTERRUPT_PRIORITIES_H_
#define BSP_INTERRUPT_PRIORITIES_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Interrupt priority order.
 */
enum {
    INTERRUPT_PRIORITY_HDLC_UART      = 0,
    INTERRUPT_PRIORITY_ETSI_SCPI_UART = 3,
    INTERRUPT_PRIORITY_DEBUG_UART     = 3,
};

/**
 * @brief Interrupt subpriority order.
 */
enum {
    INTERRUPT_SUBPRIORITY_HDLC_UART      = 0,
    INTERRUPT_SUBPRIORITY_ETSI_SCPI_UART = 0,
    INTERRUPT_SUBPRIORITY_DEBUG_UART     = 0,
};

#ifdef __cplusplus
}
#endif

#endif /* BSP_INTERRUPT_PRIORITIES_H_ */
