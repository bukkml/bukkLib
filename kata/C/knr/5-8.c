#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8;

int dayofyear(int year, int month, int day);
void monthday(int year, int day, int* pmonth, int* pday);

u8 days[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int main() {
    printf("%d\n", dayofyear(1992, 3, 5));

    int m, d;
    monthday(1992, 65, &m, &d);
    printf("%d\t%d\n", m, d);

    return 0;
}

int dayofyear(int year, int month, int day) {
    if (month < 1 || month > 12 || day < 0 || day > 31) {
        printf("Incorrect data\n");
        return -1;
    }
    int res = 0;
    int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (day > days[leap][month]) {
        printf("Incorrect data\n");
        return -1;
    }

    while (--month > 0) {
        res += days[leap][month];
    }

    return res + day;
}
void monthday(int year, int day, int* pmonth, int* pday) {
    int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (day > 365 + leap) {
        printf("Incorrect data\n");
        return;
    }
    for (*pmonth = 1; day > days[leap][*pmonth];
         day -= days[leap][*pmonth], (*pmonth)++);
    *pday = day;
}
