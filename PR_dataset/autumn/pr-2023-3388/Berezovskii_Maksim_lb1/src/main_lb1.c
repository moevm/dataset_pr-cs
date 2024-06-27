#include <stdio.h>
#include <stdlib.h> 
#include <limits.h> 

int abs_max(int array[], int len){ 
    int max_abs = 0;
    int index_max = 0;
    for (int i = 1; i < len; i++){
        if ( abs(array[i]) > abs(max_abs) ){
            max_abs = array[i];
            index_max = i;
        }
    }
    return index_max;
}

int abs_min(int array[], int len){
    int min_abs = INT_MAX;
    int index_min = 0;
    for (int i = 1; i < len; i++){
        if (( abs(array[i]) < abs(min_abs))){
            min_abs = array[i];
            index_min = i;
        }
    }
    return index_min;
}

int diff (int array[], int index_max, int index_min){
    return array[index_max] - array[index_min];
}

int sum(int array[], int len, int index_max){
    int total = 0;
    for (int i = index_max; i < len; i++){
        total += array[i];
    }
    return total;
}


int main(){

    int array[100];
    int i = 0;

    while (scanf("%d", &array[i]) == 1){
        i++;
    }   

    int len = i;
    
    int index_max = abs_max(array, len);
    int index_min = abs_min(array, len);

    switch (array[0])
    {
    case 0:
        printf("%d\n", array[index_max]);
        break;
    case 1:                            
        printf("%d\n", array[index_min]);
        break;
    case 2:
        printf("%d\n", diff(array, index_max, index_min));
        break;
    case 3:
        printf("%d\n", sum(array, len, index_max));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
    
    return 0;
}