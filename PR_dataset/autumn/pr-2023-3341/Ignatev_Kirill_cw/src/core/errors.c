#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/errors.h"

void funcIdError(char *func_id){
    if (*func_id==10){
        puts("Error: Function number not entered");
        exit(1);
    }
    if ((*func_id>=32&&*func_id<=47)||(*func_id>=58)){
        puts("Error: Entered symbol");
        exit(1);
    }
    if (*func_id>53 && *func_id!=57){
        puts("Error: Wrong function number");
        exit(1);
    }
}
void keywordError(char* keyword){
    if (strlen(keyword)==0){
        puts("Error: Keyword not entered");
        exit(1);
    }
}

void errorText(char* no_split_text){
    if (strlen(no_split_text)==1){
        printf("Error: Text not entered\n");
        exit(1);
    }
}