#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

void itoa(i32 n, char* s, u16 t);

void reverse(char* s);

int main(void) {
    int n = 555555123;
    int t = 10;
    char* s = (char*)malloc(sizeof(char) * 100);
    itoa(n, s, t);

    printf("%s\n", s);

    free(s);
}

void itoa(i32 n, char* s, u16 t) {
    if (s == NULL)
        return;
    
    i8 sign = (n < 0) ? -1 : 1;
    u32 i = 0;

    if (sign) {
        do {
            s[i++] = (n % 10) + '0';
        } while ((n /= 10) > 0);
    }
    else {
        do {
            s[i++] = -(n % 10) + '0';
        } while ((n /= 10) < 0);
        s[i++] = '-';
    }
    for (; i < t; i++) {
        s[i] = ' ';
    }
    s[++i] = '\0';

    reverse(s);
}

void reverse(char* s) {
    if (s == NULL) return;

    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char ch = s[i];
        s[i] = s[j];
        s[j] = ch;
    }
}
