#include <stdint.h>
#include "crc.h"

#define CRC_POLYNOMIAL_8 0xE0 // 0x07, rev: 0xE0
#define CRC_POLYNOMIAL_16 0x8408  // 0x1021, rev: 0x8408
#define CRC_POLYNOMIAL_32 0xEDB88320 // 0x04C11DB7, rev: 0xEDB88320



// CRC-16-CCITT, no table
// CRC_Crc16 CRC_crc16(const unsigned char* data, size_t len){
//     unsigned char x;
//     CRC_Crc16 crc = 0xFFFF;

//     for (uint8_t i = 0; i < len; i++){
//         x = crc >> 8 ^ *data++;
//         x ^= x>>4;
//         crc = (crc << 8) ^ ((CRC_Crc16)(x << 12)) ^ ((CRC_Crc16)(x <<5)) ^ ((CRC_Crc16)x);
//     }
//     return crc;
// }


static const CRC_Crc8 CRC_tab8[16] = { 
	// CCIT-Poly: 0x07 / 0xE0
	0x00, 0x1c, 0x38, 0x24, 0x70, 0x6c, 0x48, 0x54, 0xe0, 0xfc, 0xd8, 0xc4, 0x90, 0x8c, 0xa8, 0xb4, 

	// Bluetooth-Poly: 0xA7 / 0xE5 
	// 0x00,0x57,0xae,0xf9,0x97,0xc0,0x39,0x6e,0xe5,0xb2,0x4b,0x1c,0x72,0x25,0xdc,0x8b,
}; 

CRC_Crc8 CRC_crc8(const unsigned char* data, size_t len){
    CRC_Crc8 crc = 0xFF;  // init val, often 0x00 or 0xFF
    for (uint8_t i = 0; i < len; i++){
	    crc = (crc >> 4) ^ CRC_tab8[((data[i] ^ crc) & 0x0F)];
	    crc = (crc >> 4) ^ CRC_tab8[(((data[i]>>4) ^ crc) & 0x0F)];
	}
    return crc;
}

/* CRC16 implementation acording to CCITT standards */
static const CRC_Crc16 CRC_tab16[16] = { 
  0x0000, 0x1081, 0x2102, 0x3183, 0x4204, 0x5285, 0x6306, 0x7387, 
  0x8408, 0x9489, 0xA50A, 0xB58B, 0xC60C, 0xD68D, 0xE70E, 0xF78F
};  


// Kermit, alias CRC-16/CCITT, CRC-16/CCITT-TRUE
// see https://reveng.sourceforge.io/crc-catalogue/16.htm
CRC_Crc16 CRC_crc16(const unsigned char* data, size_t len){
    CRC_Crc16 crc = 0x0000; // init val, often 0x0000 or 0xFFFF
    for (uint8_t i = 0; i < len; i++){
	    crc = (crc >> 4) ^ CRC_tab16[((data[i] ^ crc) & 0x0F)];
	    crc = (crc >> 4) ^ CRC_tab16[(((data[i]>>4) ^ crc) & 0x0F)];
	}
    return crc;
}


// contains every 16th entry of the full table
static const CRC_Crc32 CRC_tab32[16] = {
    0x00000000,0x1DB71064,0x3B6E20C8,0x26D930AC,0x76DC4190,0x6B6B51F4,0x4DB26158,0x5005713C,
    0xEDB88320,0xF00F9344,0xD6D6A3E8,0xCB61B38C,0x9B64C2B0,0x86D3D2D4,0xA00AE278,0xBDBDF21C
};


CRC_Crc32 CRC_crc32 (const unsigned char *data, size_t len){
	CRC_Crc32 crc = 0xFFFFFFFF;
	for (int i = 0; i < len; i++){
		crc = (crc >> 4) ^ CRC_tab32[(data[i] ^ crc) & 0x0F];
		crc = (crc >> 4) ^ CRC_tab32[((data[i] >> 4) ^ crc) & 0x0f];
	}
   return ~crc;
}


// Generate the table for the reverse Polynom
void CRC_genTable(int bitwidth, int crcPoly){
	for (int val = 0; val < 16; val++){
		int result = val;

		for (int i = 0; i < 4; i++)
			if (result & 1)
				result = (result >> 1) ^ crcPoly;
			else
				result >>= 1;
		printf("0x%08lx\n", result);
	}
}


// References
// https://wiki.wxwidgets.org/Development:_Small_Table_CRC