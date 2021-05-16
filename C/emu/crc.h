/* Simple CRC
 *
 */

#ifndef EMU_CRC_H
#define EMU_CRC_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef unsigned char CRC_Crc8;
typedef unsigned short CRC_Crc16;
typedef unsigned int CRC_Crc32;

CRC_Crc8  CRC_crc8 (const unsigned char* data, size_t len);
CRC_Crc16 CRC_crc16(const unsigned char* data, size_t len);
CRC_Crc32 CRC_crc32(const unsigned char* data, size_t len);



#ifdef __cplusplus
}
#endif
#endif

