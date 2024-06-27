#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 100;

int read_data(int *data) {
    int c;
    int i = 0;
    
    do {
        scanf("%d", &data[i]);
        ++i;
    } while ((c = getchar()) != '\n');
    
    return i;
}

int index_first_zero(const int *data, int n) {
    for (int i = 0; i < n; ++i) {
        if (data[i] == 0) {
            return i;
        }
    }
    
    return 0;
}

int index_last_zero(const int *data, int n) {
    int last_index = 100;
    for (int i = n - 1; i >= 0; --i) {
        if (data[i] == 0) {
            return i;
        }
    }
    
    return n - 1;
}

int sum_between(int *data, int first_index, int last_index) {
    int sum = 0;
    
    for (int i = first_index; i < last_index; ++i) {
        sum += abs(data[i]);
    }
    
    return sum;
}

int sum_before_and_after(int *data, int first_index, int last_index, int n) {
    int sum = 0;
    
    for (int i = 0; i < first_index; ++i) {
        sum += abs(data[i]);
    }
    
    for (int i = last_index; i < n; ++i) {
        sum += abs(data[i]);
    }
    
    return sum;
}

int main() {
    int data[MAX_N];
    int command;
    int result;
    
    scanf("%d", &command);
    int n = read_data(data);
    
    switch(command) {
        case 0:
            result = index_first_zero(data, n);
            break;
            
        case 1:
            result = index_last_zero(data, n);
            break;
        
        case 2:
            result = sum_between(data, index_first_zero(data, n), index_last_zero(data, n));
            break;
            
        case 3:
            result = sum_before_and_after(data, index_first_zero(data, n), index_last_zero(data, n), n);
            break;
            
        default:
            printf("Данные некорректны");
            return 0;
    }
    
    printf("%d\n", result);
    return 0;
}