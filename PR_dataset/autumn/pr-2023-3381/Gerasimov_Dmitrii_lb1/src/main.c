#include <stdio.h>
#include <stdlib.h>

int index_first_negative(size_t cnt, int a[]){
    for(int i = 0;i<cnt;i++){
        if(a[i]<0){
            return i;
        }
    }
    printf("Данные некорректны\n");
    return -1;
}

int index_last_negative(size_t cnt, int a[]){
    for(int i = cnt - 1;i>=0;i--){
        if(a[i]<0){
            return i;
        }
    }
    printf("Данные некорректны\n");
    return -1;
}

void sum_between_negative(size_t cnt, int a[]){
    int index_first = index_first_negative(cnt,a);
    if(index_first==-1) return;
    int index_last = index_last_negative(cnt,a);
    int sum = 0;

    for(size_t i = index_first;i<index_last;i++){
        sum += abs(a[i]);
    }
    
    printf("%d\n",sum);
    return;
}

void sum_before_and_after_negative(size_t cnt, int a[]){
    int index_first = index_first_negative(cnt,a);
    if(index_first==-1) return;
    int index_last = index_last_negative(cnt,a);
    int sum = 0;

    if(index_first==index_last){
        printf("%d\n",0);
        return;
    }

    for(size_t i = 0;i<cnt;i++){
        if(i<index_first || i>=index_last) sum+=abs(a[i]);
    }

    printf("%d\n",sum);
    return;
}

int main(){
    int n;
    scanf("%d",&n);

    int a[100];
    for(size_t j = 0;j<100;j++){
        a[j]=0;
    }

    size_t cnt = 0;
    while (getchar()!='\n' && cnt<100)
    {
        scanf("%d",&(a[cnt]));
        cnt++;
    }

    switch (n)
    {
    case 0:
        if((n=index_first_negative(cnt,a))!=-1) printf("%d\n",n);
        break;
    case 1:
        if((n=index_last_negative(cnt,a))!=-1) printf("%d\n",n);
        break;
    case 2:
        sum_between_negative(cnt,a);
        break;
    case 3:
        sum_before_and_after_negative(cnt,a);
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
    
    return 0;
}