#include <stdio.h>
int index_first_negative(int array[],int len){
    for (int i = 0; i < len; i++) {
        if (array[i] < 0){
            return i;
        }
    }
    return -1;
}


int index_last_negative(int array[], int len){
    for (int i=len-1; i>=0; i--){
        if (array[i]<0){
            return i;
        }
    }
    return -1;
}

int multi_between_negative(int array[], int len){
    int a=index_first_negative(array, len);
    int b=index_last_negative(array, len);
    int k=1;
    for (int i=a; i<b; i++){
        k*=array[i];
    }
    return k;
}


int multi_before_and_after_negative(int array[], int len ){
    int a=index_first_negative(array, len);
    int b=index_last_negative(array, len);
    int a1=1;
    int b1=1;
    for (int i=0; i<a; i++){
        a1*=array[i];
    }
    for (int i=b;i<=len-1;i++){
        b1*=array[i];
    }
    return a1*b1;
}

int main(){
    int n;
    scanf("%d",&n);
    int array[20];
    int len = 0;
    while (len <= 20 && scanf("%d", &array[len]) == 1) {
        len++;
        if (getchar() == '\n') {
            break;
        }
    }
    switch(n){
            case 0:
                if (index_first_negative(array, len)!=-1){
                    printf("%d\n",index_first_negative(array, len));
                }
                else{
                    printf("Данные некорректны\n");
                }
                break;
            case 1:
                if (index_last_negative(array, len)!=-1){
                    printf("%d\n",index_last_negative(array, len));
                }
                else{
                    printf("Данные некорректны\n");
                }
                break;
            case 2:
                if (multi_between_negative(array, len)!=-1){
                    printf("%d\n",multi_between_negative(array, len));
                }
                else{
                    printf("Данные некорректны\n");
                }
                break;
            case 3:
                if (multi_before_and_after_negative(array, len)!=-1){
                    printf("%d\n",multi_before_and_after_negative(array, len));
                }
                else{
                    printf("Данные некорректны\n");
                }
                break;
            default:
                printf("Данные некорректны\n");
                break;
    }
}