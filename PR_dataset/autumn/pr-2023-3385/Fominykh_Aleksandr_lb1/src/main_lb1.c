#include <stdio.h>
int index_first_negative(int size,int* arr){
    for (int j = 0; j < size;j++){
        if (arr[j] < 0){
            return j;
        }
    }
}
int index_last_negative(int size,int *arr){
    for (int k = size-1;k >= 0;k--){
        if (arr[k] < 0){
            return k;
        }
    }
}
int from_index_first_negative(int size,int* arr){
    int j = index_first_negative(size,arr),pr = 1;
    int k = index_last_negative(size,arr);
    for (int i = j;i < k;i++){
        pr = pr * arr[i];
    }
    return pr;

}
int to_index_first_negative(int size,int* arr){
    int j = index_first_negative(size,arr),pr = 1;
    int k = index_last_negative(size,arr);
    for (int i = 0;i < j;i++){
        pr = arr[i] * pr;
    }
    for (int i = size - 1;i >= k;i--){
        pr = arr[i] * pr;
    }
    return pr;
}
int main() {
    int a, b[20], d = 0;
    scanf("%d", &a);
    for (int i = 0; i < 20; i++) {
        char c;
        scanf("%d%c", &b[i], &c);
        d++;
        if (c == '\n') {
            break;
        }
    }
    switch (a) {
        case 0:
            printf("%d", index_first_negative(d,b));
            break;
        case 1:
            printf("%d", index_last_negative(d,b));
            break;
        case 2:
            printf("%d", from_index_first_negative(d,b));
            break;
        case 3:
            printf("%d", to_index_first_negative(d,b));
            break;
        default:
            printf("Данные некорректны");
    }

return 0;}
