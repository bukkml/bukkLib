#include <stdio.h>

int strend(char* s, char* t) {
    char* pt = t;

    while (*s++);
    while (*t++);

    s--, t--;

    for (; *s == *t; s--, t--) {
        if (t == pt)
            return 1;
    }
    return 0;
}

int main() {
    char* s = "ASDASDASDDDDDXXCD";
    char* t = "DDDXXCD";
    char* d = "ASD";

    printf("%d\n%d\n", strend(s, t), strend(s, d));

    return 0;
}
