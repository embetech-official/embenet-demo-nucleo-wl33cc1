#if __has_include(<embetech/embetile.h>) && EMBETILE_ENABLED // This macro is defined by invoking embetile_define_component
#include <embetech/embetile.h>

#ifndef EMBETILE_crc_ID
#error "EMBETILE_crc_ID not defined"
#endif

// Define embetile:        name,  id,               arch, verHi,  verLo,  revision
EMBETILE_DEFINE_HEADER(crc, EMBETILE_crc_ID, 0, CRC_VERSION_MAJOR, CRC_VERSION_MINOR, CRC_VERSION_PATCH)

EMBETILE_START_API()
EMBETILE_API_FUNC(CRC8_Init)
EMBETILE_API_FUNC(CRC8_UpdateByte)
EMBETILE_API_FUNC(CRC8_UpdateBuf)
EMBETILE_API_FUNC(CRC16_CCITT_Init)
EMBETILE_API_FUNC(CRC16_CCITT_UpdateByte)
EMBETILE_API_FUNC(CRC16_CCITT_UpdateBuf)
EMBETILE_API_FUNC(CRC16_CCITT_Matches)
EMBETILE_API_FUNC(CRC16_MODBUS_Init)
EMBETILE_API_FUNC(CRC16_MODBUS_UpdateByte)
EMBETILE_API_FUNC(CRC16_MODBUS_UpdateBuf)
EMBETILE_API_FUNC(CRC16_MODBUS_Matches)
EMBETILE_API_FUNC(CRC32_Init)
EMBETILE_API_FUNC(CRC32_UpdateBuf)
EMBETILE_API_FUNC(CRC32_Append)
EMBETILE_API_FUNC(CRC32_Finalize)
EMBETILE_END_API()
#else
typedef int make_iso_compiler_happy;
#endif
