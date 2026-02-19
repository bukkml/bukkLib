#include <stdbool.h>
#include <stdio.h>

#define LINE_WIDTH 40
#define MAX_WIDTH 100

static bool is_delim(int c) { return c == ' ' || c == '\t'; }

static void flush_line(char line[], int* len) {
    if (*len > 0) fwrite(line, 1, *len, stdout);
    putchar('\n');
    *len = 0;
}

int main() {
    char line[MAX_WIDTH];
    int len = 0;
    int last_delim = -1;
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            flush_line(line, &len);
            last_delim = -1;
            continue;
        }

        else if (len == MAX_WIDTH) {
            fprintf(
                stderr, "Error: Word exceeds maximum width (%d)\n", MAX_WIDTH);
            return -1;
        }

        else if (len == LINE_WIDTH) {
            if (is_delim(c)) {
                flush_line(line, &len);
                last_delim = -1;
                continue;
            }

            else if (last_delim > -1) {
                fwrite(line, 1, last_delim, stdout);
                putchar('\n');
                int new_len = 0;
                for (int i = last_delim + 1; i < len; ++i) {
                    line[new_len++] = line[i];
                }
                len = new_len;
                line[len] = c;
                if (is_delim(c)) last_delim = len;
                len++;
                last_delim = -1;
                for (int i = 0; i < len; i++) {
                    if (is_delim(line[i])) last_delim = i;
                }
            }

            else {
                line[len] = c;
                if (is_delim(c)) last_delim = len;
                len++;
            }
        }

        else if (len >= LINE_WIDTH && is_delim(c)) {
            flush_line(line, &len);
        }

        else {
            line[len] = c;
            if (is_delim(c)) last_delim = len;
            len++;
        }
    }

    if (len > 0) {
        putchar('\n');
        flush_line(line, &len);
    }

    return 0;
}
