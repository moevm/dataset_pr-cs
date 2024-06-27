#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int numbers[], int size){
    int first_negative = 0;

    for(int i = 0; i < size; i++){

        if(numbers[i]<0){
            first_negative = i;
            i = size;
        }
    }

    return first_negative;
}

int index_last_negative(int numbers[], int size){
    int last_negative = 0;

    for(int i = 0;i < size; i++){

        if(numbers[i]<0){
            last_negative = i;
        }
    }

    return last_negative;
}

int sum_between_negative(int numbers[], int size){
    int sum_between=0;
    int first_negative=index_first_negative(numbers, size);
    int last_negative=index_last_negative(numbers, size);

    for(int i = first_negative;i < last_negative; i++){
        sum_between=sum_between+abs(numbers[i]);
    }

    return sum_between;
}
int sum_before_and_after_negative(int numbers[], int size){
    int sum_before_and_after=0;
    int first_negative=index_first_negative(numbers, size);
    int last_negative=index_last_negative(numbers, size);

    for(int i = 0;i < first_negative; i++){
        sum_before_and_after=sum_before_and_after+abs(numbers[i]);
    }

    for(int i = last_negative;i < size; i++){
        sum_before_and_after=sum_before_and_after+abs(numbers[i]);
    }

    return sum_before_and_after;
}

int main()
{
    int numbers[100];
    int znak = 0;
    int size = 0;
    int flag = 1;
    scanf("%d", &znak);
    int i  = 0;

    while(flag){
        scanf("%d",&numbers[i]);
        i++;
        size++;

        if (getchar()=='\n'){
            flag = 0;
        }

    }
    switch(znak){
        case 0:
            printf("%d\n",index_first_negative(numbers, size));
            break;

        case 1:
            printf("%d\n",index_last_negative(numbers, size));
            break;

        case 2:
            printf("%d\n",sum_between_negative(numbers, size));
            break;

        case 3:
            printf("%d\n",sum_before_and_after_negative(numbers, size));
            break;

        default:
            printf("%s\n","Данные некорректны");
            break;
    }

    return 0;
}
