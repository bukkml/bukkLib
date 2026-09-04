#include <stdio.h>

int main() {
    float fahr, celsius;

    fahr = -40;

    printf("Fahr\tCelsius\n");
    while (fahr <= 100) {
        celsius = (fahr - 32) * 5 / 9;
        printf("%3.0f\t%5.1f\n", fahr, celsius);
        fahr += 1;
    }
}
