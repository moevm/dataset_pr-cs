#include <stdio.h>
#include <stdlib.h>
#include <regex.h> 
#include <string.h>

int main(){
    char **arr = malloc(sizeof(char *));
    int i = 0;
    regex_t reegex;
    int pamat;
    int kol;
    char gch;
    int value;
    int user_name;
    int user_name_end;
    int command_end;
    int command_start;
    int len_user;
    int len_command;
    int flag = 0;
    while (1){
        pamat = 20;
        kol = 0;
        gch = getchar();
        arr[i] = malloc(pamat*sizeof(char));
        while(gch != '\n'){
            arr[i][kol] = gch;
            kol+=1;
            if(kol == 4){
                arr[i][kol]='\0';
                if (strcmp(arr[i], "Fin.")==0){
                    flag = 1;
                    break;
                }
            }
            if (kol+1 == pamat){
                pamat+=20;
                arr[i] = realloc(arr[i], pamat*sizeof(char));
            }
            gch = getchar();
        }
        if(flag){
            arr = realloc(arr, (i)*sizeof(char *));
            break;
        }
        arr[i][kol] = '\0';
        arr[i] = realloc(arr[i], (kol+1)*sizeof(char));
        i+=1;
        arr = realloc(arr, (i+1)*sizeof(char *));
    
    }
    value = regcomp( &reegex, "([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+): ?~ ?[#] (.*)", REG_EXTENDED);
    for (int j = 0; j<i; ++j){
        regmatch_t match[4];
        value = regexec(&reegex, arr[j], 4, match, 0);
        if(!value){
            user_name = match[1].rm_so;
            user_name_end = match[1].rm_eo;
            command_start = match[3].rm_so;
            command_end = match[3].rm_eo;
            len_command = command_end - command_start;
            len_user = user_name_end - user_name;
            char* user = malloc(sizeof(char)*(len_user));
            char* command = malloc(sizeof(char)*(len_command));
            strncpy(user, arr[j]+user_name, len_user);
            user[len_user] = '\0';
            strncpy(command, arr[j]+command_start, len_command);
            command[len_command] = '\0';
            printf("%s - %s\n", user, command);
            free(user);
            free(command);
        }
    }
    for(int j = 0; j<i+1; ++j){
        free(arr[j]);
    }
    free(arr);
    regfree(&reegex);
    return 0;
}