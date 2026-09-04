#include <stdio.h>

int main() {
    int space = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ' && space == 1);
        else if (c == ' ' && space == 0) {
            putchar(c);
            space = 1;
        }
        else {
            putchar(c);
            space = 0;
        }
    }
}
