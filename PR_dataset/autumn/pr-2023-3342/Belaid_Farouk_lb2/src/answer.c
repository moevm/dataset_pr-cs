#include "answer.h"

void answer(int choice,int* arr, int size){
	char outputFormate[] = "%d\n";
	// Обработка выбора
	switch (choice) {
		case 0:
			printf(outputFormate, index_first_zero(arr, size));
			break;
		case 1:
			printf(outputFormate, index_last_zero(arr, size));
			break;
		case 2:
			printf(outputFormate, sum_between(arr,size));
			break;
		case 3:
			printf(outputFormate, sum_before_and_after(arr, size));
			break;
		default:
			printf("Данные некорректны\n");
			break;
  }
    
}
