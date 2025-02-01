#include "embetech/crc16.h"

#if __has_include(<embetech/embetile.h>) && EMBETILE_ENABLED // This macro is defined by invoking embetile_define_component
#include <embetech/embetile.h>
// mark API functions - this enables to use them as embetile API
uint16_t CRC16_CCITT_Ini(void) EMBETILE(CRC16_CCITT_Init);
uint16_t CRC16_CCITT_UpdateByte(uint8_t byte, uint16_t crc) EMBETILE(CRC16_CCITT_UpdateByte);
uint16_t CRC16_CCITT_UpdateBuf(void const *buf, size_t size, uint16_t crc) EMBETILE(CRC16_CCITT_UpdateBuf);
bool CRC16_CCITT_Matches(void const *buf, size_t size, uint16_t crc) EMBETILE(CRC16_CCITT_Matches);
uint16_t CRC16_MODBUS_Init(void) EMBETILE(CRC16_MODBUS_InitCRC);
uint16_t CRC16_MODBUS_UpdateByte(uint8_t byte, uint16_t crc) EMBETILE(CRC16_MODBUS_UpdateByte);
uint16_t CRC16_MODBUS_UpdateBuf(void const *buf, size_t size, uint16_t crc) EMBETILE(CRC16_MODBUS_UpdateBuf);
bool CRC16_MODBUS_Matches(void const *buf, size_t size, uint16_t crc) EMBETILE(CRC16_MODBUS_Matches);
#endif

#ifndef CRC16_CCITT_USE_LUT
/// Enable look-up table usage for CCITT.
#define CRC16_CCITT_USE_LUT 1
#endif

#ifndef CRC16_MODBUS_USE_LUT
/// Enable look-up table usage for MODBUS.
#define CRC16_MODBUS_USE_LUT 0
#endif

#if defined CRC16_CCITT_USE_LUT && (CRC16_CCITT_USE_LUT == 1)
static uint16_t CRC16_CCITTLUT[256] = {
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf, 0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7, 0x1081, 0x0108,
    0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e, 0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876, 0x2102, 0x308b, 0x0210, 0x1399,
    0x6726, 0x76af, 0x4434, 0x55bd, 0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5, 0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e,
    0x54b5, 0x453c, 0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974, 0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
    0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3, 0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a, 0xdecd, 0xcf44,
    0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72, 0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9, 0xef4e, 0xfec7, 0xcc5c, 0xddd5,
    0xa96a, 0xb8e3, 0x8a78, 0x9bf1, 0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738, 0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862,
    0x9af9, 0x8b70, 0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7, 0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
    0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036, 0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e, 0xa50a, 0xb483,
    0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5, 0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd, 0xb58b, 0xa402, 0x9699, 0x8710,
    0xf3af, 0xe226, 0xd0bd, 0xc134, 0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c, 0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1,
    0xa33a, 0xb2b3, 0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb, 0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
    0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a, 0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1, 0x6b46, 0x7acf,
    0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9, 0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330, 0x7bc7, 0x6a4e, 0x58d5, 0x495c,
    0x3de3, 0x2c6a, 0x1ef1, 0x0f78};
#endif

#if defined CRC16_MODBUS_USE_LUT && (CRC16_MODBUS_USE_LUT == 1)

static uint16_t CRC16_MODBUSLUT[] = {
    0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241, 0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440, 0XCC01, 0X0CC0,
    0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40, 0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841, 0XD801, 0X18C0, 0X1980, 0XD941,
    0X1B00, 0XDBC1, 0XDA81, 0X1A40, 0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41, 0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0,
    0X1680, 0XD641, 0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040, 0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
    0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441, 0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41, 0XFA01, 0X3AC0,
    0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840, 0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41, 0XEE01, 0X2EC0, 0X2F80, 0XEF41,
    0X2D00, 0XEDC1, 0XEC81, 0X2C40, 0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640, 0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0,
    0X2080, 0XE041, 0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240, 0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
    0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41, 0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840, 0X7800, 0XB8C1,
    0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41, 0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40, 0XB401, 0X74C0, 0X7580, 0XB541,
    0X7700, 0XB7C1, 0XB681, 0X7640, 0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041, 0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0,
    0X5280, 0X9241, 0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440, 0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
    0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841, 0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40, 0X4E00, 0X8EC1,
    0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41, 0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641, 0X8201, 0X42C0, 0X4380, 0X8341,
    0X4100, 0X81C1, 0X8081, 0X4040};

#endif

uint16_t CRC16_CCITT_Init(void) { return 0xFFFFU; }

uint16_t CRC16_MODBUS_Init(void) { return 0xFFFFU; }

uint16_t CRC16_CCITT_UpdateByte(uint8_t byte, uint16_t crc) {
#if defined CRC16_CCITT_USE_LUT && (CRC16_CCITT_USE_LUT == 1)
  // use look-up-table
  return (uint16_t)(crc >> 8) ^ CRC16_CCITTLUT[(uint16_t)(crc ^ byte) & 0xff];
#else
  // not using look-up-table
  byte ^= (uint8_t)(crc & 0x00ff);
  byte ^= (uint8_t)(byte << 4);

  return ((((uint16_t)byte << 8) | (uint8_t)(crc >> 8)) ^ (uint8_t)(byte >> 4) ^ ((uint16_t)byte << 3));
#endif
}

uint16_t CRC16_MODBUS_UpdateByte(uint8_t byte, uint16_t crc) {
#if defined CRC16_MODBUS_USE_LUT && (CRC16_MODBUS_USE_LUT == 1)
  // use look-up-table
  uint8_t temp8 = (uint8_t)(byte ^ crc);
  crc = (uint16_t)(crc >> 8U);
  return (uint16_t)(crc ^ CRC16_MODBUSLUT[temp8]);
#else
  uint16_t temp16;
  int bit;

  // not using look-up-table
  for(bit = 0; bit < 8; bit++) {
    temp16 = byte ^ (unsigned char)crc;
    crc >>= 1;
    if(temp16 & 0x01) {
      crc ^= 0xa001;
    }
    byte >>= 1;
  }
  return crc;
#endif
}

uint16_t CRC16_CCITT_UpdateBuf(void const *buf, size_t size, uint16_t crc) {
  for(size_t i = 0; i < size; i++) {
    crc = CRC16_CCITT_UpdateByte(((uint8_t const *)buf)[i], crc);
  }
  return crc;
}

uint16_t CRC16_MODBUS_UpdateBuf(void const *buf, size_t size, uint16_t crc) {
  for(size_t i = 0; i < size; i++) {
    crc = CRC16_MODBUS_UpdateByte(((uint8_t const *)buf)[i], crc);
  }
  return crc;
}

bool CRC16_CCITT_Matches(void const *buf, size_t size, uint16_t crc) {
  // calculate CRC of the input buffer
  uint16_t buf_crc = CRC16_CCITT_UpdateBuf(buf, size, CRC16_CCITT_Init());

  // compare values
  return (buf_crc == crc);
}

bool CRC16_MODBUS_CheckCRC(void const *buf, size_t size, uint16_t crc) {
  // calculate CRC of the input buffer
  uint16_t buf_crc = CRC16_MODBUS_UpdateBuf(buf, size, CRC16_MODBUS_Init());

  // compare values
  return (buf_crc == crc);
}

/*! \file crc16.c
    \brief 16-bit CRC calculation routines
*/
