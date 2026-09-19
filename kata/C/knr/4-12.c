#include <stdio.h>

char* itoa(int n);

int main() {
    int x = 123;
    printf("%s\n", itoa(x));
    return 0;
}

char* itoa(int n) {
    static int i = 0;
    static char s[100];

    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }

    if (n / 10) {
        itoa(n / 10);
    }
    s[i++] = n % 10 + '0';
    s[i] = '\0';

    return s;
}