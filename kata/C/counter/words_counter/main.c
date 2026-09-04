// Words counter

#include <stdio.h>

#define IN 1
#define OUT 0
#define FLAG int

int main() {

    int c, nw;
    FLAG state;
    c = nw = 0;
    state = OUT;

    while ((c = getchar()) != EOF) {
        if (state == IN) {
            if (c == ' ' || c == '\t' || c == '\n') {
                state = OUT;
            }
        }
        else if (state == OUT) {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                state = IN;
                ++nw;
            }
        }
    }
    printf("Words = %d\n", nw);
}
