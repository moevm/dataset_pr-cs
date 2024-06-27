#include <stdio.h>

#include <string.h>

#include <regex.h>

void GroupPrint(char* string, regmatch_t group) {
    
    for (int i=group.rm_so; i<group.rm_eo; i++) {
        
        printf("%c", string[i]);
        
    }
    
}


int main()

{
    
    char* rStr = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.*)";
    
    size_t maxGroups = 3; regmatch_t groupArray[maxGroups]; regex_t regexCompiled;
    
    if (regcomp(&regexCompiled,rStr,REG_EXTENDED))
    
    {
        
        printf("Cant Compile\n");
        
        return 0;
        
    }
    
    char s[101];
    
    while(1)
    
    {
        
        fgets(s,100,stdin);
        
        if (strstr(s,"Fin.") != NULL){
            
            break;
            
        }
        
        if(regexec(&regexCompiled, s,maxGroups,groupArray,0) == 0){
            
            GroupPrint(s,groupArray[1]);
            
            printf(" - ");
            
            GroupPrint(s,groupArray[2]);
            
        }
        
    }
    
    regfree(&regexCompiled);
    
    return 0;
    
}