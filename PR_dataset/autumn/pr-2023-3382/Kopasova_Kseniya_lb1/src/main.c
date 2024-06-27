#include <stdio.h>
#include <stdlib.h>
#define N 100
int abs_max(int a[], int len_a) {
	int a_max = 0, ind_amx;
	for (int i = 0; i < len_a; i++) {
		if (abs(a[i]) > a_max) {
			a_max = abs(a[i]);
			ind_amx = i;
		}
	}
	return ind_amx;
}
int abs_min(int a[], int len_a) {
	int a_min = 1000000000, ind_amn;
	for (int i = 0; i < len_a; i++) {
		if (abs(a[i]) < a_min) {
			a_min = abs(a[i]);
			ind_amn = i;
		}
	}
	return ind_amn;
}
int diff(int a[], int ind_amx, int ind_amn) {
	return (a[ind_amx] - a[ind_amn]);
}
int sum(int a[], int len_a, int ind_amx) {
	int s = 0;
	for (int i = ind_amx; i < len_a; i++) {
		s += a[i];
	}
	return s;
}

int main() {
	int ind_mx, ind_mn, f, i = 0, len_a;
	int a[N];
	char sp;
	scanf("%d%c", &f, &sp);
	do {
		scanf("%d%c", &a[i], &sp);
		i += 1;
	} while (sp != '\n');
	len_a = i;
	ind_mx = abs_max(a, len_a);
	ind_mn = abs_min(a,len_a);
	switch (f) {
	case 0:
		printf("%d\n", a[ind_mx]);
		break;
	case 1:
		printf("%d\n", a[ind_mn]);
		break;
	case 2:
		printf("%d\n", diff(a, ind_mx, ind_mn));
		break;
	case 3:
		printf("%d\n", sum(a, len_a, ind_mx));
		break;
	default:
		printf("Данные некорректны\n");
	}
	return 0;
}
