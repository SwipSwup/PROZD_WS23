#include <stdio.h>
#include "math.h"

int convert(int in, int base) {
    return in % 10 + (in / 10) % 10 * base + (in / 100) % 10 * pow(base, 2);
}

int main() {
    int okt;
    int zs;

    scanf("%d", &okt);

    printf(": dec.: %d\n", zs = convert(okt, 8));
    printf("ZS: %d\n", convert(zs, 1));

    return 0;
}


