#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "my_lib.h"
#include "input.h"
#include "same_year_and_month.h"
#include "sort_min.h"
#include "del_19age.h"
#include "min_max.h"
#include "certificate.h"
#include "put.h"



int main(){
    printf("Course work for option 4.8, created by Artemii Kantserov.\n");
    int num_function = 0;
    int repeat = 0;
    if (scanf("%d", &num_function) == 0){
        printf("Error: сначала введите номер функции.");
        exit(1);
    }
    if (num_function==5) {
        certificate();
        return 0;
    }
    if (num_function==9){
        scanf("%d", &repeat);
    }
    struct text* text = put();
    if (text==0) {
        return 0;
    }
    if (num_function==9){
        input_9(text, repeat);
        free_memory_in(text);
        return 0;
    }
    if (num_function == 0) {
            input(text);
            free_memory_in(text);
            return 0;
    }
    processing_text(text);

    switch (num_function) {
        case 1:
            same_year_and_month(text);
            break;
        case 2:
            sort_min(text);
            break;
        case 3:
            del_19age(text);
            break;
        case 4:
            min_max(text);
            break;
        default:
            printf("Error: такого номера функции не существует.\n");
            return 0;
    }
    input(text);
    free_memory(text);
    return 0;
}
