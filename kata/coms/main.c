#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define QUOTES_IN true
#define QUOTES_OUT false

// typedef bool quotes_state_t;

enum error_code { ERR_NO_FILE = -1, ERR_BAD_NAME = -2, ERR_OPEN_FAILED = -3 };

enum State {
    NORMAL,
    SLASH,
    LINE_COMMENT,
    BLOCK_COMMENT,
    BLOCK_COMMENT_STAR,
    STRING_LITERAL,
    CHAR_LITERAL,
    ESCAPE_IN_STRING,
    ESCAPE_IN_CHAR
};

// quotes_state_t toggle_quotes_state(quotes_state_t quotes_state) {
//     return (quotes_state == QUOTES_IN) ? QUOTES_OUT : QUOTES_IN;
// }

bool is_valid_c_filename(const char* filename) {  // check file name
    if (filename == NULL || *filename == '\0') return false;

    const char* dot = strrchr(filename, '.');
    if (!dot) return false;

    if (strcmp(dot, ".c") != 0) return false;

    if (dot == filename) return false;

    for (const char* p = filename; p < dot; ++p) {
        if (*p == '.') return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    int ch;
    int prev_ch = -1;
    //    quotes_state_t quotes_state = QUOTES_OUT;
    enum State state = NORMAL;

    if (argc != 2) {
        fprintf(stderr, "Usage: program <file.c>\n");
        return ERR_NO_FILE;
    }

    const char* filename = argv[1];
    const char* tmp_filename = tmpnam(NULL);

    if (!is_valid_c_filename(filename)) {
        fprintf(stderr, "Invalid filename\n");
        return ERR_BAD_NAME;
    }

    FILE* input_file = fopen(filename, "r");
    FILE* output_file = fopen(tmp_filename, "w");
    if (input_file == NULL) {
        fprintf(stderr, "File open error\n");
        return ERR_OPEN_FAILED;
    }

    while ((ch = fgetc(input_file)) != EOF) {
        switch (state) {
            case (NORMAL):
                if (ch == '/') {
                    state = SLASH;
                    continue;
                }
                else if (ch == '\'') {
                    fputc(ch, output_file);
                    state = CHAR_LITERAL;
                    continue;
                }
                else if (ch == '\"') {
                    fputc(ch, output_file);
                    state = STRING_LITERAL;
                    continue;
                }
                else {
                    fputc(ch, output_file);
                    continue;
                }
                continue;

            case (SLASH):
                if (ch == '/') {
                    state = LINE_COMMENT;
                    continue;
                }
                else if (ch == '*') {
                    state = BLOCK_COMMENT;
                    continue;
                }
                else {
                    fputc('/', output_file);
                    fputc(ch, output_file);
                    state = NORMAL;
                    continue;
                }
                continue;

            case (LINE_COMMENT):
                if (ch == '\n') {
                    fputc('\n', output_file);
                    state = NORMAL;
                    continue;
                }
                continue;

            case (BLOCK_COMMENT):
                if (ch == '*') {
                    state = BLOCK_COMMENT_STAR;
                    continue;
                }
                continue;

            case (BLOCK_COMMENT_STAR):
                if (ch == '/') {
                    state = NORMAL;
                    continue;
                }
                else {
                    state = BLOCK_COMMENT;
                    continue;
                }
                continue;

            case (STRING_LITERAL):
                fputc(ch, output_file);
                if (ch == '\\') {
                    state = ESCAPE_IN_STRING;
                    continue;
                }
                if (ch == '\"') {
                    state = NORMAL;
                    continue;
                }
                continue;

            case (CHAR_LITERAL):
                fputc(ch, output_file);
                if (ch == '\\') {
                    state = ESCAPE_IN_CHAR;
                    continue;
                }
                if (ch == '\'') {
                    state = NORMAL;
                    continue;
                }
                continue;

            case (ESCAPE_IN_STRING):
                fputc(ch, output_file);
                state = STRING_LITERAL;
                continue;

            case (ESCAPE_IN_CHAR):
                fputc(ch, output_file);
                state = CHAR_LITERAL;
                continue;
        }
    }

    fclose(input_file);
    remove(filename);
    fclose(output_file);
    rename(tmp_filename, filename);

    return 0;
}
