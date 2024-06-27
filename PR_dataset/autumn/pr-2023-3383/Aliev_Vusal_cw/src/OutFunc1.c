#include "Common.h"
#include "OutFunc1.h"

void OutFunc1(CountWord* result, int* res) {
	int total_world = *res;
	for (int i = 0; i < total_world; i++) {
		printf("%s: %d\n", result[i].word, result[i].count);
	}
}