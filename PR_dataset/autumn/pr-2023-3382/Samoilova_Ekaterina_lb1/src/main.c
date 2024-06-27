#include <stdio.h>
int index_first_negative(int arr[], int N){
        int index;
        for (index=0; index<N; index++)
            if (arr[index]<0){
            return index;
            break;
            };
        return 0;
        };
int index_last_negative(int arr[], int N){
        int index;
        for (index=N-1; index>0; index--)
            if (arr[index]<0){
            return index;
            break;
            };
        return 0;
        };
int multi_between_negative(int arr[], int N){
        int ifn=index_first_negative(arr,N);
        int iln=index_last_negative(arr, N);
        int res=1;
        for (ifn; ifn<iln ;ifn++){
            res=res*arr[ifn];};
        return res;
    return 0;
    };
int multi_before_and_after_negative(int arr[], int N){
        int index=0;
        int ifn=index_first_negative(arr,N);
        int iln=index_last_negative(arr, N);
        int res_before=1;
        int res_after=1;
        for (index; index<ifn;index++){
            res_before = res_before *arr[index];};
        for (iln; iln<N; iln++){
            res_after = res_after *arr[iln];
        }
        return  res_before * res_after;
        
    return 0;
    };


      int main()
    { int arr[20];
    int N = 0;
    int numb = 0;
    scanf ("%d", &numb);
    char c;
    while (c!='\n'){
    scanf("%d%c", &arr[N], &c);
    N++;
}
        
    
    switch(numb){
    case 0:
    printf("%d\n",index_first_negative(arr, N));
    break;
    case 1:
    printf("%d\n",index_last_negative(arr,  N));
    break;
    case 2:
    printf("%d\n",multi_between_negative(arr,  N));
    break;
    case 3:
    printf("%d\n",multi_before_and_after_negative(arr,  N));
    break;
    default:
    printf("Данные некорректны");
    };

    return 0;
}

