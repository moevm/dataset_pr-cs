#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>



int main()
{
    const char* regexString =
                    "([wW]{3}\\.)?"
                    "(([a-z0-9A-Z_]+\\.)+[a-z0-9A-Z_]+)"
                    "(.*)"
                    "(\\/([a-z0-9A-Z_]+\\.[a-z0-9A-Z_]+))";
    size_t maxGroups = 20;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("Wow no - can't compile regular expression\n");
        return 0;
    }
    for(;;){
        char buf[1000];
        if(!fgets(buf,sizeof(buf),stdin))
            break;
        //printf("%s\n",buf);
        if(strncmp(buf,"Fin.",4)){
            if (regexec(&regexCompiled,buf,maxGroups,groupArray,0)==0){
                //for(int k=0;k<maxGroups;k++)
                //    printf("%d %d\n",groupArray[k].rm_so,groupArray[k].rm_eo);
                printf("\n");
                for(int j=groupArray[2].rm_so;j<groupArray[2].rm_eo;j++)
                    printf("%c",buf[j]);
                printf(" - ");
                for(int j=groupArray[6].rm_so;j<groupArray[6].rm_eo;j++)
                    printf("%c",buf[j]);
            } 
        }
    }

    regfree(&regexCompiled);
    return 0;
}