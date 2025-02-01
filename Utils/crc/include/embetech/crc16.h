#ifndef CRC16_H_
#define CRC16_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/** @defgroup crc16 CRC 16 bit handling routines.
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
 * Returns CRC initialization value for CCITT.
 */
uint16_t CRC16_CCITT_Init(void);

/**
 * Updates CRC with a single byte of input data using the CCITT algorithm.
 *
 * @param[in] byte byte of data.
 * @param[in] crc current value of CRC.
 *
 * @return new CRC value.
 */
uint16_t CRC16_CCITT_UpdateByte(uint8_t byte, uint16_t crc);

/**
 * Updates CRC with a buffer of input data using the CCITT algorithm.
 *
 * @param[in] in input data buffer.
 * @param[in] size size of input data buffer (in bytes).
 * @param[in] crc current value of CRC.

 * @return new CRC value.
 */
uint16_t CRC16_CCITT_UpdateBuf(void const *in, size_t size, uint16_t crc);

/**
 * Checks CRC validity for a buffer of data by calculating the CRC and comparing it
 * to a given value. Is uses the CCITT algorithm.
 *
 * @param[in] in input buffer.
 * @param[in] size size of the input buffer (in bytes).
 * @param[in] expected expected CRC.
 *
 * @return true when value matches, false otherwise.
 *
 */
bool CRC16_CCITT_Matches(void const *in, size_t size, uint16_t expected);

/**
 * Returns CRC initialization value for MODBUS.
 */
uint16_t CRC16_MODBUS_Init(void);

/**
 * Updates CRC with a single byte of input data using the MODBUS algorithm.
 *
 * @param[in] byte byte of data.
 * @param[in] crc current value of CRC.
 *
 * @return new CRC value.
 */
uint16_t CRC16_MODBUS_UpdateByte(uint8_t byte, uint16_t crc);

/**
 * Updates CRC with a buffer of input data using the MODBUS algorithm.
 *
 * @param[in] in input data buffer.
 * @param[in] size size of input data buffer (in bytes).
 * @param[in] crc current value of CRC.

 * @return new CRC value.
 */
uint16_t CRC16_MODBUS_UpdateBuf(void const *in, size_t size, uint16_t crc);

/**
 * Checks CRC validity for a buffer of data by calculating the CRC and comparing it
 * to a given value. Is uses the MODBUS algorithm.
 *
 * @param[in] in input buffer.
 * @param[in] size size of the input buffer (in bytes).
 * @param[in] expected expected CRC.
 *
 * @return true when calculated value matches, false otherwise.
 *
 */
bool CRC16_MODBUS_Matches(void const *in, size_t size, uint16_t expected);

#if defined __cplusplus
}
#endif

/** @} */

#endif
