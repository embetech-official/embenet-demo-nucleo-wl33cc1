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

  LL_LPUART_InitTypeDef LPUART_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  LL_RCC_SetLPUARTClockSource(LL_RCC_LPUCLKSEL_CLK16M);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPUART1);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  /**LPUART1 GPIO Configuration
  PB6   ------> LPUART1_TX
  PB7   ------> LPUART1_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* LPUART1 interrupt Init */
  NVIC_SetPriority(LPUART1_IRQn, 0);
  NVIC_EnableIRQ(LPUART1_IRQn);

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  LPUART_InitStruct.PrescalerValue = LL_LPUART_PRESCALER_DIV1;
  LPUART_InitStruct.BaudRate = 115200;
  LPUART_InitStruct.DataWidth = LL_LPUART_DATAWIDTH_8B;
  LPUART_InitStruct.StopBits = LL_LPUART_STOPBITS_1;
  LPUART_InitStruct.Parity = LL_LPUART_PARITY_NONE;
  LPUART_InitStruct.TransferDirection = LL_LPUART_DIRECTION_TX_RX;
  LPUART_InitStruct.HardwareFlowControl = LL_LPUART_HWCONTROL_NONE;
  LL_LPUART_Init(LPUART1, &LPUART_InitStruct);
  LL_LPUART_SetTXFIFOThreshold(LPUART1, LL_LPUART_FIFOTHRESHOLD_1_8);
  LL_LPUART_SetRXFIFOThreshold(LPUART1, LL_LPUART_FIFOTHRESHOLD_1_8);

  LL_LPUART_Enable(LPUART1);

  /* Polling LPUART1 initialisation */
  while((!(LL_LPUART_IsActiveFlag_TEACK(LPUART1))) || (!(LL_LPUART_IsActiveFlag_REACK(LPUART1)))) {
  }

  NVIC_SetPriority(LPUART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), INTERRUPT_PRIORITY_HDLC_UART, INTERRUPT_SUBPRIORITY_HDLC_UART));
  NVIC_ClearPendingIRQ(LPUART1_IRQn);
  NVIC_EnableIRQ(LPUART1_IRQn);
  LL_LPUART_EnableIT_RXNE_RXFNE(LPUART1);
  LL_LPUART_EnableIT_TC(LPUART1);
}

void EMBENET_NODE_BSP_UART_Deinit(void) {
  LL_LPUART_DisableIT_RXNE(LPUART1);
  LL_LPUART_DisableIT_TC(LPUART1);
  NVIC_DisableIRQ(LPUART1_IRQn);
  LL_LPUART_Disable(LPUART1);
  LL_LPUART_DeInit(LPUART1);

  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_LPUART1);

  txCb = NULL;
  rxCb = NULL;
  context = NULL;
}

void EMBENET_NODE_BSP_UART_WriteByte(uint8_t c) { LL_LPUART_TransmitData8(LPUART1, c); }

uint8_t EMBENET_NODE_BSP_UART_ReadByte(void) {
  uint8_t data = LL_LPUART_ReceiveData8(LPUART1);
  LL_USART_TransmitData8(USART1, data);
  return data;
}

void LPUART1_IRQHandler(void) {
  if(LL_LPUART_IsActiveFlag_RXNE_RXFNE(LPUART1)) {
    rxCb(context); // Must NOT be null (otherwise init will fail)
  } else if(LL_LPUART_IsActiveFlag_TC(LPUART1)) {
    LL_LPUART_ClearFlag_TC(LPUART1);
    txCb(context); // Must NOT be null (otherwise init will fail)
  } else if(LL_LPUART_IsActiveFlag_PE(LPUART1)) {
    LL_LPUART_ClearFlag_PE(LPUART1);
  } else if(LL_LPUART_IsActiveFlag_FE(LPUART1)) {
    LL_LPUART_ClearFlag_FE(LPUART1);
  } else if(LL_LPUART_IsActiveFlag_NE(LPUART1)) {
    LL_LPUART_ClearFlag_NE(LPUART1);
  } else if(LL_LPUART_IsActiveFlag_ORE(LPUART1)) {
    LL_LPUART_ClearFlag_ORE(LPUART1);
  }
}
