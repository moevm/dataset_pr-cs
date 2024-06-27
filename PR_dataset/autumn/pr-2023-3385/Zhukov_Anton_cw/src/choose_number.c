#include <stdio.h>

char choose_number() {
	char choose;
	char c = ' ';
	int count = 0;
	while((c = getchar()) != '\n'){
		choose = c;
		count++;
	}
	if ((choose <= '0' && choose >= '5' && choose != '9') || count > 1){
		return -1;
	}
	return choose;
}
