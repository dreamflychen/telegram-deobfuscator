#include <stdio.h>
#include <stdint.h>
#include "decrypt.h"
#include "helpers.h"
#include "tgnet/Datacenter.h"

/**
 * Decrypts encrypted data
 * @param data
 * @param length  length of data (with authKeyId and msgKey)
 */
void decrypt(unsigned char *data, uint32_t length)
{
	uint8_t authKey[] = {
			0x9d, 0xef, 0x54, 0x8f, 0xba, 0xe4, 0xb8, 0xd4, 0x7e, 0x99, 0xe5, 0x86, 0xd0, 0x3c, 0x58, 0xdb, 0x8c, 0x58,
			0x55, 0x39, 0x33, 0x6c, 0xb2, 0x9d, 0xeb, 0xb2, 0x13, 0xbd, 0x9b, 0xe8, 0xbb, 0x98, 0xc1, 0x69, 0xd0, 0x6f,
			0x3e, 0x4d, 0x78, 0x38, 0xa6, 0x55, 0xf6, 0x43, 0x8b, 0x18, 0x35, 0x06, 0xf3, 0xf5, 0x30, 0x8a, 0x7d, 0x41,
			0x0f, 0x93, 0xcb, 0x43, 0xab, 0x1f, 0x4a, 0x8c, 0x1d, 0x4d, 0xfc, 0x06, 0x00, 0x59, 0x92, 0xfb, 0x3c, 0xfd,
			0x24, 0x90, 0x50, 0xa9, 0xd5, 0x53, 0x48, 0x92, 0x23, 0x38, 0xb3, 0x5a, 0x2b, 0x26, 0x41, 0xb2, 0x2d, 0x54,
			0xb3, 0x3a, 0x9b, 0xcc, 0x2a, 0x56, 0x5c, 0x9d, 0x53, 0x16, 0xd3, 0xa1, 0x5f, 0x3b, 0xbc, 0x89, 0x33, 0x2b,
			0xda, 0x47, 0xdb, 0xbe, 0x85, 0x1d, 0x38, 0x44, 0x68, 0x00, 0x10, 0x7f, 0x16, 0xe0, 0xb4, 0x91, 0xd6, 0x70,
			0x66, 0x35, 0x1f, 0xd0, 0x91, 0xde, 0x23, 0x26, 0x91, 0xfa, 0x06, 0x96, 0x36, 0xaf, 0xc3, 0xa6, 0x7c, 0x0f,
			0x4f, 0x10, 0x4c, 0x99, 0xbb, 0x62, 0xf5, 0xc6, 0x58, 0x3b, 0xf7, 0xbe, 0x76, 0x7b, 0xc0, 0x29, 0x68, 0x01,
			0x19, 0xeb, 0x02, 0xce, 0xcb, 0x05, 0x02, 0x00, 0x5d, 0x0a, 0x03, 0x8f, 0x93, 0x11, 0x44, 0x41, 0x51, 0x1e,
			0x68, 0x25, 0x46, 0xa9, 0x1a, 0x98, 0x6e, 0x6f, 0x11, 0x27, 0x43, 0x72, 0xcb, 0xd4, 0x07, 0x59, 0xc2, 0xe6,
			0xba, 0x02, 0x0a, 0x33, 0x93, 0xed, 0x61, 0xa5, 0xdf, 0x9e, 0x60, 0x11, 0x54, 0x1a, 0x27, 0xdd, 0x24, 0x25,
			0x53, 0xa8, 0xe5, 0xb5, 0x60, 0x43, 0xa7, 0x1c, 0x62, 0x19, 0xad, 0x86, 0x3a, 0x75, 0xc3, 0xaf, 0xcd, 0xc6,
			0x2c, 0x78, 0xf6, 0xaa, 0x3d, 0x31, 0xcd, 0x31, 0x13, 0x6e, 0xaa, 0xbc, 0xc1, 0x61, 0x15, 0x86, 0x23, 0xea,
			0x6f, 0xa1, 0xc5, 0x55
	};
	printf("ige len: %d\n", length - 24);

	static uint8_t key[64];
	Datacenter::generateMessageKey(authKey, data + 8, key, false);
	Datacenter::aesIgeEncryption(data + 24, key, key + 32, false, false, length - 24);

	printf("ige decrypted:\n");
	printHex(data + 24, length - 24);

	printf("\tsalt:\n");
	printHex(data + 24, 8);
	printf("\tsession:\n");
	printHex(data + 24 + 8, 8);
	printf("\tid:\n");
	printHex(data + 24 + 16, 8);
	printf("\tmsg_seq:\n");
	printHex(data + 24 + 24, 4);
	printf("\tmsg_size:\n");
	printHex(data + 24 + 28, 4);
	printf("\tmsg:\n");
	printHex(data + 24 + 32, length - 24 - 32);
	printAscii(data + 24 + 32, length - 24 - 32);

	// last 8 are random id?
}