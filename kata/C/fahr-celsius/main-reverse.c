#include <stdio.h>

int main() {

    float fahr, celsius;

    celsius = -30.0;

    printf("Celsius\t\t Fahr\n");

    while (celsius <= 30.0) {
        fahr = ((celsius * 9.0) / 5.0) + 32;
        printf("%5.0f\t\t%5.1f\n", celsius, fahr);
        celsius += 1;
    }
}
