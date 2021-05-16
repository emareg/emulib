
#include "bit.h"


Bit_Index BIT_getIdx(Bit32_Mask mask){
	Bit_Index idx;
	for(idx = 0; idx < 32; idx++){
		if(mask & (1 << idx)){ break; }
	}
	return idx;
}


Bit8_Mask BIT8_mask(Bit_Index start, Bit_Index end){
	Bit_Index idx;
	Bit8_Mask mask = 0;
	for(idx = start; idx <= end; idx++){
		mask |= (0b1 << idx);
	}
	return mask;
}

Bit8 BIT8_set(const Bit8 data, const Bit_Index idx){
	return (data | (1 << idx));
}

Bit8 BIT8_clear(const Bit8 data, const Bit_Index idx){
	return (data & ~(1 << idx));
}

Bit8 BIT8_toggle(const Bit8 data, const Bit_Index idx){
	return (data ^ (1 << idx));
}

Bit8 BIT8_setMask(const Bit8 data, const Bit8_Mask mask){
	return (data | mask);
}

Bit8 BIT8_clearMask(const Bit8 data, const Bit8_Mask mask){
	return (data & ~mask);
}

Bit8 BIT8_toggleMask(const Bit8 data, const Bit8_Mask mask){
	return (data ^ mask);
}

Bit8 BIT8_write(const Bit8 data, const Bit_Index idx, const Bit state){
	return ( (data & ~(1 << idx)) | (state << idx));
}

Bit8 BIT8_writeMask(const Bit8 data, const Bit8_Mask mask, const Bit8 value){
	Bit_Index bit_idx = BIT_getIdx(mask);
	return BIT8_setMask( (data & ~mask), (mask & (value << bit_idx)));
}

bool BIT8_isClear(const Bit8 data, const Bit_Index idx){
	return (bool)( (~(data >> idx) & 1) == 1 );
}

bool BIT8_isSet(const Bit8 data, const Bit_Index idx){
	return (bool)( ((data >> idx) & 1) == 1 );
}

bool BIT8_isMaskSet(const Bit8 data, const Bit8_Mask mask){
	return (bool)( (data & mask) == mask );
}

bool BIT8_isMaskClear(const Bit8 data, const Bit8_Mask mask){
	return (bool)( (~data & mask) == mask );
}

Bit BIT8_read(const Bit8 data, const Bit_Index idx){
	return (Bit)( (data >> idx) & 1);
}

Bit8 BIT8_readMask(const Bit8 data, const Bit8_Mask mask){
	Bit_Index bit_idx = BIT_getIdx(mask);
	return ((data & mask) >> bit_idx);
}





Bit16_Mask BIT16_mask(Bit_Index start, Bit_Index end){
	Bit_Index idx;
	Bit16_Mask mask = 0;
	for(idx = start; idx <= end; idx++){
		mask |= (0b1 << idx);
	}
	return mask;
}

Bit16 BIT16_set(const Bit16 data, const Bit_Index idx){
	return (data | (1 << idx));
}

Bit16 BIT16_clear(const Bit16 data, const Bit_Index idx){
	return (data & ~(1 << idx));
}

Bit16 BIT16_toggle(const Bit16 data, const Bit_Index idx){
	return (data ^ (1 << idx));
}

Bit16 BIT16_setMask(const Bit16 data, const Bit16_Mask mask){
	return (data | mask);
}

Bit16 BIT16_clearMask(const Bit16 data, const Bit16_Mask mask){
	return (data & ~mask);
}

Bit16 BIT16_toggleMask(const Bit16 data, const Bit16_Mask mask){
	return (data ^ mask);
}

Bit16 BIT16_write(const Bit16 data, const Bit_Index idx, const Bit state){
	return ( (data & ~(1 << idx)) | (state << idx));
}

Bit16 BIT16_writeMask(const Bit16 data, const Bit16_Mask mask, const Bit16 value){
	Bit_Index bit_idx = BIT_getIdx(mask);
	return BIT16_setMask( (data & ~mask), (mask & (value << bit_idx)));
}

bool BIT16_isClear(const Bit16 data, const Bit_Index idx){
	return (bool)( (~(data >> idx) & 1) == 1 );
}

bool BIT16_isSet(const Bit16 data, const Bit_Index idx){
	return (bool)( ((data >> idx) & 1) == 1 );
}

bool BIT16_isMaskSet(const Bit16 data, const Bit16_Mask mask){
	return (bool)( (data & mask) == mask );
}

bool BIT16_isMaskClear(const Bit16 data, const Bit16_Mask mask){
	return (bool)( (~data & mask) == mask );
}

Bit BIT16_read(const Bit16 data, const Bit_Index idx){
	return (Bit)( (data >> idx) & 1);
}

Bit16 BIT16_readMask(const Bit16 data, const Bit16_Mask mask){
	Bit_Index bit_idx = BIT_getIdx(mask);
	return ((data & mask) >> bit_idx);
}




Bit32_Mask BIT32_mask(Bit_Index start, Bit_Index end){
	Bit_Index idx;
	Bit32_Mask mask = 0;
	for(idx = start; idx <= end; idx++){
		mask |= (0b1 << idx);
	}
	return mask;
}

Bit32 BIT32_set(const Bit32 data, const Bit_Index idx){
	return (data | (1 << idx));
}

Bit32 BIT32_clear(const Bit32 data, const Bit_Index idx){
	return (data & ~(1 << idx));
}

Bit32 BIT32_toggle(const Bit32 data, const Bit_Index idx){
	return (data ^ (1 << idx));
}

Bit32 BIT32_setMask(const Bit32 data, const Bit32_Mask mask){
	return (data | mask);
}

Bit32 BIT32_clearMask(const Bit32 data, const Bit32_Mask mask){
	return (data & ~mask);
}

Bit32 BIT32_toggleMask(const Bit32 data, const Bit32_Mask mask){
	return (data ^ mask);
}

Bit32 BIT32_write(const Bit32 data, const Bit_Index idx, const Bit state){
	return ( (data & ~(1 << idx)) | (state << idx));
}

Bit32 BIT32_writeMask(const Bit32 data, const Bit32_Mask mask, const Bit32 value){
	Bit_Index bit_idx = BIT_getIdx(mask);
	return BIT32_setMask( (data & ~mask), (mask & (value << bit_idx)));
}

bool BIT32_isClear(const Bit32 data, const Bit_Index idx){
	return (bool)( (~(data >> idx) & 1) == 1 );
}

bool BIT32_isSet(const Bit32 data, const Bit_Index idx){
	return (bool)( ((data >> idx) & 1) == 1 );
}

bool BIT32_isMaskSet(const Bit32 data, const Bit32_Mask mask){
	return (bool)( (data & mask) == mask );
}

bool BIT32_isMaskClear(const Bit32 data, const Bit32_Mask mask){
	return (bool)( (~data & mask) == mask );
}

Bit BIT32_read(const Bit32 data, const Bit_Index idx){
	return (Bit)( (data >> idx) & 1);
}

Bit32 BIT32_readMask(const Bit32 data, const Bit32_Mask mask){
	Bit_Index bit_idx = BIT_getIdx(mask);
	return ((data & mask) >> bit_idx);
}

