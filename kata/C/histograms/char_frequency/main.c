#include <stdio.h>
#include <stdlib.h>

#define TOTAL 26

int main() {

    int c;
    int *chars =(int*)malloc(sizeof(int) * TOTAL);
    if (chars == NULL) {
        printf("Malloc failed\n");
        return 1;
    }
    for (int i = 0; i < TOTAL; i++) {
        chars[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c >= 'A' && c <= 'Z') {
            c -= 'A';
            chars[c]++;
        }
        else if (c >= 'a' && c <= 'z') {
            c -= 'a';
            chars[c]++;
        }
    }

    for (int i = 0; i < TOTAL; i++) {
        if (chars[i] > 0) {
            printf("%c  ", i + 'a');
            for (int j = 0; j < chars[i]; j++) {
                printf("■");
            }
            printf("\n");
        }
    }

    free(chars);
}
