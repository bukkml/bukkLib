#include <stdio.h>

char* strcat(char* s, char* t) {
    char* x = s;
    while(*s++);

    --s;

    while(*s++ = *t++);

    return x;
}

int main() {
    char s[14] = "Hello";
    char t[8] = " world!";
    printf("%s\n", strcat(s, t));
    return 0;
}
