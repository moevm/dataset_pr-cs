#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
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
        case 3: printf("%d\n",sum_before_even_and_after_odd(array,number_of_numbers));
            break;
        default: printf("Данные некорректны\n");
    }
    return 0;
}
