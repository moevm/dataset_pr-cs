# include <stdio.h>
int   get_max(int arr[],int size){
    int max =arr[0];
    for ( int i = 1;i<size;i++){
        if (arr[i]>max){
            max = arr[i];
        }
    }
    return max;
}
int get_min(int arr[],int size){
    int min =arr[0];
    for (int i = 1;i<size;i++){
        if (arr[i]<min){
            min = arr[i];
        }
    }
    return min;
}
int get_diff(int arr[],int size){
    int max = get_max(arr,size);
    int min = get_min(arr,size);
    int diff = max-min;
    return diff;
}
int get_sum(int arr[],int size){
    int sum =0;
    int min = get_min(arr,size);
    for (int i = 0;i<size;i++){
        if (arr[i]==min){
        break;
        }
        sum = sum + arr[i];
    }
    return sum;
}
void input_result(int number, int result) {
  switch (number) {
      case 0:
          printf("%d\n", result);
            break;
       case 1:
           printf("%d\n", result);
           break;
      case 2:
           printf("%d\n", result);
           break;
       case 3:
           printf("%d\n", result);
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}
int main(){
     int number;
    scanf("%d\n", &number);

    int arr[100];
    int size= 0;
    int input_elements;
    while (scanf("%d", &input_elements) == 1) {
        arr[size] = input_elements;
        size++;
    }
    int result;
        switch(number){
            case 0:
            result= get_max(arr,size);
            input_result(number,result);
            break;
            case 1:
            result= get_min(arr,size);
            input_result(number,result);
            break;
            case 2:
            result= get_diff(arr,size);
            input_result(number,result);
            break;
            case 3:
            result= get_sum(arr,size);
            input_result(number,result);
            break;
            default:
            input_result(number,0);
            
        }
    return 0;
}
