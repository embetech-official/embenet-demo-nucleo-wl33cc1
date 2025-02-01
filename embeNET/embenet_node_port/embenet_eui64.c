/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     Implementation of EUI64 interface for embeNET Node
 */

#include <embenet_port/eui64.h>
#include <string.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <stm32wl3x_hal.h>
#pragma GCC diagnostic pop

uint64_t EMBENET_EUI64_Get(void) {
  uint64_t native;
  memcpy(&native, (uint8_t *)UID64_BASE, sizeof(native));
  // TODO temporary hack
  if(0xffffffffffffffff == native) {
    native = 0x12;
  }
  return native; // native;
}
