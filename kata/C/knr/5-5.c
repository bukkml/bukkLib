#include <stdio.h>

char* strncpy_(char* s, char* t, int n);
char* strncat_(char* s, char* t, int n);
int strncmp_(char* s, char* t, int n);

int main() {

    char s[] = "SSSSloooo";
    char t[] = "SSSS";

    printf("%d\n", strncmp_(s, t, 3));

    return 0;
}

char* strncpy_(char* s, char* t, int n) {
    char* result = s;

    while (n-- && (*s++ = *t++));

    if (n > 0)
        *s = '\0';

    return result;
}
char* strncat_(char* s, char* t, int n) {
    char* result = s;

    while (*s++);

    s--;

    while (n-- && (*s++ = *t++));

    *s = '\0';

    return result;
}
int strncmp_(char* s, char* t, int n) {
    for (; *s == *t && n > 0; s++, t++, n--) {
        if (*s == '\0' || n == 0)
            return 0;
    }

    return *s - *t;
}
