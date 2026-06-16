#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#define BITS 8

int main() {
    // NOTE: VALUES TAKEN BY <limits.h> AND <float.h>

    // NOTE: CHARS VALUES
    printf(
        "%-25s%-20d\t%5s%-20d\n", "Signed char MIN = ", SCHAR_MIN,
        "MAX = ", SCHAR_MAX);
    printf(
        "%-25s%-20d\t%5s%-20d\n", "Unsigned char MIN = ", 0,
        "MAX = ", UCHAR_MAX);

    // NOTE: INT VALUES
    printf(
        "\n%-25s%-20d\t%5s%-20d\n", "Signed int MIN = ", INT_MIN,
        "MAX = ", INT_MAX);
    printf(
        "%-25s%-20d\t%5s%-20u\n", "Unsigned int MIN = ", 0, "MAX = ", UINT_MAX);

    // NOTE: SHORT INT VALUES
    printf(
        "\n%-25s%-20d\t%5s%-20d\n", "Signed short MIN = ", SHRT_MIN,
        "MAX = ", SHRT_MAX);
    printf(
        "%-25s%-20d\t%5s%-20d\n", "Unsigned short MIN = ", 0,
        "MAX = ", USHRT_MAX);

    // NOTE: LONG INT VALUES
    printf(
        "\n%-25s-%-20lu\t%5s%-20lu\n", "Signed long MIN = ", LONG_MIN,
        "MAX = ", LONG_MAX);
    printf(
        "%-25s%-20d\t%5s%-20lu\n", "Unsigned long MIN = ", 0,
        "MAX = ", ULONG_MAX);

    // NOTE: LONG LONG VALUES
    printf(
        "\n%-25s-%-20llu\t%5s%-20llu\n",
        "Signed long long MIN = ", LONG_LONG_MIN, "MAX = ", LONG_LONG_MAX);
    printf(
        "%-25s%-20d\t%5s%-20llu\n", "Unsigned long long MIN = ", 0,
        "MAX = ", ULONG_LONG_MAX);

    // NOTE: FLOAT VALUES
    printf(
        "\n%-25s%-20e\t%9s%-20e\t%5s%-20e\n", "Singed float MIN = ", -FLT_MAX,
        "MIN_POS = ", FLT_MIN, "MAX = ", FLT_MAX);

    // NOTE: DOUBLE VALUES
    printf(
        "\n%-25s%-20e\t%9s%-20e\t%5s%-20e\n", "Signed double MIN = ", -DBL_MAX,
        "MIN_POS = ", DBL_MIN, "MAX = ", DBL_MAX);

    // NOTE: LONG DOUBLE VALUES
    printf(
        "\n%-25s%-20Le\t%9s%-20Le\t%5s%-20Le\n",
        "Signed long double MIN = ", -LDBL_MAX, "MIN_POS = ", LDBL_MIN,
        "MAX = ", LDBL_MAX);

    // NOTE: VALUES TAKEN BY MATH
    printf("\n\t\t\t\tVALUES TAKEN BY MATH");

    // NOTE: CHAR VALUES
    printf(
        "\n%-25s-%-20.0f\t%5s%-20.0f\n",
        "Signed char MIN = ", pow(2, sizeof(char) * BITS - 1),
        "MAX = ", pow(2, sizeof(char) * BITS - 1) - 1);
    printf(
        "%-25s%-20d\t%5s%-20.0f\n", "Unsigned char MIN = ", 0,
        "MAX = ", pow(2, sizeof(char) * BITS) - 1);

    // NOTE: INT VALUES
    printf(
        "\n%-25s-%-20.0f\t%5s%-20.0f\n",
        "Signed int MIN = ", pow(2, sizeof(int) * BITS - 1),
        "MAX = ", pow(2, sizeof(int) * BITS - 1) - 1);
    printf(
        "%-25s%-20d\t%5s%-20.0f\n", "Unsigned int MIN = ", 0,
        "MAX = ", pow(2, sizeof(int) * BITS) - 1);

    // NOTE: SHORT INT VALUES
    printf(
        "\n%-25s-%-20.0f\t%5s%-20.0f\n",
        "Signed short MIN = ", pow(2, sizeof(short) * BITS - 1),
        "MAX = ", pow(2, sizeof(short) * BITS - 1) - 1);
    printf(
        "%-25s%-20d\t%5s%-20.0f\n", "Unsigned short MIN = ", 0,
        "MAX = ", pow(2, sizeof(short) * BITS) - 1);

    // NOTE: LONG INT VALUES
    printf(
        "\n%-25s-%-20lu\t%5s%-20lu\n",
        "Signed long MIN = ", (long)pow(2, sizeof(long) * BITS - 1),
        "MAX = ", (long)pow(2, sizeof(long) * BITS - 1) - 1);
    printf(
        "%-25s%-20d\t%5s%-20lu\n", "Unsigned long MIN = ", 0,
        "MAX = ", (long)pow(2, sizeof(long) * BITS) - 1);

    // printf(
    //     "\nSigned long MIN = %20ld\tMAX = %20ld\n",
    //     -(1L << (sizeof(long) * BITS - 1)),
    //     (1L << (sizeof(long) * BITS - 1)) - 1);
    // printf("Unsigned long MIN = %20lu\tMAX = %20lu\n", 0UL, ~0UL);

    // NOTE: LONG LONG VALUES
    printf(
        "\n%-25s-%-20.0f\t%5s%-20.0f\n",
        "Signed long long MIN = ", pow(2, sizeof(long long) * BITS - 1),
        "MAX = ", pow(2, sizeof(long long) * BITS - 1) - 1);
    printf(
        "%-25s%-20d\t%5s%-20.0f\n", "Unsigned long long MIN = ", 0,
        "MAX = ", pow(2, sizeof(long long) * BITS) - 1);
    // printf(
    //     "\nSigned long long MIN = %20lld\tMAX = %20lld\n", (1LL << 63),
    //     (1LL << 63) - 1);
    // printf("Unsigned long long MIN = %20llu\tMAX = %20llu\n", 0ULL, ~0ULL);

    // NOTE: FLOAT VALUES

    // NOTE: DOUBLE VALUES

    // NOTE: LONG DOUBLE VALUES

    return 0;
}
