#include <stdio.h>
#include <string.h>

void reverse(char* s);

int main() {
    char s[] = "Hello";
    reverse(s);
    printf("%s\n", s);
    return 0;
}

void reverse(char* s) {
    size_t tail = strlen(s) - 1;
    static int i = 0;

    if (i > tail / 2)
        return;
    
    char t = s[i];
    s[i] = s[tail - i];
    s[tail - i] = t;

    i++;

    reverse(s);
}