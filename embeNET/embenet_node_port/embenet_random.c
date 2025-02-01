/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     Implementation of Random interface for embeNET Node
 */

#include <embenet_port/random.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <stm32wl3x_hal.h>
#include <stm32wl3x_ll_rcc.h>
#include <stm32wl3x_ll_rng.h>
#pragma GCC diagnostic pop

uint32_t EMBENET_RANDOM_Get(void) {

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_RNG);

  // Initialize random numbers generation
  LL_RNG_Enable(RNG);

  // Wait for DRDY flag to be raised
  while(!LL_RNG_IsActiveFlag_RNGRDY(RNG)) {
    ;
  }
  uint32_t val = LL_RNG_ReadRandData16(RNG);
  // Wait for DRDY flag to be raised
  while(!LL_RNG_IsActiveFlag_RNGRDY(RNG)) {
    ;
  }
  val |= (LL_RNG_ReadRandData16(RNG) << 16);
  // Stop random numbers generation
  LL_RNG_Disable(RNG);
  __HAL_RCC_RNG_CLK_DISABLE();

  return val;
}
