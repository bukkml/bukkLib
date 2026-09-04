#include <stdio.h>

int main() {

    int cl = 0, cs = 0, ct = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++cs;
        else if (c == '\t')
            ++ct;
        else if (c == '\n')
            ++cl;
    }
    printf("Spaces=%d\nTabs=%d\nLines=%d\n", cs, ct, cl);
}
