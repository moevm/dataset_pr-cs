#include "buffer_processing.h"

int buffer_command_processing(char buffer[]){
    char err_check;
    char *tmp;
    
    tmp = strtok(buffer, " ");
    
    err_check = *tmp;
    if(!isdigit(err_check)){
		return -1;
	}
	else return atoi(tmp);
}

int buffer_array_processing(char buffer[],int array[]){
	int size=0;
    char *tmp;
    
    tmp = strtok(buffer, " ");
    tmp = strtok(NULL, " ");
    while (tmp != NULL) {
        array[size] = atoi(tmp);
        size++;
        tmp = strtok(NULL, " ");
    }
    
	return size;
}