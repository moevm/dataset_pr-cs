#include <stdio.h>
#include <stdlib.h>
int index_first_even(int array[],int number_of_numbers);
int index_last_odd(int array[], int number_of_numbers);
int sum_between_even_odd(int array[],int number_of_numbers);
int sum_before_even_odd_and_after_odd(int array[],int number_of_numbers);

int main(){
    int function;
    scanf("%d",&function);
    int number_of_numbers=0;
    int array[100]={0};
    for (int i=0;i<100;i++){
        if(getchar()=='\n') break;
        else {
            scanf("%d",&array[i]);
            number_of_numbers++;}
    }
    switch(function){
        
        case 0: printf("%d\n",index_first_even(array,number_of_numbers));
            break;
        case 1: printf("%d\n",index_last_odd(array,number_of_numbers));
            break;
        case 2: printf("%d\n",sum_between_even_odd(array,number_of_numbers));
            break;
        case 3: printf("%d\n",sum_before_even_odd_and_after_odd(array,number_of_numbers));
            break;
        default: printf("Данные некорректны\n");
    }
    return 0;
}
int index_first_even(int array[],int number_of_numbers){
    int first_even;
    for(int i=0;i<number_of_numbers;i++){
        if(array[i]%2==0){
            first_even = i;
            break;
        }
    }
    return first_even;
}
int index_last_odd(int array[],int number_of_numbers){
    int last_odd;
    for(int i=0;i<number_of_numbers;i++){
        if(array[i]%2!=0) last_odd=i;
    }
    return last_odd;
}
int sum_between_even_odd(int array[],int number_of_numbers){
    int first_even=index_first_even(array,number_of_numbers),last_odd=index_last_odd(array,number_of_numbers);
    int summ=0;
    for(int i=first_even;i<last_odd;i++){
        summ=summ+abs(array[i]);
    }
    return summ;
}
int sum_before_even_odd_and_after_odd(int array[],int number_of_numbers){
    int first_even=index_first_even(array,number_of_numbers),last_odd=index_last_odd(array,number_of_numbers);
    int summ=0;
    for(int i=0;i<first_even;i++){
        summ=summ+abs(array[i]);
    }
    for(int i=last_odd;i<number_of_numbers;i++){
        summ=summ+abs(array[i]);
    }
    return summ;
}

