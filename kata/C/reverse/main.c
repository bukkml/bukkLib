#include <stdio.h>

#define MAXLEN 1000
#define MAXLINES 100

int _getline(char *line) {
    int c, i;

    for (i = 0; i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';

    return i;
}

void copy(char *to, char *from) {
    int i = 0;
    while (from[i] != '\0') {
        to[i] = from[i];
        i++;
    }
    i++;
    to[i] = from[i];
}

void reverse(char *word, int len) {
    char new_word[MAXLEN];
    int j = 0;

    for (int i = len - 1; i >= 0; --i) {
        if (word[i] == '\0' || word[i] == '\n');
        else {
            new_word[j] = word[i];
            j++;
        }
    }
    new_word[j] = '\n';
    new_word[j++] = '\0';
    copy(word, new_word);
}


int main() {

    char line[MAXLEN];
    int c, len;

    while ((len = _getline(line)) > 1) {
        reverse(line, len);
        printf("%s", line);

    }

    return 0;
}
