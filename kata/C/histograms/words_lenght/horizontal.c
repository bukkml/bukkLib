#include <stdio.h>
#include <stdlib.h>

#define IN 1
#define OUT 0
#define FLAG int

int main() {
    int max_lenght = 100;
    int* words_lenght = (int*)malloc(sizeof(int) * max_lenght);
    if (words_lenght == NULL) {
        printf("Malloc failed\n");
        return 1;
    }
    int c, wlenght;
    FLAG state;

    wlenght = 0;
    state = OUT;
    for (int i = 0; i < max_lenght; i++) {
        words_lenght[i] = 0;
    }
    while ((c = getchar()) != EOF) {
        if (state == OUT) {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                state = IN;
            }
        }
        if (state == IN) {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                wlenght++;
            }
            else {
                if (wlenght >= max_lenght) {
                    int old_max_lenght = max_lenght;
                    max_lenght = wlenght + 1;
                    int *tmp = realloc(words_lenght, sizeof(int) * max_lenght);
                    if (tmp == NULL) {
                        free(words_lenght);
                        printf("Realloc failed\n");
                        return 1;
                    }
                    words_lenght = tmp;
                    for (int i = old_max_lenght; i < max_lenght; i++) {
                        words_lenght[i] = 0;
                    }
                }
                words_lenght[wlenght]++;
                state = OUT;
                wlenght = 0;
            }
        }
    }

    for (int i = 0; i < max_lenght; i++) {
        if (words_lenght[i] != 0) {
            printf("%d: ", i);
            for (int j = 0; j < words_lenght[i]; j++) {
                printf("■");
            }
            printf(" %d\n", words_lenght[i]);
        }
    }

    free(words_lenght);
    return 0;
}
