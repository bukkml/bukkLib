#include <stdio.h>

int any(const char* s1, const char* s2) {
	if (s1 == NULL || s2 == NULL) {
		return -1;
	}

	for (int i = 0; s1[i] != '\0'; i++) {
		for (int j = 0; s2[j] != '\0'; j++) {
			if (s1[i] == s2[j]) {
				return i;
			}
		}
	}
	return -1;
}

int main() {
	char* s1 = "kalsdjlak jak jdlasdk jatdkj alsmjd lkaj dlkajsdlkjasldkj aklsjd";
	char* s2 = "tm";
	printf("%d\n", any(s1, s2));

	return 0;
}
