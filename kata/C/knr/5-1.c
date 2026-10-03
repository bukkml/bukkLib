#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#define STACKLIMIT 255

int stack[STACKLIMIT];
uint8_t sp = 0;

int getch(void);
void ungetch(int);
int getint(int*);

int main() {


    return 0;
}

int getch(void) {
    return (sp > 0) ? stack[sp--] : getchar();  
}
void ungetch(int n) {
    if (sp >= STACKLIMIT) {
        printf("Stack owerflow\n");
        return;
    }
    stack[sp++] = n;
}
int getint(int* n) {
    int ch, sign;

    while(isspace(ch = getch()));
    if (!isdigit(ch) && ch != EOF && ch != '-' && ch != '+') {
        ungetch(ch);
        return 0;
    }
    sign = (ch == '-') ? -1 : 1;
    if (ch == '-' || ch == '+') {
        ch = getch();
        if (!isdigit(ch)) {
            ungetch(ch);
            return 0;
        }
    }
    for (*n = 0; isdigit(ch); ch = getch())
        *n = *n * 10 + (ch - '0');
    *n *= sign;
    if (ch != EOF)
        ungetch(ch);
    return 1;
}