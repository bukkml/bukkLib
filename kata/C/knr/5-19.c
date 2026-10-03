#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAXTOKEN 100
#define MAXBUF 100

typedef uint8_t u8;

enum { NAME, PARENS, BRACKETS };

int gettoken();
int getch();
void ungetch(int c);
int nexttoken();
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
bool prev_token = false;

char buf[MAXBUF];
u8 bp = 0;

int main() {
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
       strcpy(out, token);
       while((tokentype = gettoken()) != '\n') {
        if (tokentype == PARENS || tokentype == BRACKETS) {
            strcat(out, token);
        }
        else if (tokentype == '*') {
            if ((tokentype = nexttoken()) != PARENS && tokentype != BRACKETS)
                sprintf(temp, "*%s", out);
            else 
                sprintf(temp, "(*%s)", out);
            strcpy(out, temp);
        }
        else if (tokentype == NAME) {
            sprintf(temp, "%s %s", token, out);
            strcpy(out, temp);
        }
        else
            printf("Unexpected element %s\n", token);
       }
       printf("%s\n", out);
    }
    return 0;
}

int gettoken() {
    int c;

    if (prev_token == true) {
        prev_token = false;
        return tokentype;
    }

    char* p = token;
    while ((c = getch()) == ' ' || c == '\t');

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for(*p++ = c; (*p++ = getch()) != ']';);
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());) *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

int nexttoken() {
    prev_token = true;
    return gettoken();
}

int getch() {
    return (bp > 0) ? buf[--bp] : getchar();
}

void ungetch(int c) {
    if (bp == MAXBUF) {
        printf("Buffer overflow\n");
        return;
    }
    buf[bp++] = c;
}