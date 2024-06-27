#include <stdio.h>
int index_first_negative(int list[],int length){
    int index;
    for(int j = 0;j<length;j++){
        if(list[j]<0){
            index = j;
            break;
            
        }
    }
    return index;
}
int index_last_negative(int list[],int length){
    int index;
    for(int q = length - 1;q>-1;q--){
        if(list[q]<0){
            index = q;
            break;
    
        }
    }
    return index;
}
int multi_between_negative(int list[],int length){
    int firstneg = index_first_negative(list,length);
    int lastneg = index_last_negative(list,length);
    int proizv = 1;
    while(firstneg < lastneg){
        proizv = proizv*list[firstneg];
        firstneg += 1;
    }
    return proizv;
}
int multi_before_and_after_negative(int list[],int length){
    int firstneg = index_first_negative(list,length);
    int lastneg = index_last_negative(list,length);
    int pr = 1;
    for(int i=0;i<firstneg;i++){
        pr *= list[i];
    }
    for(int i = lastneg;i<length;i++){
        pr *= list[i];
    }
    return pr;
}
int main(){
    char space;
    int length;
    int nomer;
    scanf("%d",&nomer);
    int list[20];
    for(int i = 0;i<21;i++){
        scanf("%d%c",&list[i],&space);
        if(i == 20||space == '\n'){
            length = i+1;
            break;
        }
        }
    switch(nomer){
        case(0):
            printf("%d \n",index_first_negative(list,length));
            break;
        case(1):
            printf("%d \n",index_last_negative(list,length));
            break;
        case(2):
            printf("%d \n",multi_between_negative(list,length));
            break;
        case(3):
            printf("%d \n",multi_before_and_after_negative(list,length));
            break;
        default:
            printf("Данные некорректны\n");
        
    }
}