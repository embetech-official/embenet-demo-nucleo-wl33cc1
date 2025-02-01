/**
@file
@copyright $Copyright$
@version   $Revision$
@purpose   embeNET demo
@brief     Task that blinks an LED in a synchronous manner based on common network time
*/

#ifndef SYNCHRONOUS_LED_TASK_H_
#define SYNCHRONOUS_LED_TASK_H_

/**
 * @brief Initializes a task responsible for synchronous LED blinking when network is joined.
 */
void synchronous_led_task_init(void);

/**
 * @brief Starts the synchronous LED blinking task
 */
void synchronous_led_task_start(void);

/**
 * @brief Stops the synchronous LED blinking task
 */
void synchronous_led_task_stop(void);

#endif // SYNCHRONOUS_LED_TASK_H_
