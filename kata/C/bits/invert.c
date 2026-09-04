#include <stdio.h>

#define BITS 8

typedef unsigned int uint;

void print_bits(uint x) {
	for (int i = sizeof(x) * BITS - 1; i >= 0; i--) {
		printf("%d", (x >> i) & 1);
	}
	printf("\n");
}

int invert(uint x, uint p, uint n) {
	if (p + n > sizeof(x) * BITS) {
		return 0;
	}

	for (int i = 0; i < n; i++) {
		uint mask = 1u << n;
	}
}