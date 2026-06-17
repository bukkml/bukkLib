#include <ctype.h>
#include <math.h>
#include <stdio.h>

int htoi(char* hex) {
    if (hex[0] != '0' || (hex[1] != 'x' && hex[1] != 'X')) return -1;

    int i = 0;
    int result = 0;

    for (i = 0; hex[i] != '\0'; i++);

    for (int j = 2; j < i; j++) {
        int h = 0;
        if (isdigit(hex[j])) {
            h = hex[j] - '0';
        }
        else if (
            (hex[j] >= 'a' && hex[j] <= 'f') ||
            (hex[j] >= 'A' && hex[j] <= 'F')) {
            h = toupper(hex[j]);
            h = h - 'A' + 10;
        }
        else
            return -1;

        result += h * pow(16, i - j - 1);
    }

    return result;
}

int main() {
    char* hex = "0x76a81273";
    printf("%d\n", htoi(hex));
    return 0;
}
