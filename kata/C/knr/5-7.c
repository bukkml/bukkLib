#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 100

typedef struct {
    char* arr[MAXLINES];
    int size;
} lineptr;

int readline_(char* line);
int readlines(lineptr* lines);
void swap(lineptr* lines, int i, int j);
void quicksort(lineptr* lines, int left, int right);
void writelines(lineptr* lines);
void freelines(lineptr* lines);

int main() {
    lineptr* lines = (lineptr*)malloc(sizeof(lineptr));
    if (!lines) return -1;

    lines->size = 0;

    if (!readlines(lines)) {
        free(lines);
        return -1;
    }

    quicksort(lines, 0, lines->size - 1);
    writelines(lines);
    freelines(lines);

    free(lines);

    return 0;
}

int readline_(char* line) {
    int ch;
    int lim = 0;

    while (lim++ < MAXLEN && (ch = getchar()) != EOF && ch != '\n')
        *line++ = (char)ch;

    if (ch != EOF && ch != '\n')
        while ((ch = getchar()) != EOF && ch != '\n');

    *line = '\0';

    return lim > 1;
}

int readlines(lineptr* lines) {
    char line[MAXLEN];

    while (lines->size < MAXLINES && readline_(line)) {
        if (!(lines->arr[lines->size] = malloc(sizeof(char) * MAXLEN))) {
            freelines(lines);
            return 0;
        }
        strcpy(lines->arr[lines->size++], line);
    }

    return 1;
}

void swap(lineptr* lines, int i, int j) {
    char* tmp;

    tmp = lines->arr[i];
    lines->arr[i] = lines->arr[j];
    lines->arr[j] = tmp;
}

void quicksort(lineptr* lines, int left, int right) {
    int i, last;

    if (left >= right) return;

    swap(lines, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (strcmp(lines->arr[i], lines->arr[left]) < 0) swap(lines, ++last, i);
    }
    swap(lines, left, last);
    quicksort(lines, left, last - 1);
    quicksort(lines, last + 1, right);
}

void writelines(lineptr* lines) {
    for (int i = 0; i < lines->size; i++) {
        printf("%s\n", lines->arr[i]);
    }
}

void freelines(lineptr* lines) {
    while (lines->size > 0) {
        free(lines->arr[lines->size--]);
    }
}
