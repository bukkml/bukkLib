#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

typedef uint8_t u8;

#define STACKLIMIT 255

int stack[STACKLIMIT];
u8 sp = 0;

int getch(void);
void ungetch(int);
int getfloat(float*);

int main() {


    return 0;
}

int getch(void) {
    return (sp > 0) ? stack[sp--] : getchar();
}
void ungetch(int ch) {
    if (sp >= STACKLIMIT) {
        printf("Stack owerflow\n");
        return;
    }
    stack[sp++] = ch;
}
int getfloat(float* n) {
    int ch, sign;
    double power = 1.0f;

    while (isspace(ch = getch()));
    if (!isdigit(ch) && ch != EOF && ch != '-' && ch != '+' && ch != '.') {
        ungetch(ch);
        return 0;
    }
    sign = (ch == '-') ? -1 : 1;
    if (ch == '-' || ch == '+') {
        if (!isdigit(ch = getch()) && ch != '.') {
            ungetch(ch);
            return 0;
        }
    }

    if (isdigit(ch)) {
        for (*n = 0.0f; isdigit(ch); ch = getch())
        *n = *n * 10.0f + (ch - '0');
    }
    if (ch == '.') {
        ch = getch();
        for (*n = 0.0f; isdigit(ch); ch = getch()) {
            *n = *n * 10.0f + (ch - '0');
            power *= 10.0f;
        }
    }
    if (ch != EOF)
        ungetch(ch);
    
    *n = *n * sign / power;

    return 1;
}