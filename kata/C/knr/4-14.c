#include <stdio.h>

#define SWAP(t, x, y) if (sizeof(x) == sizeof(t) && sizeof(y) == sizeof(t)) \
    { t tmp = ((x)); ((x)) = ((y)); ((y)) = tmp; }

int main() {
    int x = 5;
    int y = 3;
    printf("x=%d\ty=%d\n", x, y);
    SWAP(int, x, y);
    printf("x=%d\ty=%d\n", x, y);
}