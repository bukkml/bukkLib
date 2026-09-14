#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef unsigned int uint;

void printbits(uint x) {
    for (int i = sizeof(x) * CHAR_BIT - 1; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
    printf("\n");
}

uint invert(uint x, int p, int n) {
    // return x & ~(~(~0u << n) << (p + 1 - n))
    //     | (~(~0u << n) & ~(x >> (p + 1 - n))) << (p + 1 - n);
    if (n == sizeof(x) * CHAR_BIT)
        return ~x;
    return x ^ ~(~0u << n) << (p + 1 - n);
}

uint invert_reference(uint x, int p, int n) {
    for (int i = p; i > p - n; i--) {
        x ^= 1u << i;
    }
    return x;
}

int test(void) {
    for (int i = 0; i < 10000; i++) {
        printf("\rProcessed test №%d", i + 1);
        fflush(stdout);
        uint x = rand();

        int p = rand() % 32;
        int n = rand() % (p + 1) + 1;

        uint expected = invert_reference(x, p, n);
        uint actual = invert(x, p, n);

        if (actual != expected) {
            printf("\nTest №%d filed!\n", i);

            printf("x:%d\n", x);

            printf("Expected: ");
            printbits(expected);
            printf("\n");

            printf("Actual:   ");
            printbits(actual);
            printf("\n");

            printf("p = %d; n = %d\n", p, n);

            return 0;
        }
    }
    return 1;
}

int main(void) {
    srand(time(NULL));

    if (test()) {
        printf("\nCorrect\n");
        return 0;
    }

    printf("Incorrect\n");
    return 1;
}
