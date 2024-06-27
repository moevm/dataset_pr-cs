#include "choice.h"
#include "input_key.h"
#include "input_arr.h"

#define msize 100

int main() {
	int key, size, arr[msize];
	key = input_key();
	size = input_arr(arr);
	choice(arr, size, key);
}

