#include <stdio.h>		


int A[100] = {};
int arr_len = 0;


int choose_option(){
	int option_num;
	scanf("%d", &option_num);
	return option_num;
}



int* arr_input(){
	int num;
	while (1) { 
       	  if (scanf("%d", &num) == 1) { 
       	  }
	  else {
        	break; 
       	  }
	  A[arr_len] = num;
      	  arr_len += 1;
    	}
    return A;
}



int max(int arr[]){
	int max_num = arr[0];
	for(int z = 1; z < arr_len; z++){
		if(arr[z] > max_num){
			max_num = arr[z];
		}
	}
	return max_num;
	}


int min(int arr[]){
	int min_num = arr[0];
	for(int j = 1; j < arr_len; j++){
		if(arr[j] < min_num){
			min_num = arr[j];
		}
	}
	return min_num;
	}

int diff(int arr[]){
	int difference = (max(arr) - min(arr));
	return difference;
}

int sum(int arr[]){
	int s = 0;
	for(int a = 0; a < arr_len; a++){
		if(arr[a] != min(arr)){
			s += arr[a];
		}
		else return s;

	}	




}

int main(){
        switch(choose_option()){
         case 0: printf("%d\n", max(arr_input())); break;
         case 1: printf("%d\n", min(arr_input())); break;
         case 2: printf("%d\n", diff(arr_input())); break;
         case 3: printf("%d\n", sum(arr_input())); break;
         default: printf("Данные некорректны"); return 0;
        }

        }
 