#include <stdio.h>
#include <stdlib.h>

#include "index_last_negative.h"
#include "index_first_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"


int main(){
int i;
scanf("%d",&i);
int s[20];
int len = 0;
while (len <= 20 && scanf("%d", &s[len])==1)
{
len++;
    if (getchar() == '\n') {
        break;
}
}
switch(i){
case 0:

printf("%d\n",index_first_negative(s,len));


break;
case 1:

printf("%d\n",index_last_negative(s,len));

break;
case 2:

printf("%d\n",multi_between_negative(s,len));

break;
case 3:

printf("%d\n",multi_before_and_after_negative(s,len));

break;

default:
printf("Данные некорректны\n");
break;
}
}