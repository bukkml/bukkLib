#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void squeeze(char s1[], const char* s2) {
	if (s1 == NULL || s2 == NULL) {
		return;
	}

	int i, j;	
	for (i = j = 0; s1[i] != '\0'; i++) {
		int k;
		for (k = 0; s2[k] != '\0'; k++) {
			if (s1[i] == s2[k]) {
				break;
			}
		}
		if (s2[k] == '\0')
			s1[j++] = s1[i];
	}

	s1[j] = '\0';
}

int main() {
	char s1[] = "Hello dear wolrd aaaaaaddddddddsssssssxxxxxxxxxffffff";
	char* s2 =  "dxe";
	squeeze(s1, s2);
	printf("%s\n", s1);
	return 0;
}
