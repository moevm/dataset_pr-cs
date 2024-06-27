#include <stdio.h>
#include <stdlib.h>
#define N 100



int max(int arr[N]){
    int ma=0;
    for (int i=0;i<N;i++){
        if (arr[i]>ma){
            ma = arr[i];
        }
    }
    return ma;
}

int min(int arr[N], int chm){
    int m=999;
    for (int i=0;i<chm;i++){
        if (arr[i]<m){
            m=arr[i];
        }
    }
    return m;
}

int diff (int arr[N],int chm){
    int di=0;
    int ma,m;
    ma=max(arr);
    m=min(arr,chm);
    di=ma-m;
    return di;
}

int summ (int arr[N], int chm){
    int su=0;
    int m;
    int i =0;
    m=min(arr,chm);
    while(arr[i]!=m){
        su=su+arr[i];
        i=i+1;
    }
    return su;
}


int main(){
    int chek,otv,chm,arr[N];
    scanf ("%d",&chek);
    chm=0;
    if (chek>3 || chek<0){
        printf("Данные некорректны\n");
        exit(0);
    }
    for (int i=0;i<N;i++){
        arr[i]=0;
    }
    for (int g = 0;g< N;g++) {
        scanf("%d", &arr[g]);
        chm++;
        if (arr[g]>100){
            printf("Данные некорректны\n");
            exit(0);
        }
        if (getchar()=='\n'){
            break;
        }
    }
    if (chek==0){
        otv =max(arr);
        printf("%d\n",otv);
    }
    if (chek==1){
        otv = min(arr,chm);
        printf("%d\n",otv);
    }
    if (chek==2){
        otv =diff(arr,chm);
        printf("%d\n",otv);
    }
    if (chek==3){
        otv =summ(arr,chm);
        printf("%d\n",otv);
    }
    
    return 0;
}
