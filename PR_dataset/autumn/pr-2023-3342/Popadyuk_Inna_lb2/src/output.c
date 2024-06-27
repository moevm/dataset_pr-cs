#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#include "output.h"
#define ANSWER "%d\n"

void output(int choice, int arr[], int size){
    switch (choice) {
        case 0:
            printf(ANSWER, index_first_negative(arr, size));
            break;
        case 1:
            printf(ANSWER, index_last_negative(arr, size));
            break;
        case 2: {
            printf(ANSWER, multi_between_negative(arr, size));
            break;
        }
        case 3: {
            printf(ANSWER, multi_before_and_after_negative(arr, size));
            break;
        }
        default:
            printf("Данные некорректны\n");
    }
}    
