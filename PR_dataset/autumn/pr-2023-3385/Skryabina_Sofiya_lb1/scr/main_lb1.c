#include <stdio.h>
#include <stdlib.h>

int index_first_even(int mas[], int len){
	for(int k = 0;; k++){
	    if ((abs(mas[k])%2) == 0){
	        return k;
	    }
    }
}

int index_last_odd(int mas[], int len){
	for(int k = len-1;; k--) {
	    if ((abs(mas[k])%2) == 1){
	        return k;
	    }
    }
}


int sum_between_even_odd(int mas[], int len){
    int first_even = index_first_even(mas, len);
    int last_odd = index_last_odd(mas, len);
    int summa = 0;
    for(int k = first_even; k<last_odd; k++){
        summa += abs(mas[k]);
    }
    return summa;
}

int sum_before_even_and_after_odd(int mas[], int len){
    int first_even = index_first_even(mas, len);
    int last_odd = index_last_odd(mas, len);
    int summa = 0;
    for(int k = 0; k<first_even; k++){
        summa += abs(mas[k]);
    }
    for(int k = last_odd; k<(len); k++){
        summa += abs(mas[k]);
    }
    return summa;
}


int main(){
    int mas[100], value, len=0;
    char stop;
    scanf("%d", &value);
    for(int i=0; i < 100; i++)
  {
        scanf("%d%c", &mas[i], &stop);
        len++;
        if (stop=='\n') break;
  }
    switch(value){
        case 0:
            printf("%d\n", index_first_even(mas, len));
            break;
        case 1:
            printf("%d\n", index_last_odd(mas, len));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(mas, len));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(mas, len));
            break;
        default:
            printf("Данные некорректны");
    }
}