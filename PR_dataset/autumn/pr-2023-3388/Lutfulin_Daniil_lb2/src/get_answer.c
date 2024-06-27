#include <stdio.h>
#ifndef PRINTD
#define PRINTD "%d\n"
#endif

#ifndef ERROR
#define ERROR "Данные некорректны\n"
#endif

void get_answer(int ans){
       if (ans == -1){
		printf(ERROR);
       }else{
		printf(PRINTD, ans);
       }
}
