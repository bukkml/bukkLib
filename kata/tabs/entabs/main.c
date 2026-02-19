#include <stdio.h>

#define SPACES_TO_TAB 4

int main() {
	int c, space_count = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			space_count++;
			if (space_count == SPACES_TO_TAB) {
				putchar('\t');
				space_count = 0;
			}
		}
		else {
			while (space_count > 0) {
				putchar(' ');
				space_count--;
			}
			putchar(c);
		}
	}
	while (space_count > 0) {
		putchar(' ');
		space_count--;
	}
}