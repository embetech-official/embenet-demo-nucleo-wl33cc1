/**
@file
@copyright $Copyright$
@version   $Revision$
@purpose   embeNET demo
@brief     Task that blinks an LED in a synchronous manner based on common network time
*/

#include "synchronous_led_task.h"
#include "main.h"
#include <embenet/node.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

// How often the LED will blink (in ms)
#define LED_BLINK_PERIOD_MS 		1500
// How long will the LED be on (in ms)
#define LED_ON_DURATION_MS 	200

// Task Id
static EMBENET_TaskId ledBlinkTaskId = EMBENET_TASKID_INVALID;

// State of the LED (true = on, false = off)
static bool ledIsOn;

/**
 * @brief User-defined function that will be invoked as a periodically scheduled task
 *
 * @param[in] taskId id of the task
 * @param[in] timeSource time source (local time or network time)
 * @param[in] t time at which the task was scheduled to run
 * @param[in] context generic, user-defined context
 */
static void synchronousLedTask(EMBENET_TaskId taskId, EMBENET_NODE_TimeSource timeSource, uint64_t time, void *context) {
	(void) context;
	if (ledIsOn) {
		// Turn off the LED
		BSP_LED_Off(LED_RED);
		ledIsOn = false;
		// Reschedule this task
		EMBENET_NODE_TaskSchedule(taskId, timeSource, time + LED_BLINK_PERIOD_MS-LED_ON_DURATION_MS);
	} else {
		// Turn on the LED
		BSP_LED_On(LED_RED);
		ledIsOn = true;
		// Reschedule this task
		EMBENET_NODE_TaskSchedule(taskId, timeSource, time + LED_ON_DURATION_MS);
	}
}

void synchronous_led_task_init(void) {
	// creating LED blinking task
	if ( EMBENET_TASKID_INVALID == (ledBlinkTaskId = EMBENET_NODE_TaskCreate(synchronousLedTask, NULL))) {
		printf("Failed to create synchronous LED task\n\r");
	}
}

void synchronous_led_task_start(void) {
	// Get network time and calculate an even timestamp
	uint64_t timestamp = EMBENET_NODE_GetNetworkTime() / LED_BLINK_PERIOD_MS + 1;
	timestamp = timestamp * LED_BLINK_PERIOD_MS;
	// Schedule the blinking task
	if (EMBENET_RESULT_OK != EMBENET_NODE_TaskSchedule(ledBlinkTaskId, EMBENET_NODE_TIME_SOURCE_NETWORK, timestamp)) {
		printf("Failed to start synchronous LED task");
	}
}

void synchronous_led_task_stop(void) {
	// Stop LED blinking task
	if (EMBENET_RESULT_OK != EMBENET_NODE_TaskCancel(ledBlinkTaskId)) {
		printf("Failed to stop synchronous LED task");
	}
	// Return to off state
	BSP_LED_Off(LED_RED);
	ledIsOn = false;
}
