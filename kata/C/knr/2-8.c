#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned int uint;

void printbits(uint x) {
    for (int i = sizeof(x) * CHAR_BIT; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
    printf("\n");
}

uint rightrot(uint x, int n) {
    if (n > sizeof(x) * CHAR_BIT) n %= sizeof(x) * CHAR_BIT;

    return (~(~0u << n) & x) << (sizeof(x) * CHAR_BIT - n) | x >> n;
}

uint rightrot_reference(uint x, int n) {
    if (n > sizeof(x) * CHAR_BIT) n %= sizeof(x) * CHAR_BIT;

    uint last_bit;

    while (n-- > 0) {
        last_bit = x & 1;
        x >>= 1;

        if (last_bit)
            x |= 1u << (sizeof(x) * CHAR_BIT - 1);
    }

    return x;
}

int test(void) {
    for (int i = 0; i < 100000000; i++) {
        printf("\rTest processed #%d", i);

        uint x = rand();
        int n = rand() + 1;

        uint expected = rightrot_reference(x, n);
        uint actual = rightrot(x, n);

        if (expected != actual) {
            printf("\nTest filed\n");

            printf("x:%d n:%d\n", x, n);

            printf("Expected: ");
            printbits(expected);

            printf("Actual:   ");
            printbits(actual);

            return 0;
        }
    }
    return 1;
}

int main(void) {
    srand(time(NULL));

    if (test()) {
        printf("Correct\n");
        return 0;
    }

    printf("Incorrect\n");
    return 1;
}
