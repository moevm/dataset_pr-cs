#include <stdio.h>


//Определения функций
//Функция нахождения максимума
int max(int arr[], int len){

	int max = -100000;
	for (int i = 0; i < len; i++){
 
	    if (max < arr[i]){
  
			max = arr[i];
		}
	}
	return max;
}

//Функция нахождения минимума
int min(int arr[], int len){
 
    int min = 100000;
    for (int i = 0; i < len; i++){

        if (min > arr[i]){
                
            min = arr[i];
        }
    }
    return min;
}

//Функция нахождения разницы между минимальным и максимальным элементами
int diff(int arr[], int len){
    
	return max(arr, len) - min(arr, len);
}

//Функция нахождения суммы
int sum(int arr[], int len){
 
	int mn = min(arr, len);
	int sum = 0;
	int i = 0;

	while (arr[i] != mn){
 
		sum += arr[i];
		i += 1;
	}
	return sum;
}


int main(){
	
	//Ввод данных, создание переменных
		
	int n;
	int arr[100];
	int length  = 0;
	char str = ' ';
	
 	scanf("%d", &n);

	while (str!='\n') {
		
		scanf("%d%c", &arr[length], &str);
		length++;
	}
	
 //Обработка введенных данных
 switch (n){
  case 0:
      printf("%d\n", max(arr, length)); 
      break;

  case 1:
      printf("%d\n", min(arr, length)); 
      break;

  case 2:
      printf("%d\n", diff(arr, length)); 
      break;

  case 3:
      printf("%d\n", sum(arr, length)); 
      break;
	//Учет ошибки при вводе
  default:
      printf("Данные некорректны\n"); 
      break;
    }
 return 0;
}
