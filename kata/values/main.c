#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#define BITS 8

int main() {
    // NOTE: VALUES TAKEN BY <limits.h> AND <float.h>

    // NOTE: CHARS VALUES
    printf("Signed char MIN = %d\tMAX = %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("Unsigned char MIN = %d\tMAX = %d\n", 0, UCHAR_MAX);

    // NOTE: INT VALUES
    printf("\nSigned int MIN = %d\tMAX = %d\n", INT_MIN, INT_MAX);
    printf("Unsigned int MIN = %d\tMAX = %u\n", 0, UINT_MAX);

    // NOTE: SHORT INT VALUES
    printf("\nSigned short MIN = %d\tMAX = %d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned short MIN = %d\tMAX = %d\n", 0, USHRT_MAX);

    // NOTE: LONG INT VALUES
    printf("\nSigned long MIN = %ld\tMAX = %ld\n", LONG_MIN, LONG_MAX);
    printf("Unsigned long MIN = %d\tMAX = %lu\n", 0, ULONG_MAX);

    // NOTE: FLOAT VALUES
    printf("\nSigned float MIN = %e\tMIN_POS = %e\tMAX = %e\n", -FLT_MAX, FLT_MIN, FLT_MAX);

    // NOTE: DOUBLE VALUES
    printf("\nSigned double MIN = %e\tMIN_POS = %e\tMAX = %e\n", -DBL_MAX, DBL_MIN, DBL_MAX);

    // NOTE: LONG DOUBLE VALUES
    printf("\nSigned long dooble MIN = %Le\tMIN_POS = %Le\tMAX %Le\n", -LDBL_MAX, LDBL_MIN, LDBL_MAX);

    // NOTE: LONG LONG VALUES
    printf(
        "\nSigned long long MIN = %lld\tMAX = %lld\n", LONG_LONG_MIN,
        LONG_LONG_MAX);
    printf("Unsigned long long MIN = %d\tMAX = %lu\n", 0, ULONG_MAX);

    // NOTE: VALUES TAKEN BY MATH
    printf("\n\tVALUES TAKEN BY MATH");

    // NOTE: CHAR VALUES
    printf(
        "\nSigned char MIN = -%.0f\tMAX = %.0f\n",
        pow(2, (sizeof(char) * BITS) - 1),
        pow(2, (sizeof(char) * BITS) - 1) - 1);
    printf(
        "Unsigned char MIN = %d\tMAX = %.0f\n", 0,
        pow(2, sizeof(char) * BITS) - 1);

    // NOTE: INT VALUES
    printf(
        "\nSigned int MIN = -%.0f\tMAX = %.0f\n",
        pow(2, (sizeof(int) * BITS) - 1),
        pow(2, (sizeof(int) * BITS) - 1) - 1);
    printf(
        "Unsigned int MIN = %d\tMAX = %.0f\n",
        0,
        pow(2, sizeof(int) * BITS) - 1);

    // NOTE: SHORT INT VALUES
    printf(
        "\nSigned short MIN = -%.0f\tMAX = %.0f\n",
        pow(2, (sizeof(short) * BITS) - 1),
        pow(2, (sizeof(short) * BITS) - 1) - 1);
    printf("Unsigned short MIN = %d\tMAX = %.0f\n",
        0,
        pow(2, sizeof(short) * BITS) - 1);

    // NOTE: LONG INT VALUES
    printf("\nSigned long MIN = %ld\tMAX = %ld\n",
        -(1L << (sizeof(long) * BITS - 1)),
        (1L << (sizeof(long) * BITS - 1)) - 1);
    printf("Unsigned long MIN = %lu\tMAX = %lu\n",
        0UL,
        ~0UL);

    // NOTE: FLOAT VALUES

    // NOTE: DOUBLE VALUES

    // NOTE: LONG DOUBLE VALUES

    // NOTE: LONG LONG VALUES
    printf("\nSigned long long MIN = %lld\tMAX = %lld\n",
        (1LL << 63),
        (1LL << 63) - 1);
    printf("Unsigned long long MIN = %llu\tMAX = %llu\n",
        0ULL,
        ~0ULL);
    return 0;
}
