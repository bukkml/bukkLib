#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

int getline_(char* s, int lim);
int strindex(char* s, char* t);

char* pattern = "ould";

int main() {
    int i = 0;

    char* line = malloc(sizeof(char) * MAXLEN);
    if (!line) {
        printf("Error: Malloc\n");
    }

    while (getline_(line, MAXLEN)) {
        if (strindex(line, pattern) != -1) {
            printf("%s\n", line);
        }
    }

    free(line);

    return 0;
}

int getline_(char* s, int lim) {
    int i, c;
    i = 0;
    while(--lim > 0 && (c = getchar()) != EOF && c != '\n') {   
        s[i++] = c;
    }
    if (lim < 2) {
        printf("Error: MAXLEN\n");
        return -1;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int strindex(char* s, char* t) {
    int i, j, k;
    for (i = strlen(s) - 1; i >= 0; i--) {
        for (j = i, k = strlen(t) - 1; k >= 0 && s[j] == t[k]; j--, k--);
        if (k < 0) {
            return j + 1;
        }
    }
    
    return -1;
}
