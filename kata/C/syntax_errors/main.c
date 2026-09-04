#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false, true } bool;

typedef enum {
    NORMAL,
    SLASH,
    LINE_COMMENT,
    BLOCK_COMMENT,
    BLOCK_COMMENT_STAR,
    STRING_LITERAL,
    CHAR_LITERAL,
    ESCAPE_IN_STRING,
    ESCAPE_IN_CHAR,
} State;

typedef struct {
    int parenthesis;
    int braces;
    int brackets;
    int angle_brackets;
    int single_quotes;
    int double_quotes;
} Pairing;

typedef struct {
    FILE* file;
    int _char;
    Pairing pairs;
    State state;
} Parser;

FILE* file_open(const char* filename);
Parser* parser_begin(const char* filename);
void parser_process(Parser* parser);
void parser_end(Parser* parser);
void parser_result(Parser* parser);
void parser_check(Parser* parser);

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file.c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Parser* parser = parser_begin(argv[1]);
    if (parser == NULL) {
        return EXIT_FAILURE;
    }

    parser_process(parser);

    parser_result(parser);

    parser_end(parser);

    return EXIT_SUCCESS;
}

bool is_filename_valid(const char* filename) {
    if (filename == NULL || filename[0] == '\0') {
        return false;
    }

    const char* dot = strrchr(filename, '.');

    if (dot == NULL || dot == filename) {
        return false;
    }

    if (strchr(filename, '.') != dot) {
        return false;
    }

    return strcmp(dot, ".c") == 0;
}

FILE* file_open(const char* filename) {
    if (!is_filename_valid(filename)) {
        fprintf(
            stderr, "error: invalid filename \"%s\"\n",
            filename ? filename : "(null)");
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(
            stderr, "error: failed to open file \"%s\": %s\n", filename,
            strerror(errno));
        return NULL;
    }

    return file;
}

Parser* parser_begin(const char* filename) {
    Parser* parser = malloc(sizeof(*parser));
    if (!parser) {
        fprintf(stderr, "error: malloc failed\n");
        return NULL;
    }

    parser->file = file_open(filename);
    if (!parser->file) {
        parser_end(parser);
        return NULL;
    }

    parser->pairs = (Pairing){0};
    parser->state = NORMAL;

    return parser;
}

void parser_process(Parser* parser) {
    while ((parser->_char = fgetc(parser->file)) != EOF) {
        switch (parser->state) {
            case (NORMAL):
                parser_check(parser);
                if (parser->_char == '/') {
                    parser->state = SLASH;
                    continue;
                }
                else if (parser->_char == '\'') {
                    parser->state = CHAR_LITERAL;
                    continue;
                }
                else if (parser->_char == '\"') {
                    parser->state = STRING_LITERAL;
                    continue;
                }
                continue;

            case (SLASH):
                if (parser->_char == '/') {
                    parser->state = LINE_COMMENT;
                    continue;
                }
                else if (parser->_char == '*') {
                    parser->state = BLOCK_COMMENT;
                    continue;
                }
                else {
                    parser->state = NORMAL;
                    continue;
                }
                continue;

            case (LINE_COMMENT):
                if (parser->_char == '\n') {
                    parser->state = NORMAL;
                    continue;
                }
                continue;

            case (BLOCK_COMMENT):
                if (parser->_char == '*') {
                    parser->state = BLOCK_COMMENT_STAR;
                    continue;
                }
                continue;

            case (BLOCK_COMMENT_STAR):
                if (parser->_char == '/') {
                    parser->state = NORMAL;
                    continue;
                }
                else {
                    parser->state = BLOCK_COMMENT;
                }
                continue;

            case (STRING_LITERAL):
                if (parser->_char == '\\') {
                    parser->state = ESCAPE_IN_STRING;
                    continue;
                }
                if (parser->_char == '\"') {
                    parser->state = NORMAL;
                    continue;
                }
                continue;

            case (CHAR_LITERAL):
                if (parser->_char == '\\') {
                    parser->state = ESCAPE_IN_CHAR;
                    continue;
                }
                else if (parser->_char == '\'') {
                    parser->state = NORMAL;
                    continue;
                }
                continue;

            case (ESCAPE_IN_STRING):
                parser->state = STRING_LITERAL;
                continue;
            case (ESCAPE_IN_CHAR):
                parser->state = CHAR_LITERAL;
                continue;
        }
    }
}

void parser_check(Parser* parser) {
    if (parser->_char == '\'') {
        parser->pairs.single_quotes++;
    }

    else if (parser->_char == '\"') {
        parser->pairs.double_quotes++;
    }

    else if (parser->_char == '(') {
        parser->pairs.parenthesis++;
    }
    else if (parser->_char == ')') {
        parser->pairs.parenthesis--;
    }

    else if (parser->_char == '[') {
        parser->pairs.braces++;
    }
    else if (parser->_char == ']') {
        parser->pairs.braces--;
    }

    else if (parser->_char == '{') {
        parser->pairs.brackets++;
    }
    else if (parser->_char == '}') {
        parser->pairs.brackets--;
    }

    else if (parser->_char == '<') {
        parser->pairs.angle_brackets++;
    }
    else if (parser->_char == '>') {
        parser->pairs.angle_brackets--;
    }
}

void parser_result(Parser* parser) {
    if (parser->pairs.parenthesis != 0) {
        printf("Not paired parenthesis\n");
    }

    if (parser->pairs.braces != 0) {
        printf("Not paired brackes\n");
    }

    if (parser->pairs.brackets != 0) {
        printf("Not paired brackets\n");
    }

    if (parser->pairs.angle_brackets != 0) {
        printf("Not paired angle brackets\n");
    }

    if ((parser->pairs.single_quotes / 2) != 0) {
        printf("Not paired single quotes\n");
    }

    if ((parser->pairs.double_quotes / 2) != 0) {
        printf("Not paired double quotes\n");
    }

    if (parser->state == BLOCK_COMMENT) {
        printf("Block comment not closed\n");
    }

    if (parser->state == STRING_LITERAL) {
        printf("String literal not closed\n");
    }

    if (parser->state == CHAR_LITERAL) {
        printf("Char literal not closed\n");
    }
}

void parser_end(Parser* parser) {
    fclose(parser->file);
    free(parser);
}
