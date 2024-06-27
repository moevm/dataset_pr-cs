#include <stdio.h>
#define N 100

void print_func(int func_value, int arr[], int index);
int get_func_value();

int main() {
    int func_value;
    int arr[N];
    int index = 0;

    func_value = get_func_value();

    while (getchar() != '\n'){
        scanf("%d", &arr[index]);
        index+=1;
    }

    print_func(func_value, arr, index);

    return 0;
}

void print_func(int func_value, int arr[], int index) {
    scanf("%d", &func_value);
}

int get_func_value() {
    int value;
    scanf("%d", &value);
    return value;
}
