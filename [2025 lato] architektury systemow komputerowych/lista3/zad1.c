#include <stdio.h>
#include <limits.h>

int main()
{
    u_int32_t n = 6;
    u_int64_t M = ((1ll << 32)) / 3; // M = 0x55555556
    u_int32_t res = (n * M) >> 32;
    printf("%d\n", res);

    return 0;
}