#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int arr[], int len){
    for(int i=0; i < len; i++){
        if(arr[i]==0){
            return i;
        }
    }
    return -1;
}

int index_last_zero(int arr[], int len){
    for(int i = len-1; i>=0; i--){
        if(arr[i]==0){
            return i;
        }
    }
    return -1;
}

int sum_between(int arr[], int len){
    int sum = 0;
    int first = index_first_zero(arr, len) + 1;
    int last = index_last_zero(arr, len);

    for(int i =first; i < last; i++){
        sum += abs(arr[i]);
    }
    return sum;
}

int sum_before_and_after(int arr[], int len){
    int sum = 0;
    int first = index_first_zero(arr, len);
    int last = index_last_zero(arr, len);

    for(int i=0; i <= first; i++){
        sum += abs(arr[i]);
    }
    for(int i=last; i < len; i++){
        sum += abs(arr[i]);
    }
    return sum;
}

int main(){
    int arr[100];
    int k = 0, choise, len;
    
    do{
        if(k){
            scanf("%d", &arr[k-1]);
        }else{
            scanf("%d", &choise);
        }
        k++;
    }while(getchar() !='\n');

    len = k - 1;

    switch(choise){
        case 0: 
			if (index_first_zero(arr, len) == -1){
			       	printf("Данные некорректны\n");
            }
			else{
				printf("%d\n", index_first_zero(arr, len));
			    break;
            }
		case 1:
			if (index_last_zero(arr, len) == -1){
                printf("Данные некорректны\n");
            }
            else{
                printf("%d\n", index_last_zero(arr, len));
                break;
            }
		case 2:
			printf("%d\n", sum_between(arr, len));
			break;
		case 3:
			printf("%d\n", sum_before_and_after(arr, len));
			break;
		default:
			printf("Данные некорректны\n");
    }
}

