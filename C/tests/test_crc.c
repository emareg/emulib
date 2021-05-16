#include "emu/crc.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>



int main(){
    unsigned char data[10] = "123456789";

    printf("Testing CRC for '123456789'\n");
    
    uint8_t crc8 = CRC_crc8(data, 9);
    printf("CRC-8 is 0x%02x, should be 0xd0\n",crc8);

    uint16_t crc16 = CRC_crc16(data, 9);
    printf("CRC-16 is 0x%04x, should be 0x2189\n",crc16);

    uint32_t crc32 = CRC_crc32(data, 9);
    // uint32_t crc32 = crc32_bitwise(data, 9);
    printf("CRC-32 is 0x%08x, should be 0xCBF43926\n",crc32);


    // CRC_genTable(8, 0xE5);
    printf("Generating crc16 Table\n");
    CRC_genTable(16, 0x8408);
    
    printf("Generating crc32 Table\n");
    CRC_genTable(32, 0xEDB88320);

}