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
    printf("Unsigned int MIN = %d\tMAX = %d\n", 0, UINT_MAX);

    // NOTE: SHORT INT VALUES
    printf("\nSigned short MIN = %d\tMAX = %d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned short MIN = %d\tMAX = %d\n", 0, USHRT_MAX);

    // NOTE: LONG INT VALUES
    printf("\nSigned long MIN = %d\tMAX = %d\n", LONG_MIN, LONG_MAX);
    printf("Unsigned long MIN = %d\tMAX = %d\n", 0, ULONG_MAX);

    // NOTE: FLOAT VALUES
    printf("\nSigned float MIN = %d\tMAX = %d\n", FLT_MIN, FLT_MAX);

    // NOTE: DOUBLE VALUES
    printf("\nSigned double MIN = %d\tMAX = %d\n", DBL_MIN, DBL_MAX);

    // NOTE: LONG DOUBLE VALUES
    printf("\nSigned long dooble MIN = %d\tMAX %d\n", LDBL_MIN, LDBL_MAX);

    // NOTE: LONG LONG VALUES
    printf(
        "\nSigned long long MIN = %d\tMAX = %d\n", LONG_LONG_MIN,
        LONG_LONG_MAX);
    printf("Unsigned long long MIN = %d\tMAX = %d\n", 0, ULONG_MAX);

    // NOTE: VALUES TAKEN BY MATH
    printf("\n\tVALUES TAKEN BY MATH\n");

    // NOTE: CHAR VALUES
    printf(
        "\nSigned char MIN = -%f\tMAX = %f\n",
        pow(2, (sizeof(char) * BITS) - 1),
        pow(2, (sizeof(char) * BITS) - 1) - 1);
    printf(
        "Unsigned char MIN = %d\tMAX = %f\n", 0,
        pow(2, sizeof(char) * BITS) - 1);

    // NOTE: INT VALUES
    printf(
        "\nSigned int MIN = -%f\tMAX = %f\n",
        pow(2, (sizeof(int) * BITS) - 1),
        pow(2, (sizeof(int) * BITS) - 1) - 1);
    printf(
        "Unsigned int MIN = %d\tMAX = %f\n",
        0,
        pow(2, sizeof(int) * BITS) - 1);

    // NOTE: SHORT INT VALUES
    printf(
        "\nSigned short MIN = -%f\tMAX = %f\n",
        pow(2, (sizeof(short) * BITS) - 1),
        pow(2, (sizeof(short) * BITS) - 1) - 1);
    printf("Unsigned short MIN = %d\tMAX = %f\n",
        0,
        pow(2, sizeof(short) * BITS) - 1);

    // NOTE: LONG INT VALUES
    printf("\nSigned long MIN = -%f\tMAX = %f\n",
        pow(2, (sizeof(long) * BITS) - 1),
        pow(2, (sizeof(long) * BITS) - 1) - 1);
    printf("Unsigned long MIN = %d\tMAX = %f\n",
        0,
        pow(2, sizeof(long) * BITS) - 1);

    // NOTE: FLOAT VALUES

    // NOTE: DOUBLE VALUES

    // NOTE: LONG DOUBLE VALUES

    // NOTE: LONG LONG VALUES
    return 0;
}
