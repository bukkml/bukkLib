#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void itob(int n, char* s, int b);
void reverse(char* s);

int main() {
    int n = -3480957;
    char* s = (char*)malloc(sizeof(char) * 100);
    int b = 16;

    itob(n, s, b);

    printf("%s\n", s);

    free(s);

    return 0;
}

void itob(int n, char* s, int b) {
    int i, sign;

    sign = n;
    i = 0;

    if (n < 0) {
        do {
            char ch = -(n % b);
            if (ch >= 10)
                ch = ch - 10 + 'A';
            else
                ch += '0';
            s[i++] = ch;
        }
        while ((n /= b) < 0);
        s[i++] = '-';
    }
    else {
        do {
            char ch = n % b;
            if (ch >= 10)
                ch = ch - 10 + 'A';
            else
                ch += '0';
            s[i++] = ch;
        }
        while ((n /= b) > 0);
    }

    s[i] = '\0';

    reverse(s);
}

void reverse(char* s) {
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
}
