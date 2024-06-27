#include <stdio.h>
#include "writeAnswer.h"
void writeAnswer(int answer){
	if (answer == -1) printf("Данные некорректны\n");
       	else printf("%d\n", answer);	
}
