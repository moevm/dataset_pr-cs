#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int index_first_zero(int array []){
    int inx = 0;
    int k;
    for(k = 1; k < 102; k++)
        if(array[k] == 0){
            inx = k;
            break;
        }
    return inx;
}

int index_last_zero(int array []){
    int inxl = 0;
    int k;
    for(k = 102; k > 0; k--)
        if(array[k] == 0){
            inxl = k;
            break;
        }
    return inxl;
}

int sum_between(int frel,int lstel, int array []){
    int smmod = 0;
    int i = 0;
    for(i = frel + 1; i < lstel; i++)
        smmod += abs(array[i]);
    return smmod;
}

int sum_before_and_after(int frel, int lstel, int array []){
    int smmod = 0;
    int i = 0;
    int z = 101;
    int first_max_after_lstel = 0;
    if(array[100] == INT_MAX){
        while(array[z] == INT_MAX){
            first_max_after_lstel = z;
            z--;
        }
        for(i = lstel + 1; i < first_max_after_lstel; i++)
        smmod+= abs(array[i]);
    }
    else{
        for(i = lstel + 1; i < 101; i++)
        smmod+= abs(array[i]);
    }
    for(i = 1; i < frel; i++)
        smmod+= abs(array[i]);
    return smmod;
}

int main(){
    int c[101];
    int i = 0;
    int smb = 0;
    int smbeaf = 0;
    int flag = 0;
    for(i = 0; i < 102; i ++)
        c[i] = INT_MAX;
    int firstel, lastel;
    for(i = 0; i < 102; i ++)
        scanf("%d", &c[i]);
    flag = c[0];
    if(c[101] != INT_MAX){
        printf("Данные некорректны");
    }
    else{
        lastel = index_last_zero(c);
        firstel = index_first_zero(c);
        switch(flag){
            case 0:
                printf("%d\n", firstel - 1);
                break;
            case 1:
                printf("%d\n", lastel - 1);
                break;
            case 2:
                smb = sum_between(firstel, lastel, c);
                printf("%d\n", smb);
                break;
            case 3:
                smbeaf = sum_before_and_after(firstel, lastel, c);
                printf("%d\n", smbeaf);
                break;
            default:
                printf("Данные некорректны");
            }
        }

} 

