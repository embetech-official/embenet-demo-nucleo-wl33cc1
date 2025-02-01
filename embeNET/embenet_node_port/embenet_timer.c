/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     Implementation of Timer interface for the embeNET Node
 */

#include <embenet_port/timer.h>

#include "embenet_port_interrupt_priorities.h"
#include <embenet_port/critical_section.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <stm32wl3x_hal.h>
#include <stm32wl3x_ll_rcc.h>
#include <stm32wl3x_ll_tim.h>
#pragma GCC diagnostic pop

#include <stdbool.h>
#include <stddef.h>

enum {
  TICKS_PER_S = 62500U,
  TICK_PERIOD_US = 16U,
  TIMER_MAX_VALUE = 0xffffU,
  MAX_COMPARE_DURATION_TICKS = 0x7fffU,
  MAX_COMPARE_DURATION_US = (MAX_COMPARE_DURATION_TICKS * TICK_PERIOD_US),
  GUARD_US = (EMBENET_TimeUs)(20U),
  OVERFLOW_EXTENSION_US = (uint64_t)(0xffffU * TICK_PERIOD_US)
};

static EMBENET_TIMER_CompareCallback callback;
static void *callbackContext;
static uint64_t volatile timerValueExtension;
static bool volatile softwareIrq;

void EMBENET_TIMER_Init(EMBENET_TIMER_CompareCallback compareCallback, void *context) {
  LL_TIM_DeInit(TIM2); // Make sure the timer is deinitialized and reset to default values

  callback = compareCallback;
  callbackContext = context;

  LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_TIM2);
  NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), INTERRUPT_PRIORITY_TIMER, INTERRUPT_SUBPRIORITY_TIMER));
  NVIC_EnableIRQ(TIM2_IRQn);

  LL_RCC_ClocksTypeDef clocks;
  LL_RCC_GetSystemClocksFreq(&clocks);
  LL_TIM_InitTypeDef TIM_InitStruct = {.CounterMode = LL_TIM_COUNTERMODE_UP,
                                       .Prescaler = (uint16_t)(clocks.SYSCLK_Frequency / TICKS_PER_S - 1U),
                                       .ClockDivision = LL_TIM_CLOCKDIVISION_DIV1,
                                       .Autoreload = (0xFFFFU),
                                       .RepetitionCounter = 0};
  LL_TIM_Init(TIM2, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM2);
  LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);

  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {
      .OCMode = LL_TIM_OCMODE_FROZEN, .OCState = LL_TIM_OCSTATE_DISABLE, .CompareValue = 0, .OCPolarity = LL_TIM_OCPOLARITY_HIGH};
  LL_TIM_OC_Init(TIM2, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

  LL_TIM_OC_DisableFast(TIM2, LL_TIM_CHANNEL_CH1);
  LL_TIM_SetTriggerOutput(TIM2, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM2);

  LL_TIM_ClearFlag_UPDATE(TIM2);
  LL_TIM_EnableIT_UPDATE(TIM2);

  LL_TIM_EnableCounter(TIM2);
}

void EMBENET_TIMER_Deinit(void) {
  LL_TIM_DisableCounter(TIM2);
  LL_TIM_DisableIT_CC1(TIM2);
  NVIC_DisableIRQ(TIM2_IRQn);

  LL_TIM_DeInit(TIM2);
  LL_APB0_GRP1_DisableClock(LL_APB0_GRP1_PERIPH_TIM2);
}

void EMBENET_TIMER_SetCompare(EMBENET_TimeUs compareValue) {
  EMBENET_CRITICAL_SECTION_Enter();

  LL_TIM_EnableIT_CC1(TIM2); // make sure that the interrupt is active (first compare)

  // get current time and counter
  uint32_t counter = LL_TIM_GetCounter(TIM2);
  EMBENET_TimeUs now = (EMBENET_TimeUs)((uint64_t)counter * TICK_PERIOD_US + timerValueExtension);
  if(LL_TIM_IsActiveFlag_UPDATE(TIM2)) {
    counter = LL_TIM_GetCounter(TIM2);
    now = (EMBENET_TimeUs)((uint64_t)counter * TICK_PERIOD_US + timerValueExtension + OVERFLOW_EXTENSION_US);
  }

  EMBENET_TimeUs delta = compareValue - now;
  if((EMBENET_TimeUs)(delta - GUARD_US) < MAX_COMPARE_DURATION_US) {
    // arm the compare interrupt
    LL_TIM_OC_SetCompareCH1(TIM2, (counter + (uint32_t)((uint64_t)(delta) / TICK_PERIOD_US)) & TIMER_MAX_VALUE);
  } else {
    // compareValue is too close to current value and timer will be late, interrupt is triggered immediately
    NVIC_SetPendingIRQ(TIM2_IRQn);
    softwareIrq = true;
  }

  EMBENET_CRITICAL_SECTION_Exit();
}

EMBENET_TimeUs EMBENET_TIMER_ReadCounter(void) {
  // note that during assembly of the actual time, the counter may increment and overflow itself
  EMBENET_CRITICAL_SECTION_Enter();
  // this thing is sopthisticated
  // it can be called from nonpriviledged mode (1) and from @ref EMBENET_PORT_TIMER_IRQ_HANDLER ISR (2)
  // (1A) after entering the critical section and before getting the timer value it can increment and overflow,
  // OVF flag will be set and timerValueExtension will be not incremented - OVF FLAG MUST BE CHECKED!
  // (1B) during code execution inside the critical section timer may increment and overflow itself - no harm
  // (2) before entering critical section timerValueExtension may not be incremented and OVF flag will be set - OVF FLAG MUST BE CHECKED!
  uint64_t now = (uint64_t)LL_TIM_GetCounter(TIM2) * TICK_PERIOD_US + timerValueExtension;
  if(LL_TIM_IsActiveFlag_UPDATE(TIM2)) {
    now = (uint64_t)LL_TIM_GetCounter(TIM2) * TICK_PERIOD_US + timerValueExtension + OVERFLOW_EXTENSION_US;
  }
  EMBENET_CRITICAL_SECTION_Exit();

  return (EMBENET_TimeUs)(now);
}

EMBENET_TimeUs EMBENET_TIMER_GetMaxCompareDuration(void) { return (EMBENET_TimeUs)MAX_COMPARE_DURATION_US; }

void TIM2_IRQHandler(void) {
  if(LL_TIM_IsActiveFlag_UPDATE(TIM2)) {
    LL_TIM_ClearFlag_UPDATE(TIM2);
    timerValueExtension += (uint64_t)OVERFLOW_EXTENSION_US;
  }

  if(LL_TIM_IsActiveFlag_CC1(TIM2) || softwareIrq) {
    LL_TIM_ClearFlag_CC1(TIM2);
    LL_TIM_DisableIT_CC1(TIM2);
    softwareIrq = false;

    if(callback != NULL) {
      callback(callbackContext);
    }
  }
}
