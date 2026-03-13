#include <stdio.h>

#define MAXLEN 1000

int getline_(char line[MAXLEN], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }

    if (c == '\n') {
        line[i] = c;
        i++;
    }

    line[i] = '\0';
    return i;
}

void copy(char to[], char from[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        i++;
    }
}

int main() {
    int len;               // Длина текущей строки
    int max;               // Длина максимальной строки
    char line[MAXLEN];     // Текущая строка
    char longest[MAXLEN];  // Самая длинная строка

    max = 0;
    while ((len = getline_(line, MAXLEN)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0) {
        printf("%s\n", longest);
    }
}
