#include <stdio.h>

int32_t float2int(int32_t f) 
{
    int32_t s = f < 0 ? -1 : 1; // znak liczby
    int32_t m = (f & 0x7fffff) | 0x800000; // 
    int32_t e = (f & 0x7f800000) - 127 - 23; // o ile przesunąć m w prawo
    if (e > 7) return 0x80000000;
    if (e > 0) return s * (m << e);
    else if (e < -23) return 0;
    else return s * (m >> -e);
}