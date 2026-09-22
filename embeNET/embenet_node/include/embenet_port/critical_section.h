/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET PORT API
 * @brief     Critical section interface for the EMBENET NODE Port
 */

#ifndef EMBENET_NODE_PORT_CRITICAL_SECTION_H_
#define EMBENET_NODE_PORT_CRITICAL_SECTION_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup embenet_node_port_critical_section Critical Section Interface
 *
 * This interface provides a critical section primitive used by the stack to protect shared state from concurrent ISR access.
 * Critical sections may be nested; the implementation must track nesting depth and restore the interrupt state only when
 * the outermost section is exited.
 * @{
 */

/**
 * @brief Enters a critical section.
 *
 * @note In most implementations this disables interrupt handling and saves the previous interrupt enable state.
 */
void EMBENET_CRITICAL_SECTION_Enter(void);

/**
 * @brief Exits a critical section.
 *
 * @note In most implementations this re-enables interrupt handling, but only if interrupts were enabled before the
 *       matching @ref EMBENET_CRITICAL_SECTION_Enter call (i.e. the saved interrupt state is restored, not unconditionally enabled).
 */
void EMBENET_CRITICAL_SECTION_Exit(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
