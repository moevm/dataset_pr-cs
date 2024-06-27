#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max_array_size 100
#define max_str_len 1202
#define format "%d\n"

int abs_max(int array[],int size){
    int abs_max_iterator=0;
    for(int i = 1; i < size; i++){
        if(abs(array[i]) > abs(array[abs_max_iterator])) abs_max_iterator = i;
    }
    return abs_max_iterator;
}

int abs_min(int array[],int size){
    int abs_min_iterator=0;
    for(int i = 1; i < size; i++){
        if(abs(array[i]) < abs(array[abs_min_iterator])) abs_min_iterator = i;
    }
    return abs_min_iterator;
}

int diff(int array[],int size){
    return array[abs_max(array,size)]-array[abs_min(array,size)];
}

int sum(int array[],int size){
    int summ=0;
    for(int i = abs_max(array,size); i < size; i++) summ += array[i];
    return summ;
}

void input(char buffer[]){
	fgets(buffer, max_str_len, stdin);
}

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

void print_answer(int answer){
	printf(format,answer);
}

void print_error(){
	printf("Данные некорректны\n");
}

void command_processing(int command,int array[],int size){
    switch(command){
		case 0:
		    print_answer(array[abs_max(array, size)]);
			break;
        case 1:
			print_answer(array[abs_min(array, size)]);
			break;
        case 2:
            print_answer(diff(array, size));
            break;
        case 3:
		    print_answer(sum(array, size));
			break;
        default:
            print_error();	
	}
}

int main(){
	char buffer[max_str_len];
	input(buffer);
	
    int array[max_array_size];
    
    command_processing(buffer_command_processing(buffer),array,buffer_array_processing(buffer,array));
    
    return 0;
}
