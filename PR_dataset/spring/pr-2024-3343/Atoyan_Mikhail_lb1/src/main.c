#include <stdio.h>
#include <regex.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define AMOUNT_OF_MATCHES 3

int main() {
    const char *pattern = "([a-zA-Z0-9_-]+)@[a-zA-Z0-9_-]+: ?~ ?# (.+)";
    
    char buffer[BUFFER_SIZE];
    regex_t regex;
    regmatch_t matches[AMOUNT_OF_MATCHES];

    regcomp(&regex, pattern, REG_EXTENDED);
    
    while (fgets(buffer,BUFFER_SIZE,stdin)){
        if (strstr(buffer, "Fin.") != NULL)
            break;
        
        if (regexec(&regex, buffer, AMOUNT_OF_MATCHES, matches, 0) == 0){
            for (int i = 1; i < AMOUNT_OF_MATCHES; ++i){
                for (int j = matches[i].rm_so; j < matches[i].rm_eo; ++j)
                    printf("%c", buffer[j]);
                if (i == 1)
                    printf(" - ");
            }
        } 
    }
    
    
    regfree(&regex);
    
    return 0;
}