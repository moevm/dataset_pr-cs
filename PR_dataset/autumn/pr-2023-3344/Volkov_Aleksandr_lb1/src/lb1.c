#include <stdio.h>

#define maximum_size 20

int index_first_negative(int numbers[], int size){
	int index;
	for(int i = 0; i < size; i++){
		if(numbers[i] < 0){
			index = i;
			break;
		}
	}
	return index;
}

int index_last_negative(int numbers[], int size){
	int index;
	for(int i = 0; i < size; i++){
		if(numbers[i] < 0){
			index = i;
		}
	}
	return index;
}

int multi_between_negative(int numbers[], int size){
	int index_first = index_first_negative(numbers, size);
	int index_last = index_last_negative(numbers, size);
	int multiplication = 1;
	for(int i = index_first; i < index_last; i++){
		multiplication *= numbers[i]; 
	}
	return multiplication;
}

int multi_before_and_after_negative(int numbers[], int size){
	int index_first = index_first_negative(numbers, size);
	int index_last = index_last_negative(numbers, size);
	int multiplication = 1;
	for(int i = 0; i < index_first; i++){
		multiplication *= numbers[i];
	}
	for(int i = index_last; i<size; i++){
		multiplication *= numbers[i];
	}
	return multiplication;
}

// Блок заполнения массива и переменной, которая отвечает за вызов нужной функции
void main(){
	int numbers[maximum_size];
	int action;
	char new_line;
	int size = 0;
	scanf("%d", &action);
	while(size < maximum_size){
		scanf("%d", &numbers[size]);
		size += 1;
		new_line = getchar();
		if(new_line == '\n'){
			break;
		}
	}
	// Блок выбора нужной функции		
	switch(action){
		case 0:
			printf("%d\n", index_first_negative(numbers, size));
			break;
		case 1:
			printf("%d\n", index_last_negative(numbers, size));
			break;
		case 2:
			printf("%d\n", multi_between_negative(numbers, size));
			break;
		case 3:
			printf("%d\n", multi_before_and_after_negative(numbers, size));
			break;
		default:
			printf("Данные некорректны\n");
	}
}