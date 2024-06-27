#include <stdio.h>
#include <stdlib.h>

int index_first_even (int array []) {
    for (int i = 0; i < 100; i++) {
        if (abs(array[i]) % 2 == 0) {
                return i;
                break;
        }
    }
}

int index_last_odd (int array []) {
    for (int i = 99; i >= 0; i--) {
        if (abs(array[i]) % 2 == 1) {
                return i;
                break;
        }
    }
}

int sum_between_even_odd (int array []) {
    int first_even = index_first_even(array);
    int last_odd = index_last_odd(array);
    int sum = 0;

    for (int i = first_even; i < last_odd; i++){
        sum += abs(array[i]);
    }

    return sum;
}

int sum_before_even_and_after_odd(int array []) {
    int first_even = index_first_even(array);
    int last_odd = index_last_odd(array);
    int sum = 0;

    for (int i = 0; i < first_even; i++) {
            sum += abs(array[i]);
    }

    for (int i = last_odd; i < 100; i++) {
        sum += abs(array[i]);
    }

    return sum;
}

int main() {
    int n;
    int array[100];
    int length = 0;

    scanf("%d", &n);
    for (int i = 0; i < 100; i++) {
        array[i] = 0;
    }
        
    while(getchar() != '\n' && length < 100) {
        scanf("%d", &array[length]);
        length++;
    }

    switch(n){
            case 0:
                printf("%d\n", index_first_even(array));
                break;
            case 1:
                printf("%d\n", index_last_odd(array));
                break;
            case 2:
                printf("%d\n", sum_between_even_odd(array));
                break;
            case 3:
                printf("%d\n", sum_before_even_and_after_odd(array));
                break;
            default:
                printf("Данные некорректны\n");
    }
    
    return 0;
}


