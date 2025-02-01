/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     Implementation of radio transceiver interface for embeNET Node
 */

#include <embenet_port/critical_section.h>
#include <embenet_port/radio.h>
#include <embenet_port/timer.h>
#include <embetech/expect.h>

#include "embenet_port_interrupt_priorities.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <stm32wl3x_hal.h>
#pragma GCC diagnostic pop

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/// @brief Set toggle pins to 1 to enable toggling pins for debugging purposes
#define TOGGLE_PINS 0

#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <stm32wl3x_ll_bus.h>
#include <stm32wl3x_ll_gpio.h>
#include <stm32wl3x_ll_rcc.h>
#pragma GCC diagnostic pop

typedef enum {
  /// do not change order, nor count of entries without pins variable update
  PIN_1 = 0, // GPIOA_PIN_6 GPIO28 MORPHO_CN4_3
  PIN_2,     // GPIOA_PIN_7 GPIO29 MORPHO_CN4_5
  PIN_3,     // GPIOA_PIN_5 GPIO41 MORPHO_CN4_21
  PIN_4      // GPIOA_PIN_13 GPIO47 MORPHO_CN4_27
} PIN;
static uint32_t const pins[4] = {LL_GPIO_PIN_6, LL_GPIO_PIN_7, LL_GPIO_PIN_5, LL_GPIO_PIN_13};

static void PINS_Init(void) {
  static LL_GPIO_InitTypeDef gpioInit = {
      .Pin = pins[0] | pins[1] | pins[2] | pins[3],
      .Mode = LL_GPIO_MODE_OUTPUT,
      .Speed = LL_GPIO_SPEED_FREQ_HIGH,
      .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
      .Pull = LL_GPIO_PULL_DOWN,
  };
  __HAL_RCC_GPIOA_CLK_ENABLE();
  LL_GPIO_Init(GPIOA, &gpioInit);
}
static void PINS_High(PIN pin) { LL_GPIO_SetOutputPin(GPIOA, pins[pin]); }
static void PINS_Low(PIN pin) { LL_GPIO_ResetOutputPin(GPIOA, pins[pin]); }
#endif // defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)

// structure to hold radio variables and states
#define DATA_BUFFER_LENGTH (((EMBENET_RADIO_MAX_PSDU_LENGTH + 4) / 4 + 1) * 4) ///< RRM always performs 4B word write and read operation
typedef struct {
  EMBENET_RADIO_CaptureCbt onFrameStart; ///< handler to method called when start of frame interrupt occurs
  EMBENET_RADIO_CaptureCbt onFrameEnd;   ///< handler to method called when end of frame interrupt occurs
  void *handlersContext;                 ///< context passed to hanlders
  bool frameReady;                       ///< denotes if frame is ready
  bool frameCrcIsValid;                  ///< denotes if ready frame crc is valid
  int32_t frameRssi;
  /// RRM always performs 4B word write and read operation, buffer always 1B longer than expected packet payload
  uint8_t dataBuffer[DATA_BUFFER_LENGTH] __attribute__((aligned(4)));
} EMBENET_RADIO_Descriptor;

static EMBENET_RADIO_Descriptor d;

enum {
  IdleToTxReadyUs = (90 + 100),
  IdleToRxReadyUs = (90 + 100),
  ActiveToTxReadyUs = (90 + 100),
  ActiveToRxReadyUs = (90 + 100),
  TxDelayUs = (425),
  RxDelayUs = TxDelayUs, // between GO signal and start listening - cannot measure but could be the same as delayTx
  TxRxStartDelayUs = (1260),

  TxStartOffsetUs = (425), // difference between the the appearance of first bit of preamble on radio interface and TX StartOfFrame callback (added to
                           // Tx StartOfFrame callback)
  RxEndOffsetUs = (291),   // difference between the RX EndOfFrame and TX EndOfFrame callback (added to TX EndOfFrame)

  MaxTxpDbm = 14,
  MinTxpDbm = 0,
  MaxChannel = 68,
  MinChannel = 0,
  SensitivityDbm = -100,

  ChannelWidthHz = 100000,
  BaseFrequencyHz = 863100000 + 4000, /*calibration offset*/
};

EMBENET_RADIO_Status EMBENET_RADIO_Init(void) {

#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_Init();
#endif

  __HAL_RCC_MRSUBG_CLK_ENABLE();

  d.frameCrcIsValid = false;
  d.frameReady = false;
  d.onFrameStart = NULL;
  d.onFrameEnd = NULL;
  d.handlersContext = NULL;

  static SMRSubGConfig initRadio = {
      .lFrequencyBase = BaseFrequencyHz,
      .xModulationSelect = MOD_2FSK,
      .lDatarate = 50000,
      .lFreqDev = 12500,
      .lBandwidth = ChannelWidthHz,
      .dsssExp = 0,
  };
  uint8_t err = HAL_MRSubG_Init(&initRadio);
  EXPECT(err == 0) OR_ABORT("Radio initialization problem");

  static MRSubG_802_15_4_PcktFields initPckt = {
      .Modulation = MOD_2FSK,
      .PreambleLength = 6,
      .FCSType = FCS_32BIT,
      .Whitening = DISABLE,
      .FrameLength = EMBENET_RADIO_MAX_PSDU_LENGTH + 4,
  };
  HAL_MRSubG_802_15_4_PacketInit(&initPckt);
  LL_MRSubG_SetTXMode(TX_NORMAL);
  LL_MRSUBG_SetFixedVariableLength(VARIABLE);
  HAL_MRSubG_SetPALeveldBm(7, 14, PA_DRV_TX_HP);
  SET_BIT(MR_SUBG_GLOB_DYNAMIC->COMMAND, MR_SUBG_GLOB_DYNAMIC_COMMAND_BACK2ACTIVE);

  // init and enable IRQs
  MR_SUBG_GLOB_DYNAMIC->RFSEQ_IRQ_ENABLE = MR_SUBG_GLOB_DYNAMIC_RFSEQ_IRQ_ENABLE_SYNC_VALID_E | MR_SUBG_GLOB_DYNAMIC_RFSEQ_IRQ_ENABLE_RX_CRC_ERROR_E |
                                           MR_SUBG_GLOB_DYNAMIC_RFSEQ_IRQ_ENABLE_RX_OK_E | MR_SUBG_GLOB_DYNAMIC_RFSEQ_IRQ_ENABLE_TX_DONE_E;

  NVIC_SetPriority(MR_SUBG_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), INTERRUPT_PRIORITY_RADIO, INTERRUPT_SUBPRIORITY_RADIO));
  NVIC_ClearPendingIRQ(MR_SUBG_IRQn);
  NVIC_EnableIRQ(MR_SUBG_IRQn);

  // set data buffer
  MR_SUBG_GLOB_STATIC->DATABUFFER0_PTR = (uint32_t)d.dataBuffer;
  MR_SUBG_GLOB_STATIC->DATABUFFER1_PTR = (uint32_t)d.dataBuffer;
  MODIFY_REG_FIELD(MR_SUBG_GLOB_STATIC->DATABUFFER_SIZE, MR_SUBG_GLOB_STATIC_DATABUFFER_SIZE_DATABUFFER_SIZE, DATA_BUFFER_LENGTH);
  LL_MRSubG_StrobeCommand(CMD_SABORT);

  return EMBENET_RADIO_STATUS_SUCCESS;
}

void EMBENET_RADIO_SetCallbacks(EMBENET_RADIO_CaptureCbt onStartFrame, EMBENET_RADIO_CaptureCbt onEndFrame, void *cbtContext) {
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_High(PIN_1);
#endif
  d.onFrameStart = onStartFrame;
  d.onFrameEnd = onEndFrame;
  d.handlersContext = cbtContext;
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_Low(PIN_1);
#endif
}

void EMBENET_RADIO_Deinit(void) {
  d.onFrameStart = NULL;
  d.onFrameEnd = NULL;
}

EMBENET_RADIO_Status EMBENET_RADIO_Idle(void) {
  LL_MRSubG_SetTXMode(TX_NORMAL); // in case of return from Continuous Tx mode
  LL_MRSubG_StrobeCommand(CMD_SABORT);
  return EMBENET_RADIO_STATUS_SUCCESS;
}

EMBENET_RADIO_Status EMBENET_RADIO_TxEnable(EMBENET_RADIO_Channel channel, EMBENET_RADIO_Power txp, uint8_t const *psdu, size_t psduLen) {
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_High(PIN_1);
#endif
  LL_MRSubG_StrobeCommand(CMD_SABORT);
  LL_MRSubG_StrobeCommand(CMD_LOCKTX);
  if((psduLen > EMBENET_RADIO_MAX_PSDU_LENGTH) || (psduLen < 2) || (channel > MaxChannel)) {
    return EMBENET_RADIO_STATUS_GENERAL_ERROR;
  }
  // allow out of bounds power
  if(txp > MaxTxpDbm) {
    txp = MaxTxpDbm;
  } else if(txp < MinTxpDbm) {
    txp = MinTxpDbm;
  }
  HAL_MRSubG_SetPALeveldBm(7, txp, PA_DRV_TX_HP);
  HAL_MRSubG_SetFrequencyBase(BaseFrequencyHz + (uint32_t)channel * ChannelWidthHz);
  LL_MRSUBG_SetPacketLength((uint16_t)(psduLen + 4 /* 4B of CRC */));
  memcpy(d.dataBuffer, psdu, psduLen);
  MR_SUBG_GLOB_STATIC->DATABUFFER0_PTR = (uint32_t)d.dataBuffer;
  MR_SUBG_GLOB_STATIC->DATABUFFER1_PTR = (uint32_t)d.dataBuffer;
  d.frameCrcIsValid = false;
  d.frameReady = false;
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_Low(PIN_1);
#endif
  return EMBENET_RADIO_STATUS_SUCCESS;
}

EMBENET_RADIO_Status EMBENET_RADIO_TxNow(void) {
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_High(PIN_1);
#endif
  LL_MRSubG_StrobeCommand(CMD_TX);
  if(d.onFrameStart) {
    d.onFrameStart(d.handlersContext, EMBENET_TIMER_ReadCounter() + TxStartOffsetUs);
  }
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_Low(PIN_1);
#endif
  return EMBENET_RADIO_STATUS_SUCCESS;
}

EMBENET_RADIO_Status EMBENET_RADIO_RxEnable(EMBENET_RADIO_Channel channel) {
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_High(PIN_1);
#endif
  LL_MRSubG_StrobeCommand(CMD_SABORT);
  LL_MRSubG_StrobeCommand(CMD_LOCKRX);
  if(channel > MaxChannel) {
    return EMBENET_RADIO_STATUS_GENERAL_ERROR;
  }
  LL_MRSUBG_SetPacketLength(EMBENET_RADIO_MAX_PSDU_LENGTH + 4 /* 4B of CRC*/);
  HAL_MRSubG_SetFrequencyBase(BaseFrequencyHz + (uint32_t)channel * ChannelWidthHz);
  MR_SUBG_GLOB_STATIC->DATABUFFER0_PTR = (uint32_t)d.dataBuffer;
  MR_SUBG_GLOB_STATIC->DATABUFFER1_PTR = (uint32_t)d.dataBuffer;
  d.frameCrcIsValid = false;
  d.frameReady = false;
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_Low(PIN_1);
#endif

  return EMBENET_RADIO_STATUS_SUCCESS;
}

EMBENET_RADIO_Status EMBENET_RADIO_RxNow(void) {
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_High(PIN_1);
#endif
  LL_MRSubG_StrobeCommand(CMD_RX);
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_Low(PIN_1);
#endif
  return EMBENET_RADIO_STATUS_SUCCESS;
}

EMBENET_RADIO_RxInfo EMBENET_RADIO_GetReceivedFrame(uint8_t *buffer, size_t bufferLength) {
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_High(PIN_1);
#endif
  EMBENET_RADIO_RxInfo info = {.crcValid = false, .lqi = 0, .mpduLength = 0, .rssi = INT8_MIN};

  EXPECT(buffer) OR_RETURN(info);
  EXPECT(bufferLength) OR_RETURN(info);

  if(d.frameReady) {
    size_t length = READ_REG_FIELD(MR_SUBG_GLOB_STATUS->DATABUFFER_INFO, MR_SUBG_GLOB_STATUS_DATABUFFER_INFO_CURRENT_DATABUFFER_COUNT);

    info.lqi = 0;
    info.rssi = (EMBENET_RADIO_Power)d.frameRssi;
    info.crcValid = d.frameCrcIsValid;

    info.mpduLength = length;

    if(length > EMBENET_RADIO_MAX_PSDU_LENGTH) {
      // frame too long
      info.crcValid = false;
      length = EMBENET_RADIO_MAX_PSDU_LENGTH;
    }
    if(length > bufferLength) {
      // frame wont fit into buffer
      info.crcValid = false;
      length = (uint16_t)bufferLength; // uint8_t overflow not possible
    }
    if(length < EMBENET_RADIO_MIN_PSDU_LENGTH) {
      // frame too short
      info.crcValid = false;
    }
    memcpy(buffer, d.dataBuffer, length);
  }
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_Low(PIN_1);
#endif
  return info;
}

EMBENET_RADIO_Status EMBENET_RADIO_StartContinuousTx(EMBENET_RADIO_ContinuousTxMode mode, EMBENET_RADIO_Channel channel, EMBENET_RADIO_Power txp) {
  if(EMBENET_RADIO_CONTINUOUS_TX_MODE_PN9 == mode) {
    LL_MRSubG_StrobeCommand(CMD_SABORT);
    LL_MRSubG_StrobeCommand(CMD_LOCKTX);
    // allow out of bounds power
    if(txp > MaxTxpDbm) {
      txp = MaxTxpDbm;
    } else if(txp < MinTxpDbm) {
      txp = MinTxpDbm;
    }
    HAL_MRSubG_SetPALeveldBm(7, txp, PA_DRV_TX_HP);
    HAL_MRSubG_SetFrequencyBase(BaseFrequencyHz + (uint32_t)channel * ChannelWidthHz);
    LL_MRSubG_SetTXMode(TX_PN);
    LL_MRSubG_StrobeCommand(CMD_TX);

    return EMBENET_RADIO_STATUS_SUCCESS;
  }

  return EMBENET_RADIO_STATUS_GENERAL_ERROR;
}

EMBENET_RADIO_Capabilities const *EMBENET_RADIO_GetCapabilities(void) {
  static EMBENET_RADIO_Capabilities timings = {.idleToTxReady = IdleToTxReadyUs,
                                               .idleToRxReady = IdleToRxReadyUs,
                                               .activeToTxReady = ActiveToTxReadyUs,
                                               .activeToRxReady = ActiveToRxReadyUs,
                                               .txDelay = TxDelayUs,
                                               .rxDelay = RxDelayUs,
                                               .txRxStartDelay = TxRxStartDelayUs,
                                               .sensitivity = SensitivityDbm,
                                               .maxOutputPower = MaxTxpDbm,
                                               .minOutputPower = MinTxpDbm};
  return &timings;
}

void HAL_MRSubG_IRQ_Callback(void) { EXPECT_ABORT("LOL"); }

void MRSUBG_IRQHandler(void) {
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_High(PIN_2);
#endif
  EMBENET_TimeUs timestamp = EMBENET_TIMER_ReadCounter();
  uint32_t irq = READ_REG(MR_SUBG_GLOB_STATUS->RFSEQ_IRQ_STATUS);

  if(irq & MR_SUBG_GLOB_DYNAMIC_RFSEQ_IRQ_ENABLE_RX_CRC_ERROR_E) {
    MR_SUBG_GLOB_STATUS->RFSEQ_IRQ_STATUS = MR_SUBG_GLOB_DYNAMIC_RFSEQ_IRQ_ENABLE_RX_CRC_ERROR_E;

    LL_MRSubG_StrobeCommand(CMD_SABORT);

    d.frameCrcIsValid = false;
    d.frameReady = true;
    d.frameRssi = HAL_MRSubG_GetRssidBm();

    if(d.onFrameEnd) {
      d.onFrameEnd(d.handlersContext, timestamp);
    }
  }
  if(irq & MR_SUBG_GLOB_STATUS_RFSEQ_IRQ_STATUS_RX_OK_F) {
    MR_SUBG_GLOB_STATUS->RFSEQ_IRQ_STATUS = MR_SUBG_GLOB_STATUS_RFSEQ_IRQ_STATUS_RX_OK_F;
    LL_MRSubG_StrobeCommand(CMD_SABORT);

    d.frameReady = true;
    d.frameCrcIsValid = true;
    d.frameRssi = HAL_MRSubG_GetRssidBm();

    if(d.onFrameEnd) {
      d.onFrameEnd(d.handlersContext, timestamp);
    }
  }

  if(irq & MR_SUBG_GLOB_STATUS_RFSEQ_IRQ_STATUS_TX_DONE_F) {
    /* Clear the IRQ flag */
    MR_SUBG_GLOB_STATUS->RFSEQ_IRQ_STATUS = MR_SUBG_GLOB_STATUS_RFSEQ_IRQ_STATUS_TX_DONE_F;
    LL_MRSubG_StrobeCommand(CMD_SABORT);

    if(d.onFrameEnd) {
      d.onFrameEnd(d.handlersContext, timestamp + RxEndOffsetUs);
    }
  }

  if(irq & MR_SUBG_GLOB_DYNAMIC_RFSEQ_IRQ_ENABLE_SYNC_VALID_E) {
    MR_SUBG_GLOB_STATUS->RFSEQ_IRQ_STATUS = MR_SUBG_GLOB_DYNAMIC_RFSEQ_IRQ_ENABLE_SYNC_VALID_E;
    if(d.onFrameStart) {
      d.onFrameStart(d.handlersContext, timestamp - TxRxStartDelayUs);
    }
  }
#if defined(TOGGLE_PINS) && (TOGGLE_PINS == 1)
  PINS_Low(PIN_2);
#endif
}
