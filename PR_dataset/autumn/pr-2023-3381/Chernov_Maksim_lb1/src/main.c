#include <stdio.h>
#define N 20

int index_first_negative(int arr[], int cnt);              
int index_last_negative(int arr[], int cnt);               
int multi_between_negative(int arr[], int cnt);            
int multi_before_and_after_negative(int arr[], int cnt);   

int main(){
        char str;               
        int arr[N];           
        int num;               
        int cnt;            
        scanf("%d", &num);
        for(int i = 0; i < N; i++){
                scanf("%d%c", &arr[i], &str);
                if(i == N || str == '\n'){
                        cnt = i + 1;
                        break;
                }
        }       

        switch(num){
                case(0):
                        printf("%d\n", index_first_negative(arr, cnt));
                        break;
                case(1):
                        printf("%d\n", index_last_negative(arr, cnt));
                        break;
                case(2):
                        printf("%d\n", multi_between_negative(arr, cnt));
                        break;
                case(3):
                        printf("%d\n", multi_before_and_after_negative(arr, cnt));
                        break;
                default:
                        printf("Данные некорректны\n");
        }
        return 0;
}

int index_first_negative(int arr[], int cnt){
    for(int i = 0; i < cnt; i++){
            if(arr[i] < 0){
                    return i;
            }
    }
}

int index_last_negative(int arr[], int cnt){
    for(int i = cnt - 1; i >= 0; i--){
            if(arr[i] < 0){
                    return i;
            }
    }
}

int multi_between_negative(int arr[], int cnt){
        int first = index_first_negative(arr, cnt);
        int last = index_last_negative(arr, cnt);
        int pr = 1;
        while(first < last){
                pr = pr * arr[first];
                first++;
        }
        return pr;
}

int multi_before_and_after_negative(int arr[], int cnt){
        int first = index_first_negative(arr, cnt);
        int last = index_last_negative(arr, cnt);
        int pr = 1;
        for(int i = 0; i < first; i++){
                pr = pr * arr[i];
        }
        while(last < cnt){
                pr = pr * arr[last];
                last++;
        }
        return pr;
}