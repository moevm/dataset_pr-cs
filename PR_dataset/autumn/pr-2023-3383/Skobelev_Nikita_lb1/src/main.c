//created by niks (student LETI)

#include <stdio.h>
typedef int ll;

ll max(),min();
void diff(),sum();
int main(){
        ll array[100];
        ll task;
        scanf("%d",&task);
        ll cnt=0;
        for(ll i=0;i<100;++i){
            scanf("%d",&array[i]);
            cnt++;
            if(getchar()=='\n')break;
        }
        switch(task){
            case 0:
                max(array,cnt,task);
                break;
            case 1:
                min(array,cnt,task);
                break;
            case 2:
                diff(array,cnt,task);
                break;
            case 3:
                sum(array,cnt,task);
                break;
            default:
                printf("Данные некорректны\n");
        }
        return 0;
}
ll max(ll array[], ll cnt, ll task){
    ll index_max=0;
    for(ll i=0;i<cnt;++i){
        if(array[index_max]<array[i])index_max=i;
    }
    if(task == 0){
        printf("%d\n",array[index_max]);
        return 0;
    }
    else return index_max;
}

ll min(ll array[], ll cnt, ll task){
    ll index_min=0;
    for(ll i=0;i<cnt;++i){
        if(array[index_min]>array[i])index_min=i;
    }
    if(task == 1){
        printf("%d\n",array[index_min]);
        return 0;
    }
    else return index_min;
}

void diff(ll array[], ll cnt, ll task){
    printf("%d\n", array[max(array,cnt,task)]-array[min(array,cnt,task)]);
}

void sum(ll array[], ll cnt, ll task){
    ll sum=0;
    for(ll i=0;i<min(array,cnt,task);++i)sum+=array[i];
    printf("%d\n",sum);
}
