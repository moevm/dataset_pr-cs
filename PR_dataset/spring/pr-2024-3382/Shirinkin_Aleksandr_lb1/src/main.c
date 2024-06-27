#include <stdio.h>
#include <regex.h>
#include <string.h>
int main ()
{
    char * regexString = "((\\w+\\.)+\\w+)(.*)(\\/\\w+\\.\\w+)";
    size_t maxGroups = 5;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Can't compile regular expression\n");
        return 0;
    };
    char s[1000];
    while (fgets(s,1000,stdin)){
        if (strstr(s, "Fin.") != NULL){break; printf("\n");}
        if (regexec(&regexCompiled, s, maxGroups, groupArray, 0) == 0)
        {
            char url[1000];
            char filename[1000];
            strncpy(url, s + groupArray[1].rm_so, groupArray[1].rm_eo - groupArray[1].rm_so);
            url[groupArray[1].rm_eo - groupArray[1].rm_so] = '\0';
            char *wwwSubstr = "www.";
            char *wwwPos = strstr(url, wwwSubstr);
            if (wwwPos == url) {
                memmove(url, url + strlen(wwwSubstr), strlen(url) - strlen(wwwSubstr) + 1);
            }
            strncpy(filename, s + groupArray[4].rm_so + 1, groupArray[4].rm_eo - groupArray[4].rm_so - 1);
            filename[groupArray[4].rm_eo - groupArray[4].rm_so - 1] = '\0';
            printf("\n%s - %s", url, filename);
        }
    }
    regfree(&regexCompiled);
    return 0;
}

