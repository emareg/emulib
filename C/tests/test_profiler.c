#include <stdio.h>
#include "emu/prf.h"

int main(){
    PRF_Profile prf_test;
    PRF_reset(&prf_test);

    for (int idx = 0; idx < 13; idx++){
        PRF_start( &prf_test);
        printf("how long to print this?\n");
        PRF_stop( &prf_test);
    }

    PRF_print("prinf time:", &prf_test);
}