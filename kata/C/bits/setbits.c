#include <stdio.h>

#define BITS 8

typedef unsigned int uint;

// a b  &   |   ^
// 0 0  0	0	0
// 0 1	0	1	1
// 1 0	0	1	1
// 1 1	1	1	0

void print_bits(uint x) {
	for (int i = sizeof(x) * BITS - 1; i >= 0; i--) {
		printf("%d", (x >> i) & 1);
	}
	printf("\n");
}

uint setbits(uint x, uint p, uint n, uint y) {
	if (p + n > sizeof(x) * BITS) {
		return 0;
	}
	
	uint mask = (1u << n) - 1;

	return (x & ~(mask << (p + 1 - n))) | ((y & mask) << (p + 1 - n));
}

uint invert(uint x, uint p, uint n) {
	if (p + n > sizeof(x) * BTIS) {
		return 0;
	}

	uint mask = (1u << n) - 1;

	return x ^ (mask << (p + 1 - n));
}

uint rightrot(uint x, uint n) {
	n %= sizeof(x) * BITS;

	if (n == 0)
		return x;

	uint mask = (1u << n) - 1;
	mask = mask & x;

	return (x >> n) | (mask << (sizeof(x) * BITS) - n);
}

