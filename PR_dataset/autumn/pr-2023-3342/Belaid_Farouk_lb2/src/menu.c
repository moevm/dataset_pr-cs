#include "menu.h"

int main() {
	
	char input[CHAR_ARR_SIZE];
	
	readInput(input);
	
	char *token = strtok(input, " \n");

	int choice = userChoice(input,token);
	int arr[ARR_SIZE];
	int size = convertTokenToInt(input,arr);

	answer(choice,arr,size);

	return 0;
}
