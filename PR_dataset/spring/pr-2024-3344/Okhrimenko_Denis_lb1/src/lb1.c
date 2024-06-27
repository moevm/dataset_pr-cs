#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


int main(){
    char* input_buffer = (char*)malloc(sizeof(char) * 100000);
    char* text = (char*)malloc(sizeof(char) * 100000);
    char* pattern = "((http|https|ftp):\\/\\/)?(www\\.)?(([a-zA-Z]+\\.)+[a-zA-Z]+)(\\/[a-zA-Z]+)*(\\/([a-zA-Z]+\\.[a-zA-Z0-9_+=!-]+))";
    regmatch_t group_match[9]; //структура с матчами и группами
    regex_t pointer_to_regex;
    //Скомпилируем регулярное выражение: 
    regcomp(&pointer_to_regex, pattern, REG_EXTENDED); //Расширенный синтаксис regex (icase - w\out registr)
    while(strstr(fgets(input_buffer, 100000, stdin), "Fin.") == NULL){
        strcat(text, input_buffer);
    }
    
    //finding matches
    while(1){
        int check = regexec(&pointer_to_regex, text, 9, group_match, 0);
        if(check != REG_NOMATCH)
        {
            if (group_match[4].rm_so != -1 && group_match[4].rm_eo != -1 &&
                group_match[8].rm_so != -1 && group_match[8].rm_eo != -1) 
            {
                printf("%.*s - %.*s\n",
                       (int)(group_match[4].rm_eo - group_match[4].rm_so),
                       text + group_match[4].rm_so,
                       (int)(group_match[8].rm_eo - group_match[8].rm_so),
                       text + group_match[8].rm_so);
            text += group_match[0].rm_eo;
            }
        } else {
            break;
        }
    }
}