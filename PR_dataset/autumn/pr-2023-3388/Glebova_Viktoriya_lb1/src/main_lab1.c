#include <stdio.h> 
#define n 21 
int index_first_negative(int array[], int count); 
int index_last_negative(int array[], int count); 
int multi_between_negative(int array[], int count); 
int multi_before_and_after_negative(int array[], int count); 

const char* format = "%d\n";

int index_first_negative(int array[], int i) { 
    int index = 0; 
    for (int x = 1; x < i; x++){
        if(array[x] < 0){ 
            return index; 
            break; 
        } 
        index++; 
    } 
    return -1; 
} 

int index_last_negative(int array[], int i){
    int index = i - 2;
    for (int x = i - 1; x >= 1; x--){
        if(array[x] < 0){
            return index;
            break;
        }
    index--;
        
    }
    return -1;
}

int multi_between_negative(int array[], int i){
    int first_negative = index_first_negative(array, i);
    int last_negative = index_last_negative(array, i);
    int multi_result = 1;
    for (int x = first_negative + 1; x < last_negative + 1; x ++)
    {
        multi_result = multi_result * array[x];
        
    }
    return multi_result;
}

int multi_before_and_after_negative(int array[], int count){
    int first_negative = index_first_negative(array, count);
    int last_negative = index_last_negative(array, count);
    int multi_result = 1;
    for (int x = 1; x < first_negative + 1; x++){
        multi_result = multi_result * array[x];
        
    }
    for (int x = last_negative + 1; x < count; x++){
        multi_result = multi_result * array[x];
        
    }
    return multi_result;
}

int main(){
    int i = 0;
    int arr[n];
    int count;

 do{
    if (i < n){
         scanf("%d", &arr[i++]);
         
    }
 }while(getchar() != '\n');
 int meaning = arr[0];
 switch(meaning){
  case 0:
   printf("%d\n", index_first_negative(arr, i));
   break;
  case 1:
   printf("%d\n", index_last_negative(arr, i));
   break;
  case 2:
   printf("%d\n", multi_between_negative(arr, i));
   break;
  case 3:
   printf("%d\n", multi_before_and_after_negative(arr, i));
   break;
  default:
   printf("Данные некорректны\n");
 }
 return 0;
}
