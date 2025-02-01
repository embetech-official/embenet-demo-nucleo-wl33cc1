/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     Implementation of AES-128 interface for embeNET Node
 */

#include <embenet_port/aes128.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <stm32wl3x_hal.h>
#pragma GCC diagnostic pop

#include <stdlib.h>
#include <string.h>

static CRYP_HandleTypeDef hcryp;
static uint32_t aesKey[4];

void EMBENET_AES128_Init(void) {
  __HAL_RCC_AES_CLK_ENABLE();

  hcryp.Instance = AES;
  hcryp.Init.DataType = CRYP_DATATYPE_8B;
  hcryp.Init.KeySize = CRYP_KEYSIZE_128B;
  hcryp.Init.pKey = aesKey;
  hcryp.Init.pInitVect = NULL;
  hcryp.Init.Algorithm = CRYP_AES_ECB;
  hcryp.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_BYTE;
  hcryp.Init.HeaderWidthUnit = CRYP_HEADERWIDTHUNIT_BYTE;
  hcryp.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;

  HAL_CRYP_DeInit(&hcryp);
  HAL_CRYP_Init(&hcryp);
}

void EMBENET_AES128_Deinit(void) {
  HAL_CRYP_DeInit(&hcryp);
  __HAL_RCC_AES_CLK_DISABLE();
}

void EMBENET_AES128_SetKey(uint8_t const key[16U]) {
  // HAL obtains key in native endianess (as 4 4B words)
  aesKey[0] = ((uint32_t)key[0] << 24) + ((uint32_t)key[1] << 16) + ((uint32_t)key[2] << 8) + ((uint32_t)key[3]);
  aesKey[1] = ((uint32_t)key[4] << 24) + ((uint32_t)key[5] << 16) + ((uint32_t)key[6] << 8) + ((uint32_t)key[7]);
  aesKey[2] = ((uint32_t)key[8] << 24) + ((uint32_t)key[9] << 16) + ((uint32_t)key[10] << 8) + ((uint32_t)key[11]);
  aesKey[3] = ((uint32_t)key[12] << 24) + ((uint32_t)key[13] << 16) + ((uint32_t)key[14] << 8) + ((uint32_t)key[15]);
}

void EMBENET_AES128_Encrypt(uint8_t data[16U]) {
  uint32_t in[4];
  memcpy(in, data, 16);
  uint32_t out[4];
  HAL_CRYP_Encrypt(&hcryp, in, (uint16_t)16, out, 10000);
  memcpy(data, out, 16);
}

void EMBENET_AES128_Decrypt(uint8_t data[16U]) {
  uint32_t in[4];
  memcpy(in, data, 16);
  uint32_t out[4];
  HAL_CRYP_Decrypt(&hcryp, in, (uint16_t)16, out, 10000);
  memcpy(data, out, 16);
}
