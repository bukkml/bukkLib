#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void escape(char* s, char* t) {
    int i = 0, j = 0;
    while (s[i] != '\0') {
        switch (s[i]) {
            case ('\n'):
                t[j++] = '\\';
                t[j++] = 'n';
                break;

            case ('\t'):
                t[j++] = '\\';
                t[j++] = 't';
                break;

            case ('\\'):
                t[j++] = '\\';
                t[j++] = '\\';
                break;

            case ('\b'):
                t[j++] = '\\';
                t[j++] = 'b';
                break;

            default:
                t[j++] = s[i];
                break;
        }
        i++;
    }
    t[j++] = '\\';
    t[j++] = '0';
    t[j] = '\0';
}

void unescape(char* s, char* t) {
    int i = 0, j = 0;
    while (s[i] != '\0') {
        switch (s[i]) {
            case ('\\'):
                switch (s[i + 1]) {
                    case ('n'):
                        t[j++] = '\n';
                        i++;
                        break;

                    case ('t'):
                        t[j++] = '\t';
                        i++;
                        break;

                    case ('b'):
                        t[j++] = '\b';
                        i++;
                        break;
                    case ('0'):
                        t[j++] = '\0';
                        i++;
                    default:
                        t[j++] = '\\';
                        i++;
                        break;
                }
                break;
            default:
                t[j++] = s[i];
                break;
        }
        i++;
    }
    if (t[j - 1] != '\0') t[j] = '\0';
}

int main(void) {
    char* str = "Привет, меня\tзовут\t\tМаксим\n!\t. А\tтебя?\0";

    char* tstr = malloc(sizeof(char) * (strlen(str) + 10));
    escape(str, tstr);
    char* sstr = malloc(sizeof(char) * (strlen(str) + 10));
    unescape(tstr, sstr);

    printf(
        "Text 1(original):\n%s\n\nText 2(after escape):\n%s\n\nText 3(after "
        "unescape):\n%s\n\n",
        str, tstr, sstr);

    free(tstr);
    free(sstr);
    return 0;
}
