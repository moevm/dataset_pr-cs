#include <stdio.h>
#include <stdlib.h>


int index_first_zero(int quantity, int arr_end[100]){
    for (int k = 0; k < quantity; ++k){
        if (arr_end[k] == 0){
            return k;
        }
    }
}

int index_last_zero(int quantity, int arr_end[100]){
    for (quantity; quantity >= 0; --quantity){
        if (arr_end[quantity] == 0){
            return quantity;
        }
    }
}

int sum_between(int quantity, int arr_end[100]){
    int sum = 0;
    int first_zero = index_first_zero(quantity, arr_end);
    int last_zero = index_last_zero(quantity - 1, arr_end);
    for (first_zero; first_zero < last_zero; ++first_zero){
        sum += abs(arr_end[first_zero]);
    }
    return sum;


}
int sum_before_and_after(int quantity, int arr_end[100]){
    int sum = 0;
    int first_zero = index_first_zero(quantity, arr_end);
    int last_zero = index_last_zero(quantity - 1, arr_end);
    for (int k = 0; k <= first_zero; ++k){
        sum += abs(arr_end[k]);
    }
    for (last_zero; last_zero < quantity; ++last_zero){
        sum += abs(arr_end[last_zero]);
    }
    return sum;
}

int main(){
    int num;
    scanf("%d", &num);
    if (num != 0 && num != 1 && num != 2 && num != 3){
        printf("Данные некорректны");
        return 0;
    }
    
    int arr_end[100];
    char str = ' ';
    int quantity = 0;
    for (quantity; (quantity < 100 && str != '\n'); ++quantity){
        scanf("%d%c", &arr_end[quantity], &str);
        }
    switch (num){
    case 0:
        printf("%d\n", index_first_zero(quantity, arr_end));
        break;
    case 1:
        printf("%d\n", index_last_zero(quantity-1, arr_end));
        break;
    case 2:
        printf("%d\n", sum_between(quantity, arr_end));
        break;
    case 3:
        printf("%d\n", sum_before_and_after(quantity, arr_end));
        break;
    }
    return 0;
}
  
