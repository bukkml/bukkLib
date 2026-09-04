#include <stdio.h>

#define BITS 8

typedef unsigned int uint;

void print_bits(uint x) {
	for (int i = sizeof(x) * BITS - 1; i >= 0; i--) {
		printf("%d", (x >> i) & 1);
	}
	printf("\n");
}

int main() {
	print_bits(5);
	return 0;
}
