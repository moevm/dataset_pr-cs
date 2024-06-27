
#include <stdio.h>

void func1(char** text, int num_str) {
	char nums[10] = { 0 };
	for (int i = 0; i < num_str; i++) {
		for (int j = 0; text[i][j] != 0; j++) {
			if (text[i][j] >= '0' && text[i][j] <= '9') {
				nums[text[i][j] - 48] += 1;
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		if (nums[i] != 0) {
			printf("Digit %d occurs %d times.\n", i, nums[i]);
		}
	}
}
