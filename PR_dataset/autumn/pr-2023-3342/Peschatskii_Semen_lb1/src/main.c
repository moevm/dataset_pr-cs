#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int num_list[], int length){
    for (int i = 0; i < length; i++){
        if (num_list[i] < 0){
            return i;}}}

int index_last_negative(int num_list[], int length){
    for (int j = length - 1; j >= 0; j--){
        if (num_list[j] < 0){
            return j;}}}

int sum_between_negative(int num_list[], int length){
    int sum = 0;
    for (int i = index_first_negative(num_list, length); i < index_last_negative(num_list, length); i++){
        sum += abs(num_list[i]);}
    return sum;}

int sum_before_and_after_negative(int num_list[], int length){
    int sum_all = 0;
    for (int i = 0; i < length; i++){
        sum_all += abs(num_list[i]);
    }
    return sum_all - sum_between_negative(num_list, length);
}

int main(){
    int fun_num;
    int list[100];
    char ballast_char;
    int counter = 0;
    scanf("%d", &fun_num);
    ballast_char = getchar();
    while (ballast_char != '\n')
    {
        scanf("%d", &list[counter++]);
        ballast_char = getchar();
    }
	if (fun_num==0){printf("%d\n",index_first_negative(list,counter));}
	else if (fun_num==1){printf("%d\n",index_last_negative(list,counter));}
	else if (fun_num==2){printf("%d\n",sum_between_negative(list,counter));}
	else if (fun_num==3){printf("%d\n",sum_before_and_after_negative(list,counter));}
	else{printf("Данные некорректны");}
    return 0;
}
