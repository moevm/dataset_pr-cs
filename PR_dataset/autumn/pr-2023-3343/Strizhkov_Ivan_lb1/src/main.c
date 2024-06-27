#include <stdio.h>
#include <stdlib.h>
int FindIndex(int int_numbers[], int ct, int value){
 for(int j=0; j<ct; j++ ){
 if(int_numbers[j] == value){
 return j;
 }
 }
 return -1;
}
int abs_max(int int_numbers[], int ct){
 int clear_number = 0;
 for(int i=0; i<ct; i++){
 if (abs(int_numbers[i]) > abs(clear_number)){
 clear_number = int_numbers[i];
 }
 }
 return clear_number;
}
int abs_min(int int_numbers[], int ct){
 int mnabs = 2147483647;
 for(int i=0; i<ct; i++){
 if (abs(int_numbers[i]) < abs(mnabs)){
 mnabs = int_numbers[i];
 }
 }
 return mnabs;
}
int diff(int int_numbers[], int ct){
 return (abs_max(int_numbers, ct) - abs_min(int_numbers, ct));
}
int sum(int int_numbers[], int ct){
 int max_el = abs_max(int_numbers, ct);
 int index_start_of_sum = FindIndex(int_numbers, ct, max_el);
 int summ = 0;
 for(index_start_of_sum; index_start_of_sum < ct; 
index_start_of_sum++){
 summ += int_numbers[index_start_of_sum];
 }
 return summ;
}
int main()
{
 int action;
 scanf("%d", &action);
 int int_numbers[100];
 int ct = 0;
 while (getchar() != '\n'){
 scanf("%d", &int_numbers[ct]);
 ct++;
 }
 switch (action){
 case 0:
 printf("%d\n", abs_max(int_numbers, ct));
 break;
 case 1:
 printf("%d\n", abs_min(int_numbers, ct));
 break;
 case 2:
 printf("%d\n", diff(int_numbers, ct));
 break;
 case 3:
 printf("%d\n", sum(int_numbers, ct));
 break;
 default:
 printf("Данные некорректны\n");
 break;
 }
 return 0;
}