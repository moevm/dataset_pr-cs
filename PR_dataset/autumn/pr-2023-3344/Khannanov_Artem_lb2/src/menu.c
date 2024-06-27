#include <stdio.h>
#include <stdlib.h>

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

int main()
{
    short int control_number;
    int support_array[100];
    int scan_count = 0;

    scanf("%hd", &control_number);
    while (getchar() != '\n') scanf("%d", &support_array[scan_count++]);
    
    int num_array[scan_count];
    for (int i = 0; i < scan_count; i++) num_array[i] = support_array[i];
    

    switch (control_number) {
        case 0:
            printf("%d\n", index_first_negative(num_array, scan_count));
            break;
        case 1:
            printf("%d\n", index_last_negative(num_array, scan_count));
            break;
        case 2:
            printf("%d\n", sum_between_negative(num_array, scan_count));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_negative(num_array, scan_count));
            break;
        default:
            printf("Данные некорректны\n");
    }

    return 0;
}
