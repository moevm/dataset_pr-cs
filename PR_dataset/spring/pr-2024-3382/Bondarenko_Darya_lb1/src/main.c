#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAX_STR_LENGTH 1000


int main()
{
    char *regexString = "(www.)?(([a-zA-Z0-9]+\\.)+[a-zA-Z0-9]+)(.*)(\\/([a-zA-Z0-9]+\\.[a-zA-Z0-9]+))";
    size_t maxGroups = 7;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Can't compile regular expression\n");
        return 0;
    }
    
    char text[MAX_STR_LENGTH];
    while ((fgets(text, MAX_STR_LENGTH, stdin)) && (strstr(text, "Fin.") == NULL))
    {
        if (regexec(&regexCompiled, text, maxGroups, groupArray, 0) == 0)
        {
            int site_start = groupArray[2].rm_so;
            int site_end = groupArray[2].rm_eo;
            char sitename[MAX_STR_LENGTH];
            
            int file_start = groupArray[6].rm_so;
            int file_end = groupArray[6].rm_eo;
            char filename[MAX_STR_LENGTH];
            
            strncpy(sitename, text + site_start, site_end - site_start);
            sitename[site_end - site_start] = '\0';
            
            strncpy(filename, text + file_start, file_end - file_start);
            filename[file_end - file_start] = '\0';
            
            printf("%s - %s\n", sitename, filename);
        }
    }
    
    regfree(&regexCompiled);
    
    return 0;
}