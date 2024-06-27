#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char* regexString = "([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+)\\:\\s*\\~\\s*(\\$|\\#)\\s(.+)";
    size_t maxGroups = 5;


    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];


    if(regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("can't compile");
        return 0;

    }

    char s[101];
    int capacity = 25; //start count string
    char** users_names = malloc(capacity * sizeof(char*));
    char** users_commands = malloc(capacity * sizeof(char*));
    

    int count = 0;
    int n = 0;
    while(1){
        fgets(s,100,stdin);
        if(strstr(s, "Fin.") != NULL)
            break;

        if(regexec(&regexCompiled, s,maxGroups, groupArray,0) == 0){
            if(s[groupArray[3].rm_so] == '#'){
                count ++;
                if (count >= capacity){
                    capacity*= 1.5;
                    if(users_names != NULL && users_commands != NULL){
                        users_names = realloc(users_names, capacity * sizeof(char*));
                        users_commands = realloc(users_commands, capacity * sizeof(char*));
                    }
                }

                int size_c_names = (int)groupArray[1].rm_eo - (int)groupArray[1].rm_so + 1;
                if(users_names != NULL){
                    users_names[count - 1] = malloc(size_c_names * sizeof(char));
                }
                if(users_names[count - 1] != NULL){
                    for(int j = groupArray[1].rm_so;j<groupArray[1].rm_eo;j++){
                        users_names[count - 1][n++] = s[j];
                    }
                    users_names[count - 1][size_c_names] = '\0';
                }



                int size_c_command = (int)groupArray[4].rm_eo - (int)groupArray[4].rm_so + 1;
                
                if(users_commands != NULL){
                    users_commands[count - 1] = malloc( size_c_command * sizeof(char));
                }

                if(users_commands[count - 1] != NULL){
                    n = 0;
                    for(int k = groupArray[4].rm_so;k < groupArray[4].rm_eo - 1;k++){
                        users_commands[count - 1][n ++] = s[k];
                    }
                    n = 0;
                    users_commands[count - 1][size_c_command] = '\0';
                }
            }
        }



    }


    for(int i = 0;i < count; i ++){
        printf("%s - %s\n",users_names[i],users_commands[i]);
    }
    if(users_names != NULL && users_commands != NULL){
        for(int i = 0;i < count; i ++){
            free(users_names[i]);
            free(users_commands[i]);
        }
    
        free(users_names);
        free(users_commands);
    }

    regfree(&regexCompiled);

    return 0;
}
