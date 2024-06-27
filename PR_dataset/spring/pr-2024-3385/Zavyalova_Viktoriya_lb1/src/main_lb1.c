#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX 3

int main(){
    char* regexString = "([a-zA-Z0-9_-]+)@[a-zA-Z0-9_-]+: ?~ ?# (.+)";
    regex_t regexCompiled;
    regmatch_t groupArray[MAX];
    char arr[100];
    
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED) != 0){
        printf("Error");
        return 1;
    }
    
    while (fgets(arr, 100, stdin)){
        if (strcmp(arr, "Fin.") == 0) {
            break;
        }
        
        if (regexec(&regexCompiled, arr, MAX, groupArray, 0) == 0){
            for(int j = groupArray[1].rm_so; j < groupArray[1].rm_eo; j++){
                printf("%c",arr[j]);
            }
	            
		    printf(" - ");
			for(int j = groupArray[2].rm_so; j < groupArray[2].rm_eo; j++){
		        printf("%c",arr[j]);
			}
        }
    
    }
    
    regfree(&regexCompiled);
    
    return 0;
}