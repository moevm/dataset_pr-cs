#include <stdio.h>
#define N 100

int max_element_in_array(int array[], int index){
    int arrayMax = array[0];
    for (int i = 1; i < index; i++){
        if (array[i] > arrayMax){
            arrayMax = array[i];
        }
    }
    return arrayMax;
}

int min_element_in_array(int array[], int index){
    int arrayMin = array[0];
    for (int i = 1; i < index; i++){
        if (array[i] < arrayMin){
            arrayMin = array[i];
        }
    }
    return arrayMin;
}

int diff_max_and_min_in_array(int array[], int index){
    int diffMaxMin = max_element_in_array(array, index) - min_element_in_array(array, index);
    return diffMaxMin;
}

int sum_to_min_in_array(int array[], int index){
    int sumToMin = 0;
    int minInArray = min_element_in_array(array, index);
    int indexCounter = 0;
    while (array[indexCounter] != minInArray){
        sumToMin += array[indexCounter];
        indexCounter++;
    }
    return sumToMin;
}

int main(){
    int operationValue;
    int array[N];
    int elementIndex = 0;
    scanf("%d", &operationValue);
    while (elementIndex < N) {
        scanf("%d", &array[elementIndex]);
        elementIndex++;
        if (getchar() == '\n') {
            break;
        }
    }
    switch (operationValue){
        case 0:
            printf("%d\n", max_element_in_array(array, elementIndex));
            break;
        case 1:
            printf("%d\n", min_element_in_array(array, elementIndex));
            break;
        case 2:
            printf("%d\n", diff_max_and_min_in_array(array, elementIndex));
            break;
        case 3:
            printf("%d\n", sum_to_min_in_array(array, elementIndex));
            break;
        default:
            printf("Данные некорректны\n");
    };
    return 0;
}

