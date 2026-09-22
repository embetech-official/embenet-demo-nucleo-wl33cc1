/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET PORT API
 * @brief     Timer interface for the EMBENET NODE Port
 */

#ifndef EMBENET_NODE_PORT_TIMER_H_
#define EMBENET_NODE_PORT_TIMER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup embenet_node_port_timer Timer Interface
 *
 * Provides interface for the hardware timer that the embeNET Node stack uses to schedule various activities.
 *
 * @{
 */

typedef uint32_t EMBENET_TimeUs;          ///< Type to store time in microseconds
typedef int64_t EMBENET_TimeDifferenceUs; ///< Type to store time difference in microseconds

/**
 * @brief EMBENET timer callback function type
 * @param[in] context general-purpose context associated with the timer
 */
typedef void (*EMBENET_TIMER_CompareCallback)(void *context);

/**
 * @brief Initializes and starts the hardware timer.
 *
 * The timer must begin counting from 0 upwards after this call. The supplied callback will be invoked each time the compare event fires
 * (see @ref EMBENET_TIMER_SetCompare).
 *
 * @param[in] compareCallback function invoked when the compare value is reached; must not be NULL.
 * @param[in] context         opaque pointer passed to @p compareCallback on each invocation; may be NULL.
 */
void EMBENET_TIMER_Init(EMBENET_TIMER_CompareCallback compareCallback, void *context);

/**
 * @brief Deinitializes the hardware timer.
 *
 * Stops the timer and disables the compare interrupt.
 */
void EMBENET_TIMER_Deinit(void);

/**
 * @brief Schedules a compare event at the given absolute timer value.
 *
 * The implementation must call the @c compareCallback registered in @ref EMBENET_TIMER_Init when the hardware counter reaches @p compareValue.
 *
 * Because the underlying counter wraps at 2^32 µs, the implementation uses @ref EMBENET_TIMER_GetMaxCompareDuration to disambiguate past from future:
 * - If the signed distance from the current counter to @p compareValue exceeds @ref EMBENET_TIMER_GetMaxCompareDuration, the event is considered
 *   to be in the past and the callback MUST be invoked immediately.
 * - Otherwise the compare interrupt MUST be scheduled for the future.
 *
 * On lower-performance systems the implementation may apply a guard time (e.g. 20 µs): any @p compareValue within
 * [current_time − guard, current_time + guard] MAY be treated as if it were in the past.
 *
 * @param[in] compareValue absolute timer value at which the callback should fire, in microseconds.
 */
void EMBENET_TIMER_SetCompare(EMBENET_TimeUs compareValue);

/**
 * @brief Returns the current hardware counter value.
 *
 * The counter is monotonically increasing and wraps at 2^32 (i.e. the value is in the range [0, 2^32 − 1]).
 *
 * @return Current timer counter value in microseconds.
 */
EMBENET_TimeUs EMBENET_TIMER_ReadCounter(void);

/**
 * @brief Returns the maximum duration that the timer considers to be in the future.
 *
 * Used by @ref EMBENET_TIMER_SetCompare to resolve the past-vs-future ambiguity introduced by the 32-bit counter wrap.
 * If the forward distance from the current counter value to a requested compare value exceeds this limit, the compare
 * event is treated as already past. The returned value must not exceed the timer period (2^32 µs).
 * In most implementations the appropriate value is (timer period) / 2.
 *
 * @return Maximum schedulable compare duration in microseconds.
 */
EMBENET_TimeUs EMBENET_TIMER_GetMaxCompareDuration(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
