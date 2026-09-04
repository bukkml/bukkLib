#include <stdio.h>

// Copy paste v2
int main() {
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\\') printf("\\");
        else if (c == '\b') printf("\\b");
        else if (c == '\t') printf("\\t");
        else putchar(c);
    }

}
