#include <stdio.h>
int index_first_negative(int arr[], int n) {
    int ind= -1;
    for (int i = 0; i<n; ++i) {
        if (arr[i]<0) {
            ind=i;
            break;
        }
    }
    return ind;
}

int index_last_negative(int arr[], int n) {
    int ind=-1;
    for (int i=0; i<n; ++i) {
        if (arr[i]<0) {
            ind=i;
            
        }
    }
    return ind;
}

void multi_between_negative(int arr[], int n) {
    int first = index_first_negative(arr,n);
    int last = index_last_negative(arr,n);
    long long int multi = 1;
    for (int i = first; i < last; ++i) {
        multi *=arr[i];
    }
    printf("%lld\n", multi);
    return;
}

void multi_before_and_after_negative(int arr[], int n) {
    int first = index_first_negative(arr, n);
    int last = index_last_negative(arr, n);
    long long int multi = 1;
    for (int i = 0; i < first; ++i) {
        multi *= arr[i];
    }
    for (int i = last; i < n; ++i) {
        multi *= arr[i];
    }
    printf("%lld\n", multi);
    return;
}

int main () {
    int n = 0;
    int N =20;
    int arr[N];
    char c;
    int choice;
    scanf("%d%c", &choice, &c);
    do {
        scanf("%d%c",&arr[n], &c);
        n++;
    }while (c!= '\n' &&n < N);
    int answer;
    switch (choice) {
    case 0:
        answer = index_first_negative(arr,n);
        printf("%d\n", answer);
        return 0;
        break;
    case 1:
        answer = index_last_negative(arr,n);
        printf("%d\n", answer);
        return 0;
        break;
    case 2:
        multi_between_negative(arr, n);
        return 0;
        break;
    case 3:
        multi_before_and_after_negative(arr,n);
        return 0;
        break;
    
    default:
        printf("Данные некорректны\n");
        return 0; 
    }
}
