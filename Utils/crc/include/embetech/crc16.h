/**
 * @file
 * @license   MIT License
 * @copyright Embetech sp. z o.o.
 * @version   2.0.5
 * @purpose   16-bit CRC calculation routines
 * @brief     16-bit CRC calculation routines
 */

#ifndef CRC16_H_
#define CRC16_H_

#include <stddef.h>
#include <stdint.h>
/** @defgroup crc16 CRC-16 calculation routines
 *  @code
 *  #include <embetech/crc16.h>
 *  @endcode
 *
 * This module groups utility functions that calculate 16-bit CRC using various
 * algorithms. Currently CCITT and MODBUS algorithms are supported.
 *
 * @{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns CCITT CRC16 initialization value for CCITT.
 */
uint16_t CRC16_CCITT_Init(void);

/**
 * Updates CCITT CRC16 with a buffer of input data using the Look-up-table.
 *
 * @param[in] data input data buffer.
 * @param[in] data_size size of input data buffer (in bytes).
 * @param[in] crc current value of CRC.

 * @return new CCITT CRC16 value.
 */
uint16_t CRC16_CCITT_UpdateUsingLut(void const *data, size_t data_size, uint16_t crc);

/**
 * Updates CCITT CRC16 with a buffer of input data using the polynomial division formula.
 *
 * @param[in] data input data buffer.
 * @param[in] data_size size of input data buffer (in bytes).
 * @param[in] crc current value of CRC.

 * @return new CCITT CRC16 value.
 */
uint16_t CRC16_CCITT_UpdateUsingFormula(void const *data, size_t data_size, uint16_t crc);

/**
 * Finalizes the CCITT CRC16.
 *
 * @param[in] crc current value of CRC.
 *
 * @return final CCITT CRC16 value.
 */
uint16_t CRC16_CCITT_Finalize(uint16_t crc);

/**
 * Returns MODBUS CRC16 initialization value for MODBUS.
 */
uint16_t CRC16_MODBUS_Init(void);

/**
 * Updates MODBUS CRC16 with a buffer of input data using the Look-up-table.
 *
 * @param[in] data input data buffer.
 * @param[in] data_size size of input data buffer (in bytes).
 * @param[in] crc current value of CRC.

 * @return new MODBUS CRC16 value.
 */
uint16_t CRC16_MODBUS_UpdateUsingLut(void const *data, size_t data_size, uint16_t crc);

/**
 * Updates MODBUS CRC16 with a buffer of input data using the polynomial division formula.
 *
 * @param[in] data input data buffer.
 * @param[in] data_size size of input data buffer (in bytes).
 * @param[in] crc current value of CRC.

 * @return new MODBUS CRC16 value.
 */
uint16_t CRC16_MODBUS_UpdateUsingFormula(void const *data, size_t data_size, uint16_t crc);

/**
 * Finalizes the MODBUS CRC16.
 *
 * @param[in] crc current value of CRC.
 *
 * @return final MODBUS CRC16 value.
 */
uint16_t CRC16_MODBUS_Finalize(uint16_t crc);

#if defined __cplusplus
}
#endif

/** @} */

#endif
