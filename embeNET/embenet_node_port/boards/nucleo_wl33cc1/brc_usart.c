/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     BSP implementation
 */

#include "bsp_interrupt_priorities.h"
#include "embenet_node_stm32wl3_bsp_interface.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <stm32wl3x.h>
#include <stm32wl3x_ll_bus.h>
#include <stm32wl3x_ll_gpio.h>
#include <stm32wl3x_ll_lpuart.h>
#include <stm32wl3x_ll_usart.h>
#pragma GCC diagnostic pop

#include <stddef.h>

static EMBENET_NODE_BSP_UART_Callback_t txCb;
static EMBENET_NODE_BSP_UART_Callback_t rxCb;
static void *context;

void EMBENET_NODE_BSP_UART_Init(EMBENET_NODE_BSP_UART_Callback_t txEndCallback, EMBENET_NODE_BSP_UART_Callback_t rxCallback, void *context) {
  txCb = txEndCallback;
  rxCb = rxCallback;
  context = context;
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPUART1);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART1);

  /**LPUART1 GPIO Configuration
   PA3   ------> LPUART1_RX
   PA2   ------> LPUART1_TX
  //  */
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = LL_GPIO_PIN_1 | LL_GPIO_PIN_15;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  LL_USART_InitTypeDef USART_InitStruct = {0};
  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_DisableFIFO(USART1);
  LL_USART_ConfigAsyncMode(USART1);

  LL_USART_SetRXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetTXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);

  LL_USART_Enable(USART1);

  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), INTERRUPT_PRIORITY_HDLC_UART, INTERRUPT_SUBPRIORITY_HDLC_UART));
  NVIC_ClearPendingIRQ(USART1_IRQn);
  NVIC_EnableIRQ(USART1_IRQn);
  LL_USART_EnableIT_RXNE(USART1);
  LL_USART_EnableIT_TC(USART1);
}

void EMBENET_NODE_BSP_UART_Deinit(void) {
  LL_USART_DisableIT_RXNE(USART1);
  LL_USART_DisableIT_TC(USART1);
  NVIC_DisableIRQ(USART1_IRQn);
  LL_USART_Disable(USART1);
  LL_USART_DeInit(USART1);

  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_LPUART1);

  txCb = NULL;
  rxCb = NULL;
  context = NULL;
}

void EMBENET_NODE_BSP_UART_WriteByte(uint8_t c) { LL_USART_TransmitData8(USART1, c); }

uint8_t EMBENET_NODE_BSP_UART_ReadByte(void) { return LL_USART_ReceiveData8(USART1); }

void USART1_IRQHandler(void) {
  if(LL_USART_IsActiveFlag_RXNE(USART1)) {
    rxCb(context); // Must NOT be null (otherwise init will fail)
  } else if(LL_USART_IsActiveFlag_TC(USART1)) {
    LL_USART_ClearFlag_TC(USART1);
    txCb(context); // Must NOT be null (otherwise init will fail)
  } else if(LL_USART_IsActiveFlag_PE(USART1)) {
    LL_USART_ClearFlag_PE(USART1);
  } else if(LL_USART_IsActiveFlag_FE(USART1)) {
    LL_USART_ClearFlag_FE(USART1);
  } else if(LL_USART_IsActiveFlag_NE(USART1)) {
    LL_USART_ClearFlag_NE(USART1);
  } else if(LL_USART_IsActiveFlag_ORE(USART1)) {
    LL_USART_ClearFlag_ORE(USART1);
  }
}
