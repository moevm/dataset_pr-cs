#include <stdio.h>

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

#define N 20

int main() {
	int number = -1;
    	char symbol;
    	int masive[N];
    	int countElements = 0; // счетчик элементов в массиве
    
    	while (symbol != '\n') {
        	if (number != -1)
            		scanf("%d%c", &masive[countElements], &symbol);
        	else
            		scanf("%d%c%d%c", &number, &symbol, &masive[countElements], &symbol);
        	countElements++;
    	}
    
    	switch (number) {
        	case 0 :
        		printf("%d\n", index_first_negative(masive, countElements)); // индекс первого отрицательного
            		break;
        	case 1:
            		printf("%d\n", index_last_negative(masive, countElements)); // индекс последнего отрицательного
            		break;
        	case 2:
            		printf("%d\n", multi_between_negative(masive, index_first_negative(masive, countElements), index_last_negative(masive, countElements))); // произведение между отрицательными
            		break;
        	case 3:
            		printf("%d\n", multi_before_and_after_negative(masive, index_first_negative(masive, countElements), index_last_negative(masive,countElements), countElements)); // произведение вне крайних элементов
            		break;
        	default:
            		puts("Данные некорректны\n");
    	}

}
