/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     BSP implementation
 */
 
 #ifndef EMBENET_NODE_STM32WLE5_BSP_INTERFACE_H_
#define EMBENET_NODE_STM32WLE5_BSP_INTERFACE_H_
#pragma once


#include <stdbool.h>
#include <stdint.h>

/**
 * @brief UART callback type
 * @param[in] context optional context that will be passed to the callbacks upon calling
 */
typedef void (*EMBENET_NODE_BSP_UART_Callback_t)(void* context);

/**
 * @brief Initializes UART (GPIO, clocks, peripherals, etc.).
 * @param[in] txEndCallback Callback to be called on finished transmission
 * @param[in] rxCb Callback to be called on reception
 * @param[in] context optional context that will be passed to the callbacks upon calling
 */
void EMBENET_NODE_BSP_UART_Init(const EMBENET_NODE_BSP_UART_Callback_t txEndCallback, const EMBENET_NODE_BSP_UART_Callback_t rxCallback, void* context);


/// @brief Deinitializes UART
void EMBENET_NODE_BSP_UART_Deinit(void);

/**
 * @brief Writes byte to TX register. Does not wait if register is already occupied
 * @param[in] c character to write
 */
void EMBENET_NODE_BSP_UART_WriteByte(const uint8_t c);


/// @brief Reads byte from RX register. Does not wait for data.
uint8_t EMBENET_NODE_BSP_UART_ReadByte(void);


#endif
