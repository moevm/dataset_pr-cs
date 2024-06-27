#include <stdio.h>
#include <stdlib.h>
#define N 100


int index_first_zero(int array[], int array_size){
        for(int i = 0; i < array_size; i++){
                if(array[i] == 0){
                    return i;
                }
        }
}

int index_last_zero(int array[], int array_size){
        for(int i = array_size - 1; i >= 0; i--){
                if(array[i] == 0){
                        return i;
                }
        }
}

int sum_between(int array[], int array_size){
        int summary = 0;
        for(int i = index_first_zero(array, array_size) + 1; i < index_last_zero(array, array_size); i++){
                summary += abs(array[i]);
        }
        return summary;
}

int sum_before_and_after(int array[], int array_size){
        int summary = 0;
        for(int i = 0; i < index_first_zero(array, array_size); i++){
                summary += abs(array[i]);
        }
        for(int i = index_last_zero(array, array_size) + 1; i < array_size; i++){
                summary += abs(array[i]);
        }
        return summary;
}


int main(){
        int key, array_size;
        int array[N];
        char space = ' ';
        array_size = 0;
        scanf("%d", &key);
        while(array_size < N && space == ' '){
                scanf("%d%c", &array[array_size], &space);
                array_size++;
        }
        switch(key){
            case 0:
                    printf("%d\n", index_first_zero(array, array_size));
                    break;
            case 1:
                    printf("%d\n", index_last_zero(array, array_size));
                    break;
            case 2:
                    printf("%d\n", sum_between(array, array_size));
                    break;
            case 3:
                    printf("%d\n", sum_before_and_after(array, array_size));
                    break;
            default:
                    printf("Данные некорректны\n");
                    break;
        }
        return 0;
}
