#include <stdio.h>

#define BITS 8

typedef unsigned int uint;

void printbits(uint x) {
    for (int i = sizeof(x) * BITS - 1; i >= 0; i--) {
        printf("%d", x >> i & 1);
    }
    printf("\n");
}

uint setbits(uint x, int p, int n, uint y) {
    return x & ~(~(~0u << n) << (p + 1 - n)) | (y & ~(~0u << n)) << (p + 1 - n);
}

int main(int argv, char** argc) {
    uint x = 0, y = 0;
    scanf("%d %d", &x, &y);
    printf("x = ");
    printbits(x);
    printf("y = ");
    printbits(y);
    x = setbits(x, 12, 6, y);
    printbits(x);

    return 0;
}
