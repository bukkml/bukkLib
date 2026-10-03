#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACKLIMIT 500
#define LINELIMIT 100

int* stack;
int sp = 0;

void stackpush(int num);
int stackpop(void);
int getop(char* line);
int atoni(char* line);

int main(int argc, char** argv) {
    if (argc < 1) {
        printf("Use with arguments\n");
        return -1;
    }

    if ((stack = malloc(sizeof(int) * STACKLIMIT)) == NULL) return -1;

    while (argc-- > 1 && *++argv) {
        if (isdigit(**argv)) {
            stackpush(atoi(*argv));
            continue;
        }
        int t;
        switch (**argv) {
            case '+':
                stackpush(stackpop() + stackpop());
                break;
            case '*':
                stackpush(stackpop() * stackpop());
                break;
            case '-':
                if (*(*argv + 1) != '\0') {
                    stackpush(atoni(*argv + 1));
                    continue;
                }
                t = stackpop();
                stackpush(stackpop() - t);
                break;
            case '/':
                t = stackpop();
                if (t == 0) {
                    printf("Error: divided by 0\n");
                    free(stack);
                    return -1;
                }
                stackpush(stackpop() / t);
                break;
        }
    }

    printf("%d\n", stackpop());

    free(stack);
    return 0;
}

void stackpush(int num) { stack[sp++] = num; }

int stackpop() { return (sp > 0) ? stack[--sp] : 0; }

int atoni(char* line) {
    int res;
    for (res = 0; *line != '\0' && isdigit(*line); line++) {
        res = res * 10 + *line - '0';
    }
    return res * -1;
}
