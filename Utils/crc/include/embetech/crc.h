/**
 * @file
 * @license   MIT License
 * @copyright Embetech sp. z o.o.
 * @version   2.0.5
 * @purpose   CRC calculation routines
 * @brief     CRC calculation routines
 */

#ifndef EMBETECH_CRC_H_
#define EMBETECH_CRC_H_

#include <embetech/crc16.h>
#include <embetech/crc32.h>
#include <embetech/crc8.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get library version as a NUL-terminated string.
 *
 * @return Pointer to a read-only, statically-allocated string in semantic version format (e.g., "1.2.3+extra_info"). Must not be freed or modified.
 */
char const *CRC_GetVersionString(void);

#ifdef __cplusplus
}
#endif

#endif
