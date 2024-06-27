#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define SIZE 1000 // Из условия задачи


/* Функция сравнения для qsort */
int comparator(const void* ptr_a, const void* ptr_b){
	
	const int a = *((const int*) ptr_a);
	const int b = *((const int*) ptr_b);

	if(a == b)
		return 0;
	else if(abs(a) < abs(b))
		return 1;
	
	return -1; // else abs(a) > abs(b)
}


int main(){

	/* Ввод массива */
	int arr[SIZE];
	int real_size = 0;
	for(size_t i = 0; i < SIZE; i++){
		int num;
		int rc = scanf(" %d", &num);

		if(rc == 0 || rc == EOF)
			break;

		arr[i] = num;
		real_size++;

	}


	/* Сортируем массив int-ов по невозрастанию модулей элементов, засекаем время исполнения 
	 * Расчет времени взят из [документации](https://en.cppreference.com/w/c/chrono/clock_t)
	 * */

	clock_t start, end;
	double diff_in_sec;

	start = clock();
	qsort(arr, real_size, sizeof(int), comparator);
	end = clock();

	diff_in_sec = ((double)(end - start)) / CLOCKS_PER_SEC;


	/* Вывод отсортированного массива и времени */
	for(size_t i = 0; i < real_size; i++)
		printf("%d ", arr[i]); // Элементы разделены пробелом
	putchar('\n');

	printf("Time: %f sec\n", diff_in_sec); // Формат не указан

	return 0;
}
