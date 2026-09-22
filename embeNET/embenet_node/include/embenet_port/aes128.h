/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET PORT API
 * @brief     AES-128 interface for the EMBENET NODE Port
 */

#ifndef EMBENET_NODE_PORT_AES128_H_
#define EMBENET_NODE_PORT_AES128_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup embenet_node_port_aes AES-128 Interface
 *
 * This is interface to the 128-bit version of the Advanced Encryption Standard (AES) algorithm used by the embeNET Node.
 * This interface was declared to allow various implementations of the AES-128 algorithm, including hardware-accelerated support.
 * @{
 */

/**
 * @brief Initializes the AES-128 ciphering module.
 *
 * Called by the stack once before any other AES API function is invoked.
 * Use this function to set up any required resources (e.g. hardware accelerator, lookup tables).
 */
void EMBENET_AES128_Init(void);

/**
 * @brief Deinitializes the AES-128 ciphering module.
 *
 * Called by the stack when it is being deinitialized. Release any resources acquired in @ref EMBENET_AES128_Init.
 */
void EMBENET_AES128_Deinit(void);

/**
 * @brief Sets the AES-128 key for subsequent encrypt and decrypt operations.
 *
 * The key set by this function is used in all subsequent calls to @ref EMBENET_AES128_Encrypt and @ref EMBENET_AES128_Decrypt
 * until this function is called again.
 *
 * @param[in] key pointer to a 16-byte secret key; must not be NULL.
 */
void EMBENET_AES128_SetKey(uint8_t const key[16U]);

/**
 * @brief Encrypts a 16-byte block in place using AES-128.
 *
 * Overwrites @p data with the AES-128 ciphertext of the original plaintext.
 *
 * @param[in,out] data 16-byte buffer containing plaintext on entry; contains ciphertext on return. Must not be NULL.
 */
void EMBENET_AES128_Encrypt(uint8_t data[16U]);

/**
 * @brief Decrypts a 16-byte block in place using AES-128.
 *
 * Overwrites @p data with the AES-128 plaintext of the original ciphertext.
 *
 * @param[in,out] data 16-byte buffer containing ciphertext on entry; contains plaintext on return. Must not be NULL.
 */
void EMBENET_AES128_Decrypt(uint8_t data[16U]);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // EMBENET_NODE_PORT_AES128_H_
