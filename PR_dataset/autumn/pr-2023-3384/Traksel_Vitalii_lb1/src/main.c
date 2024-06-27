#include <stdio.h>
#include <stdlib.h>

// максимальное по модулю
int abs_max (int input_array[],int input_size){
int max = input_array[0];
for (int count = 1; count<input_size; count++){
if (abs(max) < abs(input_array[count])) max = input_array[count]; 
}
return(max);
}

// минимальное по модулю
int abs_min (int input_array[],int input_size){
int min = input_array[0];
for (int count = 1; count<input_size; count++){
if (abs(min) > abs(input_array[count])) min = input_array[count]; 
}
return (min);
}

// разница максимального по модулю и минимального по модулю
int diff(int input_array[],int input_size){
int delta = abs_max(input_array, input_size) - abs_min(input_array, input_size);
return delta;
}

// сумма элементов после максимального по модулю, включая его самого
int sum(int input_array[],int input_size){
int number_max;
int max = abs_max(input_array,input_size);
int total_sum = max;
for (int count = 0; count<input_size; count++){
	if (input_array[count] == max) {
	number_max = count;
	break;
	}
}
for (int count = 0; count<input_size; count++){
	if (count > number_max) {
	total_sum = total_sum + input_array[count];
	}
}
return total_sum;
}

int main(){
int key, array[100], size = 0;
char stop;

//ввод значения key
scanf("%d", &key);

// ввод массива
for (int count = 0; count<100; count++){
	scanf ("%d%c", &array[count],&stop);
	size++;
	if (stop == '\n') break;
}

// переобозначение массива
int new_array[size];
for (int count = 0; count<size; count++){
 new_array[count] = array[count];
}

// функция в зависимости от значения key
switch (key){
	case 0: 
		printf("%d\n", abs_max(new_array, size));
		break;
	case 1:
		printf("%d\n", abs_min(new_array,size));
		break;
	case 2:
		printf("%d\n", diff(new_array, size));
		break;
	case 3:
		printf("%d\n", sum(new_array, size));
		break;
	default: 
		printf("Данные некорректны\n");
		break;
	
}
return 0;
}
