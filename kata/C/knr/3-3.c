#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv) {
    // if (argc < 2) return -1;
    // char* str = argv[2];

    char* str = "0-9";

    for(int i = 0; i < strlen(str); i++) {
        if (str[i] == '-' && i != 0 && i != strlen(str) - 1) {
            if ((isalpha(str[i - 1]) && isalpha(str[i + 1])) && (((str[i + 1]) - (str[i - 1])) > 2)) {
                for (int j = str[i - 1] + 1; j < str[i + 1]; j++) {
                    printf("%c", j);
                }
            }
            else
                printf("-");
        }
        else
            printf("%c", str[i]);
    }
    return 0;
}
