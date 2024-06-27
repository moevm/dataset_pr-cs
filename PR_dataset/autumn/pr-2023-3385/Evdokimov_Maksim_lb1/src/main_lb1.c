#include <stdio.h>
#include <stdlib.h>


int abs_max_i(int* m, int n) {
	int max_el = 0;
	for (int i = 1; i < n; i++) {
		if (abs(m[max_el]) < abs(m[i])) {
			max_el = i;
		}
	}
	return max_el;
}

int abs_min_i(int* m, int n) {
	int min_el = 0;
	for (int i = 1; i < n; i++) {
		if (abs(m[min_el]) > abs(m[i])) {
			min_el = i;
		}
	}
	return min_el;
}

int abs_max(int* m, int n) {
	return m[abs_max_i(m, n)];
}

int abs_min(int* m, int n) {
	return m[abs_min_i(m, n)];
}

int diff(int* m, int n) {
	return abs_max(m,n) - abs_min(m,n);
}

int sum(int* m, int n) {
	int s = 0;
	for (int i = abs_max_i(m, n); i < n; i++) {
		s += m[i];
	}
	return s;
}

int main() {
	int size, mode, num[100];
	size = 0;
	char cur_c = ' ';
	scanf("%d", &mode);

	for (int i = 0; cur_c != '\n'; i++) {
		scanf("%d%c", &num[i], &cur_c);
		size = i + 1;
	}

	switch(mode) {
		case 0:
			printf("%d", abs_max(num, size));
		break;
		case 1:
			printf("%d", abs_min(num, size));
		break;
		case 2:
			printf("%d", diff(num, size));
		break;
		case 3:
			printf("%d", sum(num, size));
		break;
		default:
			printf("Данные некорректны");
		break;
	}

	return 0;
}