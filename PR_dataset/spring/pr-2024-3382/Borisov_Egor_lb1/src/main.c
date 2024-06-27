#include <stdio.h>
#include <regex.h>
#include <string.h>


int main()
{
    char* stringRegex = "((\\w+\\.)+\\w+)(.*)\\/(\\w+\\.\\w+)";
    size_t maxSize = 5;
    regex_t regexCompiled;
    regmatch_t groupArr[maxSize];
    if(regcomp(&regexCompiled, stringRegex, REG_EXTENDED)){
        printf("Oops! Something went wrong! Regular expression compilation error.\n");
        return 0;
    }
    char str[1000];
    while(fgets(str, 1000, stdin)){
        if(strstr(str, "Fin.") != NULL){
            break;
        }
        if(regexec(&regexCompiled, str, maxSize, groupArr, 0) == 0){
            char website[1000];
            char file[1000];
            strncpy(website, str + groupArr[1].rm_so, groupArr[1].rm_eo - groupArr[1].rm_so);
            strncpy(file, str + groupArr[4].rm_so, groupArr[4].rm_eo - groupArr[4].rm_so);
            website[groupArr[1].rm_eo - groupArr[1].rm_so] = '\0';
            file[groupArr[4].rm_eo - groupArr[4].rm_so] = '\0';
            if(strstr(website, "www.") != NULL){
                printf("\n%s - %s", &website[4], file);
            }
            else{
                printf("\n%s - %s", website, file);
            }
        }
    }
    regfree(&regexCompiled);
    return 0;
}