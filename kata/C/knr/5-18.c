#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100
#define MAXBUF 100

typedef uint8_t u8;

enum { NAME, PARENS, BRACKETS };

void dcl();
void dirdcl();
int gettoken();    // Get token type
int is_validdt();  // Is data type valid
int getch();
void ungetch(int c);
int tokentype;            // Last token type
char token[MAXTOKEN];     // Last token text
char name[MAXTOKEN];      // Var/func name
char datatype[MAXTOKEN];  // Var/func type
char out[1000];           // Out text

char buf[MAXBUF];
u8 bp = 0;

int main() {
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        if (!is_validdt()) {
            printf("Data type is invalid\n");
            while (gettoken() != '\n');
        }
        else {
            out[0] = '\0';
            dcl();
            if (tokentype != '\n') {
                printf("Syntaxis error\n");
            }
            printf("%s: %s %s\n", name, out, datatype);
        }
    }
}

void dcl() {
    int ns;

    for (ns = 0; gettoken() == '*';) ns++;
    dirdcl();
    while (ns-- > 0) {
        strcat(out, " указ. на");
    }
}

void dirdcl() {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') printf("Error: Miss )\n");
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("Error: should be name or (dcl)\n");

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " функц. возвр.");
        else {
            strcat(out, " массив");
            strcat(out, token);
            strcat(out, " из");
        }
    }
}

int gettoken() {
    int c;

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
        for (*p++ = c; (*p++ = getch()) != ']';);
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

int is_validdt() {
    return strcmp(datatype, "char") || strcmp(datatype, "int") ||
           strcmp(datatype, "short") || strcmp(datatype, "long") ||
           strcmp(datatype, "float") || strcmp(datatype, "double") ||
           strcmp(datatype, "void");
}

int getch() { return (bp > 0) ? buf[--bp] : getchar(); }

void ungetch(int c) {
    if (bp == MAXBUF) {
        printf("Buffer owerflow\n");
        return;
    }
    buf[bp++] = c;
}
