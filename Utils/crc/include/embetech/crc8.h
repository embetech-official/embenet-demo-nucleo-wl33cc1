/**
 * @file
 * @license   MIT License
 * @copyright Embetech sp. z o.o.
 * @version   2.0.5
 * @purpose   8-bit CRC calculation routines
 * @brief     8-bit CRC calculation routines
 */

#ifndef CRC8_H_
#define CRC8_H_

#include <stddef.h>
#include <stdint.h>
/** @defgroup crc8 CRC-8 calculation routines
 *  @code
 *  #include <embetech/crc8.h>
 *  @endcode
 *
 * This module groups utility functions that calculate 8-bit CRC using a simple algorithm.
 *
 * @{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns CRC initialization value.
 */
uint8_t CRC8_ITU_Init(void);

/**
 * Updates ITU CRC8 with a buffer of input data using the polynomial division formula.
 *
 * @param[in] data input data buffer.
 * @param[in] data_size size of input data buffer (in bytes).
 * @param[in] crc current value of CRC.
 *
 * @return new CRC value.
 */
uint8_t CRC8_ITU_UpdateUsingFormula(void const *data, size_t data_size, uint8_t crc);

/**
 * Updates ITU CRC8 with a buffer of input data using the Look-up-table.
 *
 * @param[in] data input data buffer.
 * @param[in] data_size size of input data buffer (in bytes).
 * @param[in] crc current value of CRC.

 * @return new CRC value.
 */
uint8_t CRC8_ITU_UpdateUsingLut(void const *data, size_t data_size, uint8_t crc);

/**
 * Finalizes the CRC.
 *
 * @param[in] crc current value of CRC.
 *
 * @return final CRC value.
 */
uint8_t CRC8_ITU_Finalize(uint8_t crc);

#ifdef __cplusplus
}
#endif

/** @} */

#endif
