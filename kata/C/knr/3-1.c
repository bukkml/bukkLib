#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2000000
#define TESTS 2000000

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

i64 Binsearch(i32 x, i32 array[], u32 n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < array[mid])
            high = --mid;
        else if (x > array[mid])
            low = ++mid;
        else
            return mid;
    }
    return -1;
}

i64 Binsearch2(i32 x, i32 array[], u32 n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < array[mid])
            high = --mid;
        else
            low = ++mid;
    }
    return (x == array[mid]) ? mid : -1;
}

static double elapsed_ns(struct timespec* start, struct timespec* end) {
    return (double)(end->tv_sec - start->tv_sec) * 1000000000.0 +
           (double)(end->tv_nsec - start->tv_nsec);
}

int main(void) {
    srand(time(NULL));

    i32* array = malloc(N * sizeof(i32));

    if (!array) {
        perror("malloc");
        return -1;
    }

    i32* tests = malloc(TESTS * sizeof(i32));

    if (!tests) {
        perror("malloc");
        free(array);
        return -1;
    }

    for (u32 i = 0; i < N; ++i) {
        array[i] = (i32)i;
    }

    for (u32 i = 0; i < TESTS; ++i) {
        tests[i] = rand() % INT32_MAX;
    }

    struct timespec start, end;

    volatile i64 checksum1 = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (u32 i = 0; i < TESTS; ++i) {
        checksum1 = Binsearch(tests[i], array, N);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time1 = elapsed_ns(&start, &end);

    volatile i64 checksum2 = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (u32 i = 0; i < TESTS; ++i) {
        checksum2 = Binsearch2(tests[i], array, N);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time2 = elapsed_ns(&start, &end);

    printf("Array size: %u\n", N);
    printf("Tests: %u\n\n", TESTS);

    printf("Binsearch:\n");
    printf(" total: %.3f ms\n", time1 / 1e6);
    printf(" per call: %.3f ns\n", time1 / TESTS);
    printf(" checksum: %lld\n\n", (long long)checksum1);

    printf("Binsearch2:\n");
    printf(" total: %.3f ms\n", time2 / 1e6);
    printf(" per call: %.3f ns\n", time2 / TESTS);
    printf(" checksum: %lld\n\n", (long long)checksum2);

    printf("Ratio Binsearch2 / Binsearch: %.3fx\n", time2 / time1);

    free(array);
    free(tests);
}
