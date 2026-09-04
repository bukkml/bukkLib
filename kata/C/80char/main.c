#include <stdio.h>

#define LINELEN 80
#define MAXLEN 1000
#define MAXLINES 10

int getline_(char *line) {
    int c, i;
    for (i= 0; i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';
    return i;
}

void copy(char *to, const char *from) {
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        i++;
    }
}

int main() {
    char line[MAXLEN];
    char answer[MAXLINES][MAXLEN];
    int len, i;
    i = 0;
    while ((len = getline_(line)) > 0) {
        if (len >= 80) {
            copy(answer[i], line);
            i++;
        }
    }

    for (int j = 0; j < i; j++) {
        printf("%s", answer[j]);
    }

    return 0;
}
