#include <stdio.h>
#include <regex.h>
#include <string.h>

int main()
{
    char* pattern = "([a-zA-Z0-9_]+)@[0-9a-zA-Z_-]+: ?~ ?# (.+\n)";
    
    regex_t reg_str;
    regcomp(&reg_str, pattern, REG_EXTENDED);
    
    regmatch_t matches[3];
    char sent[100];
    
    while(strcmp(sent, "Fin.")) {
        fgets(sent, 99, stdin);
        
        if (!(regexec(&reg_str, sent, 3, matches, 0))) {
            for (int i = matches[1].rm_so; i < matches[1].rm_eo; i++) {
                printf("%c", sent[i]);
            }
            
            printf(" - ");
            
            for (int j = matches[2].rm_so; j < matches[2].rm_eo; j++) {
                printf("%c", sent[j]);
            }
        }
    }
    
    regfree(&reg_str);
    
    return 0;
}
