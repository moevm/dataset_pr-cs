#include "input.h"
#include "output.h"
#define MAXSIZE 100
int main(){
	int arr[MAXSIZE];
	int task, size = 0;
	scanf("%d", &task);
	size = input(arr);
	output(arr, size, task);
	return 0;
}
