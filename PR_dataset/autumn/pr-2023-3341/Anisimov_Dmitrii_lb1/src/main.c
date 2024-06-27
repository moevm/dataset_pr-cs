#include <stdio.h>

int index_first_negative(int *x,int n){
    int i = 0;
    int index_1;
    while(x[i] >= 0){
    i++;
    }
    index_1=i;
    return index_1;
}
int index_last_negative(int *x,int n){
    int index_2;
    int i;
    for (i=0;i<n;i++){
        if (x[i]<0){
        index_2=i;
        }
    }
    return index_2;
}
int multi_between_negative(int *x,int n,int index_1,int index_2){
    int index_3;
    int multiplication=1;
    for (index_3=index_1;index_3<index_2;index_3++){
        multiplication=multiplication*x[index_3];
    }
    return multiplication;
}
int multi_before_and_after_negative(int *x,int n,int index_1,int index_2){
    int index_4;
    index_4=index_1;
    int s=0;
    int index_5;
    int l=1;
    for (s=0;s<index_4;s++){
        l=l*x[s];
    }
    for (index_5=index_2;index_5<n;index_5++){
        l=l*x[index_5];
    }
    return l;
}
int main()
{
    int b;
    scanf("%d",&b);
    char g;
    int a[20];
    int j;
    do
    {
        scanf("%d%c",&a[j],&g);
        j++;
    }
    while(g!='\n');
    int c,d,v,y;
    c=index_first_negative(a,j);
    d=index_last_negative(a,j);
    v=multi_between_negative(a,j,c,d);
    y=multi_before_and_after_negative(a,j,c,d);
    switch(b){
        case 0:
            printf("%d",c);
            break;
        case 1:
            printf("%d",d);
            break;
        case 2:
            printf("%d",v);
            break;
        case 3:
            printf("%d",y);
            break;
        default:
            printf("Данные некорректны");
    }
    return 0;
}
