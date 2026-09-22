/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET PORT API
 * @brief     Radio interface for the EMBENET NODE Port
 *
 * The IDLE state is implementation defined. The assumption is to balance speed and energy consumption in cross-platform manner.
 * Modern transceivers may not differentiate between SLEEP and STANDBY modes (or consumed power difference is miniscule), so we can prioritize
 * minimizing energy consumption by assuming that RADIO IDLE state is SLEEP.
 * @note     Radio states:
 * UNINITIALIZED  State just after hardware reset.
 * IDLE        In this state radio may remain in low power mode.
 * TX_READY    Prepared for immediate transmission trigger.
 * RX_READY    Prepared for immediate listening trigger.
 * LISTEN      Radio listens for frames.
 * TX          Radio is transmitting frame.
 * RX          Radio is receiving frame.
 * ACTIVE      After TX or RX radio remains in state ready for fast transition to TX_READY or RX_READY.
 * HardwareReset                       -> UNINITIALIZED
 * UNINITIALIZED(EMBENET_RADIO_Init)   -> IDLE
 * IDLE(EMBENET_TxEnable)              -> TX_READY     at idleToTxReady
 * IDLE(EMBENET_RxEnable)              -> RX_READY     at idleToRxReady
 * IDLE(EMBENET_RADIO_Idle)            -> IDLE
 * RX_READY(EMBENET_RADIO_RxNow)       -> LISTEN
 * RX_READY(EMBENET_RADIO_Idle)        -> IDLE
 * TX_READY(EMBENET_RADIO_TxNow)       -> TX         at txDelay
 * TX_READY(EMBENET_RADIO_Idle)        -> IDLE
 * LISTEN(start of frame)              -> RX         at rxDelay
 * LISTEN(EMBENET_RADIO_Idle)          -> IDLE
 * RX(end of frame)                    -> ACTIVE
 * RX(EMBENET_RADIO_Idle)              -> IDLE
 * ACTIVE(EMBENET_TxEnable)             -> TX_READY      at activeToTxReady
 * ACTIVE(EMBENET_RxEnable)            -> RX_READY     at activeToRxReady
 * ACTIVE(EMBENET_RADIO_Idle)          -> IDLE
 */

// clang-format off
/**
*                                                           UNINITIALIZED (after hardware reset)
                                                                |
                                                                | EMBENET_RADIO_Init
                                                                |
                                                               \|/
                  (from any state except UNINITIALIZED) EMBENET_RADIO_Idle ------> IDLE
                                                                |
                                                                |
                                           EMBENET_TxEnable     |     EMBENET_RxEnable
                    -------> TX_READY <--------------------------------------------------------> RX_READY <---------------------------------------------------
                  |             |                                                                   |                                                        |
                  |             |  EMBENET_RADIO_TxNow                                              | EMBENET_RADIO_RxNow                                    |
                  |             | (calls EMBENET_RADIO_CaptureCbt on start of TX frame)             |                                                        |
 EMBENET_TxEnable |            \|/                                                                 \|/                                                       |
                  |            TX                                                                 LISTEN                                                     |
                  |             |                                                                   |                                                        |
                  |             | (calls EMBENET_RADIO_CaptureCbt on end of frame)                  | (calls EMBENET_RADIO_CaptureCbt on start of RX frame)  |
                  |             |                                                                   |                                                        |
                  |            \|/            (calls EMBENET_RADIO_CaptureCbt on end of RX frame)  \|/                                                       |
                  -----------ACTIVE <------------------------------------------------------------- RX                                                        |
                                |                                                                                                                            |
                                |                                           EMBENET_RxEnable                                                                 |
                                ------------------------------------------------------------------------------------------------------------------------------
**/
// clang-format on

#ifndef EMBENET_NODE_PORT_RADIO_H_
#define EMBENET_NODE_PORT_RADIO_H_

#include "embenet_port/timer.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup embenet_node_port_radio Radio Interface
 *
 * Provides interface to the radio transceiver
 *
 * @{
 */

typedef int8_t EMBENET_RADIO_SetParamType; ///< Radio implementation-specific parameter type for set operations.
typedef int8_t EMBENET_RADIO_GetParamType; ///< Radio implementation-specific parameter type for get operations.
typedef uint8_t EMBENET_RADIO_Channel;     ///< Radio channel number.
typedef int8_t EMBENET_RADIO_Power;        ///< Radio power level in dBm.

/**
 * @brief Radio timing and capability parameters reported by the port implementation.
 *
 * All timing fields are worst-case upper bounds in microseconds.
 */
typedef struct {
  EMBENET_TimeUs idleToTxReady;   ///< Maximum time to reach TX_READY from IDLE (@ref EMBENET_RADIO_Idle → TX_READY).
  EMBENET_TimeUs idleToRxReady;   ///< Maximum time to reach RX_READY from IDLE (@ref EMBENET_RADIO_Idle → RX_READY).
  EMBENET_TimeUs activeToTxReady; ///< Maximum time to reach TX_READY from ACTIVE (end-of-frame callback → TX_READY).
  EMBENET_TimeUs activeToRxReady; ///< Maximum time to reach RX_READY from ACTIVE (end-of-frame callback → RX_READY).
  EMBENET_TimeUs txDelay;         ///< Maximum time from TX_READY until the radio signal appears on the antenna port.
  EMBENET_TimeUs rxDelay;         ///< Maximum time from RX_READY until the radio starts listening.
  EMBENET_TimeUs txRxStartDelay;  ///< Time between the appearance of the first preamble bit and the startOfFrame callback.

  EMBENET_RADIO_Power sensitivity;    ///< Minimum receive power (dBm) below which PER rises significantly (e.g. from 0% to 1% for a 30-byte packet).
  EMBENET_RADIO_Power maxOutputPower; ///< Maximum TX output power the radio can produce, in dBm.
  EMBENET_RADIO_Power minOutputPower; ///< Minimum TX output power the radio can produce, in dBm.
} EMBENET_RADIO_Capabilities;

/**
 * @brief Radio layer operation status codes.
 */
typedef enum {
  EMBENET_RADIO_STATUS_SUCCESS             = 0,   ///< Operation completed successfully.
  EMBENET_RADIO_STATUS_GENERAL_ERROR       = -1,  ///< Unspecified error.
  EMBENET_RADIO_STATUS_COMMUNICATION_ERROR = -2,  ///< Radio hardware communication error (e.g. SPI failure).
  EMBENET_RADIO_STATUS_WRONG_STATE         = -3,  ///< Function called in an incorrect radio state.
  EMBENET_RADIO_STATUS_CHANNEL_BUSY        = -4,  ///< The requested channel is busy (CCA failure).

  EMBENET_RADIO_STATUS_PARAMETER_NOT_IMPLEMENTED    = -30, ///< The requested parameter is not supported by this implementation.
  EMBENET_RADIO_STATUS_PARAMETER_ARGS_WRONG_NUMBER  = -31, ///< Wrong number of arguments provided for the parameter.
  EMBENET_RADIO_STATUS_PARAMETER_ARG1_OUT_OF_BOUNDS = -32, ///< First argument is out of the allowed range.
  EMBENET_RADIO_STATUS_PARAMETER_ARG2_OUT_OF_BOUNDS = -33, ///< Second argument is out of the allowed range.
  EMBENET_RADIO_STATUS_PARAMETER_ARG3_OUT_OF_BOUNDS = -34, ///< Third argument is out of the allowed range.
  EMBENET_RADIO_STATUS_PARAMETER_ARGS_OUT_OF_BOUNDS = -35, ///< One or more arguments are out of the allowed range.
} EMBENET_RADIO_Status;

/**
 * @brief PSDU length limits.
 */
enum {
  EMBENET_RADIO_MAX_PSDU_LENGTH = 128, ///< Maximum allowed PSDU length in bytes.
  EMBENET_RADIO_MIN_PSDU_LENGTH = 1,   ///< Minimum allowed PSDU length in bytes.
};

/**
 * @brief Timestamped radio event callback.
 *
 * Called by the radio driver to report a frame boundary event (start or end of frame).
 *
 * @param[in] context opaque context pointer as provided to @ref EMBENET_RADIO_SetCallbacks.
 * @param[in] timestamp hardware timer value at the moment of the event, in microseconds.
 */
typedef void (*EMBENET_RADIO_CaptureCbt)(void *context, EMBENET_TimeUs timestamp);

/**
 * @brief Information about a received frame, filled by @ref EMBENET_RADIO_GetReceivedFrame.
 */
typedef struct {
  EMBENET_RADIO_Power rssi; ///< Received Signal Strength Indicator in dBm.
  uint8_t lqi;              ///< Link Quality Indicator (implementation-defined scale).
  bool crcValid;            ///< true if the CRC check passed; always false when mpduLength is outside [EMBENET_RADIO_MIN_PSDU_LENGTH, EMBENET_RADIO_MAX_PSDU_LENGTH].
  size_t mpduLength;        ///< Number of bytes written into the caller-supplied buffer (clamped to bufferLength).
} EMBENET_RADIO_RxInfo;

/**
 * @brief Continuous transmission mode.
 */
typedef enum {
  EMBENET_RADIO_CONTINUOUS_TX_MODE_PN9,     ///< Continuous transmission of a PN9 pseudo-random sequence.
  EMBENET_RADIO_CONTINUOUS_TX_MODE_CARRIER, ///< Continuous unmodulated carrier wave.
} EMBENET_RADIO_ContinuousTxMode;

/**
 * @brief Initializes the radio transceiver and places it in the IDLE state.
 *
 * @retval EMBENET_RADIO_STATUS_SUCCESS on success
 * @retval EMBENET_RADIO_STATUS_COMMUNICATION_ERROR if the radio hardware does not respond
 */
EMBENET_RADIO_Status EMBENET_RADIO_Init(void);

/**
 * @brief Registers frame boundary callbacks.
 *
 * @param[in] onStartFrame callback invoked when the sync word of an incoming or outgoing frame is detected,
 *                         with a back-calculated timestamp of the first bit; NULL disables this callback.
 * @param[in] onEndFrame   callback invoked when the last bit of a frame has been transmitted or received; NULL disables this callback.
 * @param[in] cbtContext   opaque pointer passed as the first argument to both callbacks.
 */
void EMBENET_RADIO_SetCallbacks(EMBENET_RADIO_CaptureCbt onStartFrame, EMBENET_RADIO_CaptureCbt onEndFrame, void *cbtContext);

/**
 * @brief Deinitializes the radio transceiver and places it in the lowest energy consumption mode available.
 */
void EMBENET_RADIO_Deinit(void);

/**
 * @brief Aborts any ongoing reception or transmission, clears internal buffers, and places the radio in the IDLE state.
 *
 * May be called from any state except UNINITIALIZED.
 *
 * @retval EMBENET_RADIO_STATUS_SUCCESS on success
 * @retval EMBENET_RADIO_STATUS_COMMUNICATION_ERROR if the radio hardware does not respond
 */
EMBENET_RADIO_Status EMBENET_RADIO_Idle(void);

/**
 * @brief Wakes the transceiver from IDLE and loads a frame into the TX buffer ready for immediate transmission.
 *
 * Transitions the radio from IDLE to TX_READY. The frame data pointed to by @p psdu must remain valid
 * until @ref EMBENET_RADIO_TxNow has been called and the end-of-frame callback has fired.
 *
 * @param[in] channel radio channel to transmit on
 * @param[in] txp     transmit power in dBm
 * @param[in] psdu    pointer to the frame payload; must not be NULL
 * @param[in] psduLen frame length in bytes; must be in the range [EMBENET_RADIO_MIN_PSDU_LENGTH, EMBENET_RADIO_MAX_PSDU_LENGTH]
 *
 * @retval EMBENET_RADIO_STATUS_SUCCESS on success
 * @retval EMBENET_RADIO_STATUS_PARAMETER_ARGS_OUT_OF_BOUNDS if @p psduLen is outside the valid range
 * @retval EMBENET_RADIO_STATUS_COMMUNICATION_ERROR if the radio hardware does not respond
 */
EMBENET_RADIO_Status EMBENET_RADIO_TxEnable(EMBENET_RADIO_Channel channel, EMBENET_RADIO_Power txp, uint8_t const *psdu, size_t psduLen);

/**
 * @brief Triggers immediate transmission of the frame previously loaded by @ref EMBENET_RADIO_TxEnable.
 *
 * Transitions the radio from TX_READY to TX.
 *
 * @retval EMBENET_RADIO_STATUS_SUCCESS on success
 * @retval EMBENET_RADIO_STATUS_COMMUNICATION_ERROR if the radio hardware does not respond
 */
EMBENET_RADIO_Status EMBENET_RADIO_TxNow(void);

/**
 * @brief Wakes the transceiver from IDLE and prepares it for reception.
 *
 * Transitions the radio from IDLE to RX_READY.
 *
 * @param[in] channel radio channel to listen on
 *
 * @retval EMBENET_RADIO_STATUS_SUCCESS on success
 * @retval EMBENET_RADIO_STATUS_COMMUNICATION_ERROR if the radio hardware does not respond
 * @retval EMBENET_RADIO_STATUS_WRONG_STATE if the radio is not in a state that allows this transition
 */
EMBENET_RADIO_Status EMBENET_RADIO_RxEnable(EMBENET_RADIO_Channel channel);

/**
 * @brief Triggers immediate listening.
 *
 * Transitions the radio from RX_READY to LISTEN.
 *
 * @retval EMBENET_RADIO_STATUS_SUCCESS on success
 * @retval EMBENET_RADIO_STATUS_COMMUNICATION_ERROR if the radio hardware does not respond
 */
EMBENET_RADIO_Status EMBENET_RADIO_RxNow(void);

/**
 * @brief Copies the last received frame into the caller-supplied buffer.
 *
 * Must be called after the @c onEndFrame callback fires. Up to @p bufferLength bytes are written into @p buffer.
 * The @ref EMBENET_RADIO_RxInfo::mpduLength field in the returned structure reflects the number of bytes actually
 * written (clamped to @p bufferLength). If the received frame was longer than @p bufferLength, @ref EMBENET_RADIO_RxInfo::crcValid
 * is set to false.
 *
 * @param[out] buffer       destination buffer; must not be NULL
 * @param[in]  bufferLength size of @p buffer in bytes; should be at least EMBENET_RADIO_MAX_PSDU_LENGTH to avoid truncation
 *
 * @return @ref EMBENET_RADIO_RxInfo describing the received frame.
 */
EMBENET_RADIO_RxInfo EMBENET_RADIO_GetReceivedFrame(uint8_t *buffer, size_t bufferLength);

/**
 * @brief Returns the radio timing and capability parameters for this port implementation.
 *
 * @note Values are determined empirically by the port implementor and must be worst-case upper bounds.
 *
 * @return Pointer to a @ref EMBENET_RADIO_Capabilities structure; never NULL. The pointed-to data is valid for the lifetime of the application.
 */
EMBENET_RADIO_Capabilities const *EMBENET_RADIO_GetCapabilities(void);

/**
 * @brief Starts continuous transmission for radio testing purposes.
 *
 * @param[in] mode    continuous TX mode (PN9 sequence or unmodulated carrier)
 * @param[in] channel radio channel to transmit on
 * @param[in] txp     transmit power in dBm
 *
 * @retval EMBENET_RADIO_STATUS_SUCCESS on success
 * @retval EMBENET_RADIO_STATUS_COMMUNICATION_ERROR if the radio hardware does not respond
 */
EMBENET_RADIO_Status EMBENET_RADIO_StartContinuousTx(EMBENET_RADIO_ContinuousTxMode mode, EMBENET_RADIO_Channel channel, EMBENET_RADIO_Power txp);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // EMBENET_RADIO_H_ included
