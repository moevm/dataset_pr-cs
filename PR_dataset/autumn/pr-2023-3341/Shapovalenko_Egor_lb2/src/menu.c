#include "input.h"
#include "command_processing.h"
#include "buffer_processing.h"
#define MAX_STR_LEN 1202
#define MAX_ARRAY_SIZE 100

int main(){
	char buffer[MAX_STR_LEN];
	input(buffer);
	
    int array[MAX_ARRAY_SIZE];
    
    command_processing(buffer_command_processing(buffer),array,buffer_array_processing(buffer,array));
    
    return 0;
}
