#include "embetech/crc8.h"

#define CRC8INIT 0x00
#define CRC8POLY 0x18 // 0X18 = X^8+X^5+X^4+X^0

#if __has_include(<embetech/embetile.h>) && EMBETILE_ENABLED // This macro is defined by invoking embetile_define_component
#include <embetech/embetile.h>
// mark API functions - this enables to use them as embetile API
uint8_t CRC8_Init(void) EMBETILE(CRC8_Init);
uint8_t CRC8_UpdateByte(uint8_t byte, uint8_t crc) EMBETILE(CRC8_UpdateByte);
uint8_t CRC8_UpdateBuf(void const *buf, size_t size, uint8_t crc) EMBETILE(CRC8_UpdateBuf);
#endif

uint8_t CRC8_Init(void) { return CRC8INIT; }

uint8_t CRC8_UpdateByte(uint8_t byte, uint8_t crc) {
  uint8_t bit_counter;
  uint8_t feedback_bit;

  bit_counter = 8;
  do {
    feedback_bit = (uint8_t)(crc ^ byte) & 0x01;

    if(0x01 == feedback_bit) {
      crc = crc ^ CRC8POLY;
    }
    crc = (uint8_t)(crc >> 1) & 0x7F;
    if(0x01 == feedback_bit) {
      crc = crc | 0x80;
    }

    byte = byte >> 1;
    bit_counter--;

  } while(bit_counter > 0);

  return crc;
}

uint8_t CRC8_UpdateBuf(void const *buf, size_t size, uint8_t crc) {
  size_t i;
  uint8_t bit_counter;
  uint8_t data;
  uint8_t feedback_bit;

  crc = CRC8INIT;

  for(i = 0; i < size; i++) {
    data = ((uint8_t const *)buf)[i];

    bit_counter = 8;
    do {
      feedback_bit = (uint8_t)(crc ^ data) & 0x01;

      if(0x01 == feedback_bit) {
        crc = crc ^ CRC8POLY;
      }
      crc = (uint8_t)(crc >> 1) & 0x7F;
      if(0x01 == feedback_bit) {
        crc = crc | 0x80;
      }

      data = data >> 1;
      bit_counter--;

    } while(bit_counter > 0);
  }

  return crc;
}
