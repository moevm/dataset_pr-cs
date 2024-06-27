#include <stdio.h>

int index_first_even(int array[], int length){
    int ans, element;
    for(int i = 0; i < length; i++){
        element = array[i];
        if((element%2) == 0){
            ans = i;
            return ans;
        }
    }
}

int index_last_odd(int array[], int length){
    int ans, element;
    for(int i = length-1; i > -1; i -= 1){
        element = array[i];
        if((element%2) != 0){
            ans = i;
            return ans;
        }
    }
}

int sum_between_even_odd(int array[], int length){
    int begin, finish, element, sum = 0;
    begin = index_first_even(array, length);
    finish = index_last_odd(array, length);
    for(int i = begin; i < finish; i++){
        element = array[i];
        if(element < 0){element = -element;}
        sum += element;
    }
    return sum;
}

int sum_before_even_and_after_odd(int array[], int length){
    int finish, begin, element, sum = 0;
    finish  = index_first_even(array, length);
    begin = index_last_odd(array, length);
    for(int i = 0; i < finish; i++){
        element = array[i];
        if(element < 0){element = -element;}
        sum += element;
    }
    for(int i = begin; i < length; i++){
        element = array[i];
        if(element < 0){element = -element;}
        sum += element;
    }
    return sum;
}


int main() {
    int subtask_number, fl = 1, length = 0;
    scanf("%d", &subtask_number);
    int array[100];
    char check;
    while(fl){
        scanf("%d%c", &array[length], &check);
        length ++;
        if(check == '\n'){fl = 0;}
    }
    if((length == 0) || (subtask_number < 0) || (subtask_number > 3)){
        printf("Данные некорректны");
        return 0;
    } else {
        int result;
        switch (subtask_number) {
            case 0:
                result = index_first_even(array, length);
                break;
            case 1:
                result = index_last_odd(array, length);
                break;
            case 2:
                result = sum_between_even_odd(array, length);
                break;
            case 3:
                result = sum_before_even_and_after_odd(array, length);
                break;
        }
        printf("%d\n", result);
        return 0;
    }
}