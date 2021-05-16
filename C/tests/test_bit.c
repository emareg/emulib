#include "emu/bit.h"

#include <stdio.h>
#include <assert.h>

void print_bit16(Bit16 data){
    printf("Bit16: 0b");
	for (int idx = 15; idx >= 0; idx--){
		printf("%1d", BIT16_isSet(data, idx));
	}
    printf("\n");
}

int main(){
    Bit16 myreg = 0;
    print_bit16(myreg);

    printf("setMask(0b0000111100001111)\n");
    myreg = BIT16_setMask(myreg, 0b0000111100001111);
    print_bit16(myreg);

    printf("toggle(5)\n");
    myreg = BIT16_toggle(myreg, 5);
    print_bit16(myreg);

}