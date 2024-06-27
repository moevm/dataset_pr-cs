#include <stdio.h>
#include <stdlib.h>
 
int first_neg_index(int array[], int len_array);
int last_neg_index(int array[], int len_array);
int sum_between_neg(int array[], int len_array);
int sum_before_and_after_neg(int array[], int len_array);


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
            printf("%d\n", first_neg_index(num_array, scan_count));
            break;
        case 1:
            printf("%d\n", last_neg_index(num_array, scan_count));
            break;
        case 2:
            printf("%d\n", sum_between_neg(num_array, scan_count));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_neg(num_array, scan_count));
            break;
        default:
            printf("Данные некорректны\n");
    }

    return 0;
}


int first_neg_index(int array[], int len_array) {
    int ret_value;

    for (int i = 0; i < len_array; i++) {

        if (array[i] < 0) {
            ret_value = i;
            break;}
    }
    return ret_value;
}


int last_neg_index(int array[], int len_array) {
    int ret_value;

    for (int i = len_array - 1; i >= 0; i--) {

        if (array[i] < 0) {
            ret_value = i;
            break;}
    }
    return ret_value;
}


int sum_between_neg(int array[], int len_array) {
    int left_index = first_neg_index(array, len_array), right_index = last_neg_index(array, len_array), ret_sum = 0;

    for (int i = left_index; i < right_index; i++) ret_sum += abs(array[i]);

    return ret_sum;
}


int sum_before_and_after_neg(int array[], int len_array) {
    int sum_between = sum_between_neg(array, len_array), array_sum = 0;

    for (int i = 0; i < len_array; i++) array_sum += abs(array[i]);

    return array_sum - sum_between;
}
