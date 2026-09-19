#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0'

#define MAXOP 255
#define STACKSIZE 255
#define BUFSIZE 255

double stack[STACKSIZE];
uint8_t sp = 0;  // stack pos

char buf[BUFSIZE];
uint8_t bp = 0;  // buf pos

double vars[26];

int getch();
void ungetch(int);
int getop(char[]);
void stack_push(double);
double stack_pop(void);
void stack_print(void);
void stack_double(void);
void stack_roll(void);
void stack_clear(void);

void vars_create(void);
void vars_push(double, uint8_t);
double vars_pop(uint8_t);

int main() {
    char s[MAXOP];
    int type;
    double t;
    vars_create();

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                stack_push(atof(s));
                break;
            case '+':
                stack_push(stack_pop() + stack_pop());
                break;
            case '*':
                stack_push(stack_pop() * stack_pop());
                break;
            case '-':
                t = stack_pop();
                stack_push(stack_pop() - t);
                break;
            case '/':
                if ((t = stack_pop()) == 0.0) {
                    printf("Error: divided by 0\n");
                    return -1;
                }
                stack_push(stack_pop() / t);
                break;
            case '%':
                if ((t = stack_pop()) == 0.0) {
                    printf("Error: divided by 0\n");
                    return -1;
                }
                stack_push(fmod(stack_pop(), t));
                break;
            case 's':
                stack_push(sin(stack_pop()));
                break;
            case 'e':
                stack_push(exp(stack_pop()));
                break;
            case 'p':
                t = stack_pop();
                stack_push(pow(stack_pop(), t));
                break;
            case '\n':
                printf("%f\n", stack_pop());
                break;
            default:
                printf("Error: unexpected symbol %s\n", s);
                break;
        }
    }
    return 0;
}

void stack_push(double n) {
    if (sp == STACKSIZE) {
        printf("Stack overflow\n");
        return;
    }
    stack[sp++] = n;
}

double stack_pop() {
    if (sp == 0) {
        printf("Stack is empty\n");
        return 0.0;
    }
    return stack[--sp];
}

void ungetch(int ch) {
    if (bp == BUFSIZE) {
        printf("Buffer overflow\n");
        return;
    }
    buf[bp++] = ch;
}

int getch() { return (bp > 0) ? buf[--bp] : getchar(); }

int getop(char* s) {
    int ch, i;

    while ((s[0] = ch = getch()) == ' ' || ch == '\t');

    s[1] = '\0';

    if (!isdigit(ch) && ch != '.' && ch != '-' && !isalpha(ch)) {
        return ch;
    }

    i = 0;

    if (ch == '-' && !isdigit(ch = getch())) {
        ungetch(ch);
        return '-';
    }

    if (s[0] == '-') s[++i] = ch;

    if (isdigit(ch)) {
        while (isdigit(s[++i] = ch = getch()));
    }

    if (ch == '.') {
        while (isdigit(s[++i] = ch = getch()));
    }
    s[i] = '\0';

    if (ch != EOF) ungetch(ch);

    return NUMBER;
}

void stack_print() {
    printf("%f\n", stack[sp]);
    return;
}

void stack_double() {
    stack[sp + 1] = stack[sp];
    sp++;
    return;
}

void stack_roll() {
    double t = stack[sp];
    stack[sp] = stack[sp - 1];
    stack[sp - 1] = t;
    return;
}

void stack_clear() {
    for (int i = 0; i < STACKSIZE; i++) {
        stack[i] = 0.0;
    }
    sp = 0;
    return;
}

void vars_create(void) {
    for (int i = 0; i < 26; i++) {
        vars[i] = 0.0;
    }
}

void vars_push(double n, uint8_t p) {
    vars[p] = n;
}

double vars_pop(uint8_t p) {
    return vars[p];
}
