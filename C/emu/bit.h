/** Functions for Bit Manipulation
 * \author: Emanuel Regnath (emanuel.regnath@tum.de)
 *
 * \dependencies stdint.h
 * 
 **/


#ifndef _EMBEDDED_BITS_H_
#define _EMBEDDED_BITS_H_

#ifdef __cplusplus
extern "C" {
#endif

// C Standard Library
#include <stdint.h>
#include <stdbool.h>


// ============================================================================
// types
// ============================================================================
typedef uint8_t Byte;
typedef unsigned int Bit_Index;

typedef uint8_t Bit8;
typedef uint8_t Bit8_Mask;

typedef uint16_t Bit16;
typedef uint16_t Bit16_Mask;

typedef uint32_t Bit32;
typedef uint32_t Bit32_Mask;

typedef enum Bit_Enum { BIT_LOW = 0, BIT_HIGH = 1 } Bit;

// ============================================================================
// defines
// ============================================================================
#define BIT_IDX 0



// ============================================================================
// prototypes
// ============================================================================

Bit_Index BIT_getIdx(Bit32_Mask mask);

// 8 Bit
Bit8_Mask BIT8_mask(Bit_Index start, Bit_Index end);

Bit8 BIT8_set(const Bit8 data, const Bit_Index idx);
Bit8 BIT8_clear(const Bit8 data, const Bit_Index idx);
Bit8 BIT8_toggle(const Bit8 data, const Bit_Index idx);

Bit8 BIT8_setMask(const Bit8 data, const Bit8_Mask mask);
Bit8 BIT8_clearMask(const Bit8 data, const Bit8_Mask mask);
Bit8 BIT8_toggleMask(const Bit8 data, const Bit8_Mask mask);

Bit8 BIT8_write(const Bit8 data, const Bit_Index idx, const Bit state);
Bit8 BIT8_writeMask(const Bit8 data, const Bit8_Mask mask, const Bit8 value);

bool BIT8_isClear(const Bit8 data, const Bit_Index idx);
bool BIT8_isSet(const Bit8 data, const Bit_Index idx);
bool BIT8_isMaskSet(const Bit8 data, const Bit8_Mask mask);
bool BIT8_isMaskClear(const Bit8 data, const Bit8_Mask mask);
Bit BIT8_read(const Bit8 data, const Bit_Index idx);
Bit8 BIT8_readMask(const Bit8 data, const Bit8_Mask mask);


// 16 Bit
Bit16_Mask BIT16_mask(Bit_Index start, Bit_Index end);

Bit16 BIT16_set(const Bit16 data, const Bit_Index idx);
Bit16 BIT16_clear(const Bit16 data, const Bit_Index idx);
Bit16 BIT16_toggle(const Bit16 data, const Bit_Index idx);

Bit16 BIT16_setMask(const Bit16 data, const Bit16_Mask mask);
Bit16 BIT16_clearMask(const Bit16 data, const Bit16_Mask mask);
Bit16 BIT16_toggleMask(const Bit16 data, const Bit16_Mask mask);

Bit16 BIT16_write(const Bit16 data, const Bit_Index idx, const Bit state);
Bit16 BIT16_writeMask(const Bit16 data, const Bit16_Mask mask, const Bit16 value);

bool BIT16_isClear(const Bit16 data, const Bit_Index idx);
bool BIT16_isSet(const Bit16 data, const Bit_Index idx);
bool BIT16_isMaskSet(const Bit16 data, const Bit16_Mask mask);
bool BIT16_isMaskClear(const Bit16 data, const Bit16_Mask mask);
Bit BIT16_read(const Bit16 data, const Bit_Index idx);
Bit16 BIT16_readMask(const Bit16 data, const Bit16_Mask mask);


// 32 Bit
Bit32_Mask BIT32_mask(Bit_Index start, Bit_Index end);

Bit32 BIT32_set(const Bit32 data, const Bit_Index idx);
Bit32 BIT32_clear(const Bit32 data, const Bit_Index idx);
Bit32 BIT32_toggle(const Bit32 data, const Bit_Index idx);

Bit32 BIT32_setMask(const Bit32 data, const Bit32_Mask mask);
Bit32 BIT32_clearMask(const Bit32 data, const Bit32_Mask mask);
Bit32 BIT32_toggleMask(const Bit32 data, const Bit32_Mask mask);

Bit32 BIT32_write(const Bit32 data, const Bit_Index idx, const Bit state);
Bit32 BIT32_writeMask(const Bit32 data, const Bit32_Mask mask, const Bit32 value);

bool BIT32_isClear(const Bit32 data, const Bit_Index idx);
bool BIT32_isSet(const Bit32 data, const Bit_Index idx);
bool BIT32_isMaskSet(const Bit32 data, const Bit32_Mask mask);
bool BIT32_isMaskClear(const Bit32 data, const Bit32_Mask mask);
Bit BIT32_read(const Bit32 data, const Bit_Index idx);
Bit32 BIT32_readMask(const Bit32 data, const Bit32_Mask mask);



#ifdef __cplusplus
}
#endif

#endif // _EMBEDDED_BITS_H_
