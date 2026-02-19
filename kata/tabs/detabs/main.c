#include <stdio.h>

#define SPACES_IN_TAB 4

int main() {
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			for (int i = 0; i < SPACES_IN_TAB; i++) {
				putchar(' ');
			}
		}
		else
			putchar(c);
	}
	return 0;
}