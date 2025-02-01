/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// Standard C library
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
// embeNET includes
#include <embetech/logger.h>
#include <embenet/node.h>
#include <embenet/enms_node.h>
// demo services
#include "udp_service.h"
#include "mqttsn_client_service.h"
#include "synchronous_led_task.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

CRYP_HandleTypeDef hcryp;
__ALIGN_BEGIN static const uint32_t pKeyAES[4] __ALIGN_END = {
                            0x00000000,0x00000000,0x00000000,0x00000000};

UART_HandleTypeDef hlpuart1;

SMRSubGConfig MRSUBG_RadioInitStruct;
MRSubG_802_15_4_PcktFields MRSUBG_PacketSettingsStruct;

RNG_HandleTypeDef hrng;

/* USER CODE BEGIN PV */

/// Descriptor of the ENMS service (network maintenance and visualization)
EnmsNode enmsNode;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_MRSUBG_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_AES_Init(void);
static void MX_RNG_Init(void);
static void MX_TIM2_Init(void);
static void MX_LPUART1_UART_Init(void);
/* USER CODE BEGIN PFP */
#if defined(__ICCARM__)
__ATTRIBUTES size_t __write(int, const unsigned char *, size_t);
#endif /* __ICCARM__ */

#if defined(__ICCARM__)
/* New definition from EWARM V9, compatible with EWARM8 */
int iar_fputc(int ch);
#define PUTCHAR_PROTOTYPE int iar_fputc(int ch)
#elif defined ( __CC_ARM ) || defined(__ARMCC_VERSION)
/* ARM Compiler 5/6*/
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#elif defined(__GNUC__)
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#endif /* __ICCARM__ */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * User-defined callback that will be called, when the node joins the network.
 * @param[in] panId Identifier of the Network that node joined
 * @param[in] quickJoinCredentials pointer to the Quick Join Credentials that MAY be stored by the user to facilitate rejoining process.
 */
static void onJoined(EMBENET_PANID panId, const EMBENET_NODE_QuickJoinCredentials *quickJoinCredentials) {
    printf("Joined network with PANID: 0x%04" PRIx16 "\n\r", panId);

    // Start ENMS Service that provides network-wide telemetry information
    EnmsResult enmsStartStatus = ENMS_NODE_Start(&enmsNode);
    if (ENMS_RESULT_OK == enmsStartStatus) {
        printf("ENMS service started\n\r");
    } else {
        printf("ENMS service failed to start with status: %d\n\r", (int)enmsStartStatus);
    }

	// Start LED blinking task
    synchronous_led_task_start();

#if 1 != IS_ROOT
    // Start exemplary, user-defined custom service
    udp_service_start();
    // Start MQTT-SN demo service
    mqttsn_client_service_start();
#endif
}

/**
 * @brief User-defined callback, that will be called after the node leaves the network
 */
static void onLeft(void) {
    printf("Node has left the network\n\r");
    // Stop ENMS service
    EnmsResult enmsStopStatus = ENMS_NODE_Stop(&enmsNode);
    if (ENMS_RESULT_OK == enmsStopStatus) {
        printf("ENMS service stopped\n\r");
    } else {
        printf("ENMS service failed to stop with status: %d\n\r", (int)enmsStopStatus);
    }
	// Stop LED blinking task
    synchronous_led_task_stop();

#if 1 != IS_ROOT
    // Stop exemplary, user-defined custom service
    udp_service_stop();
    // Stop MQTT-SN demo service
    mqttsn_client_service_stop();
#endif

}

/**
 * @brief User-defined callback, that will be called when node tries to join the network
 *
 * NOTE: This callback is included in this demo only for debugging purposes
 */
static void onJoinAttempt(EMBENET_PANID panId, const void *panData, size_t panDataSize) {
    printf("Node is attempting to join the network with PANID 0x%04" PRIx16 "\n\r", panId);
    printf("Network-wide data (%uB)\n\r", (unsigned)panDataSize);
}


/**
 * @brief User-defined callback, that will be called when the node receives UDP datagram on closed port
 *
 * NOTE: This callback is included for purely debugging purposes. It should be Never used as a method of reliable data transfer
 */
static void dataOnUregisteredPort(uint16_t port) {
    printf("Got UDP datagram on unregistered port no: %" PRIu16 "\n\r", port);
}

/**
 * @brief User-defined callback, that will be called when provided quick join credentials become obsolete.
 *
 * If the quick join feature is used, user should delete the stored data and store new data, when onJoined callback will be called again.
 * This demo application does not use the quick join feature.
 */
static void onQuickJoinCredentialsObsolete(void) {
    printf("Quick join credentials became obsolete\n\r");
}

/**
 * @brief User-defined log output function used for logging diagnostic logs from embeNET
 */
static void loggerOutput(char c, void* context) {
#if 1 != IS_ROOT
	while (!LL_USART_IsActiveFlag_TXE_TXFNF(USART1)) {
	    ;
	}
    LL_USART_TransmitData8(USART1, c);
#endif
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* Configure the peripherals common clocks */
    PeriphCommonClock_Config();

    /* USER CODE BEGIN SysInit */

   /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_MRSUBG_Init();
    MX_USART1_UART_Init();
    MX_AES_Init();
    MX_RNG_Init();
    MX_TIM2_Init();
    MX_LPUART1_UART_Init();
    /* USER CODE BEGIN 2 */
    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);
    BSP_LED_Init(LED_BLUE);
    BSP_LED_On(LED_RED);

    LOGGER_SetOutput(loggerOutput, NULL);
    LOGGER_SetRuntimeLevel(LOGGER_LEVEL_TRACE);
    // You can change this to LOGGER_Enable to enable more logs from embeNET:
    LOGGER_Disable();

    printf("\n\r"
            "+---------------------------------------------+\n\r"
            "   embeNET Node demo for nucleo-wl33c1 board   \n\r"
            "+---------------------------------------------+\n\r");

    // Initialize structure with user-defined event handlers
    EMBENET_NODE_EventHandlers handlers = {
        .onJoined = onJoined,
        .onLeft = onLeft,
        .onJoinAttempt = onJoinAttempt,
        .onQuickJoinCredentialsObsolete = onQuickJoinCredentialsObsolete,
        .onDataOnUnregisteredPort = dataOnUregisteredPort
    };

    // Initialize network stack
    if (EMBENET_RESULT_OK == EMBENET_NODE_Init(&handlers)) {
        EMBENET_Version ver = EMBENET_NODE_GetVersion();
    	printf("embeNET Node v%d.%d.%d initialized\n\r", ver.hi, ver.lo, ver.rev);
    } else {
        printf("Failed to initialize embeNET Node\n\r");
    }
    
    // Get hardware ID using 96-bit CPU uid
    uint8_t hardwareId[16] = { 0x00 };
    memcpy(hardwareId, (void const*) UID64_BASE, 12);
    // Initialize ENMS service on its default port. You may specify custom Hardware Identifier
    if (ENMS_RESULT_OK == ENMS_NODE_Init(&enmsNode, ENMS_NODE_GetDefaultPort(), hardwareId, ENMS_NODE_GetSmallScalePolicy())) {
        printf("ENMS service initialized\n\r");
    } else {
        printf("Failed to initialize ENMS service!\n\r");
    }
    // Initialize LED blinking task
    synchronous_led_task_init();

#if 1 == IS_ROOT
    printf("Acting as root with UID: 0x%x%08x\n\r", (unsigned)(EMBENET_NODE_GetUID()>>32), (unsigned)(EMBENET_NODE_GetUID()));
    // When the application is built for Root node, start as root instead of joining the network
    if (EMBENET_RESULT_OK == EMBENET_NODE_RootStart(NULL, 0)) {
    	printf("Root started successfully\n\r");
    } else {
    	printf("Failed to start as root!\n\r");
    }
#else
    printf("Acting as node with UID: 0x%x%08x\n\r", (unsigned)(EMBENET_NODE_GetUID()>>32), (unsigned)(EMBENET_NODE_GetUID()));

    // Initialize exemplary, user-defined custom UDP service
    udp_service_init();
    // Initialize MQTT-SN service
    mqttsn_client_service_init();

    // Additionally tell the ENMS what services are running
    (void) ENMS_NODE_RegisterService(&enmsNode, "udp-service", 1);
    (void) ENMS_NODE_RegisterService(&enmsNode, "mqttsn-service", 1);

    // embeNET network configuration:
    // K1 key, used to authenticate the network node should join and
    // PSK - Node's secret key.
    // Note that the psk value should be preferably stored in secure memory, or be preloaded using custom bootloader.
    const EMBENET_NODE_JoinConfig config = {
        .k1.val = { 0xc0, 0x8b, 0x76, 0x62, 0x77, 0x09, 0x9e, 0x7d, 0x7e, 0x9c, 0x02, 0x22, 0xf1, 0x68, 0xcc, 0x9e },
        .psk.val = {0x46, 0xd7, 0xdc, 0x94, 0xe8, 0xee, 0x74, 0x96, 0xce, 0xaf, 0x54, 0xa3, 0xab, 0x64, 0xcb, 0xeb },
    };

    printf("Trying to join a network...\n\r");
    // Make the node join the network
    EMBENET_NODE_Join(&config);
#endif
  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_BLUE);
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_RED);

  /* Initialize User push-button without interrupt mode. */
  BSP_PB_Init(B1, BUTTON_MODE_GPIO);
  BSP_PB_Init(B2, BUTTON_MODE_GPIO);
  BSP_PB_Init(B3, BUTTON_MODE_GPIO);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
        // Periodically call embeNET Node process function
        EMBENET_NODE_Proc();
#if 1 != IS_ROOT
        // When acting as Node, run the MQTT-SN service process
        mqttsn_client_service_proc();
#endif
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource and SYSCLKDivider
  */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_RC64MPLL;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_RC64MPLL_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_WAIT_STATES_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLK_DIV4;
  PeriphClkInitStruct.KRMRateMultiplier = 4;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief AES Initialization Function
  * @param None
  * @retval None
  */
static void MX_AES_Init(void)
{

  /* USER CODE BEGIN AES_Init 0 */

  /* USER CODE END AES_Init 0 */

  /* USER CODE BEGIN AES_Init 1 */

  /* USER CODE END AES_Init 1 */
  hcryp.Instance = AES;
  hcryp.Init.DataType = CRYP_DATATYPE_32B;
  hcryp.Init.KeySize = CRYP_KEYSIZE_128B;
  hcryp.Init.pKey = (uint32_t *)pKeyAES;
  hcryp.Init.Algorithm = CRYP_AES_ECB;
  hcryp.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_WORD;
  hcryp.Init.HeaderWidthUnit = CRYP_HEADERWIDTHUNIT_WORD;
  hcryp.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;
  if (HAL_CRYP_Init(&hcryp) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN AES_Init 2 */

  /* USER CODE END AES_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 209700;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART1);

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  /**USART1 GPIO Configuration
  PA1   ------> USART1_TX
  PA15   ------> USART1_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_1|LL_GPIO_PIN_15;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_SetTXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_DisableFIFO(USART1);
  LL_USART_ConfigAsyncMode(USART1);

  /* USER CODE BEGIN WKUPType USART1 */

  /* USER CODE END WKUPType USART1 */

  LL_USART_Enable(USART1);

  /* Polling USART1 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(USART1))) || (!(LL_USART_IsActiveFlag_REACK(USART1))))
  {
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief MRSUBG Initialization Function
  * @param None
  * @retval None
  */
static void MX_MRSUBG_Init(void)
{

  /* USER CODE BEGIN MRSUBG_Init 0 */

  /* USER CODE END MRSUBG_Init 0 */

  /* USER CODE BEGIN MRSUBG_Init 1 */

  /* USER CODE END MRSUBG_Init 1 */

  /** Configures the radio parameters
  */
  MRSUBG_RadioInitStruct.lFrequencyBase = 865100000;
  MRSUBG_RadioInitStruct.xModulationSelect = MOD_2GFSK05;
  MRSUBG_RadioInitStruct.lDatarate = 100000;
  MRSUBG_RadioInitStruct.lFreqDev = 25000;
  MRSUBG_RadioInitStruct.lBandwidth = 150000;
  MRSUBG_RadioInitStruct.dsssExp = 0;
  MRSUBG_RadioInitStruct.outputPower = 14;
  MRSUBG_RadioInitStruct.PADrvMode = PA_DRV_TX_HP;
  HAL_MRSubG_Init(&MRSUBG_RadioInitStruct);

  /** Configures the packet parameters
  */
  MRSUBG_PacketSettingsStruct.Modulation = MOD_2FSK;
  MRSUBG_PacketSettingsStruct.PreambleLength = 0x08;
  MRSUBG_PacketSettingsStruct.FCSType = FCS_32BIT;
  MRSUBG_PacketSettingsStruct.Whitening = DISABLE;
  MRSUBG_PacketSettingsStruct.FecType = FEC_15_4_G_NONE;
  MRSUBG_PacketSettingsStruct.FrameLength = MSG_SIZE + FCS_SIZE;
  HAL_MRSubG_802_15_4_PacketInit(&MRSUBG_PacketSettingsStruct);
  /* USER CODE BEGIN MRSUBG_Init 2 */

  /* USER CODE END MRSUBG_Init 2 */

}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  hrng.Init.ClockErrorDetection = RNG_CED_ENABLE;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  LL_TIM_InitTypeDef TIM_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_TIM2);

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 4294967295;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM2, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM2);
  LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);
  LL_TIM_SetTriggerOutput(TIM2, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM2);
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART1 and Loop until the end of transmission */
#if 1 != IS_ROOT
	while (!LL_USART_IsActiveFlag_TXE_TXFNF(USART1)) {
	    ;
	}
    LL_USART_TransmitData8(USART1, ch);
#endif

  return ch;
}

#if defined(__ICCARM__)
size_t __write(int file, unsigned char const *ptr, size_t len)
{
  size_t idx;
  unsigned char const *pdata = ptr;

  for (idx = 0; idx < len; idx++)
  {
    iar_fputc((int)*pdata);
    pdata++;
  }
  return len;
}
#endif /* __ICCARM__ */
/**
 * This hander is called by the embeNET stack when a critical error aborts operation.
 */
__attribute__((noreturn)) void EXPECT_OnAbortHandler(char const *why, char const *file, int line) {
    printf("Program aborted: %s %s:%i\n\r", why, file, line);
    while(1) {
        ;
    }
    __builtin_unreachable();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
        NVIC_SystemReset();
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n\r", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
