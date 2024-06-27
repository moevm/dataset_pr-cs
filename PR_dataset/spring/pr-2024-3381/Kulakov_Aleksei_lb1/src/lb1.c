#include <stdio.h>
#include <string.h>
#include <regex.h>


int main()
{
    regex_t regex;
    regcomp(&regex,"([A-Za-z0-9_-]+)@[A-Za-z0-9_-]+: *~ *# ([ -~]+)", REG_EXTENDED);
    while(1) {
        char s[1000];
        fgets(s,1000,stdin);
        regmatch_t matches[3];
        if(strcmp(s,"Fin.") == 0) {
            break;
        }
        s[strlen(s) - 1] = '\0';
        int reti = regexec(&regex, s, 3, matches, 0);
        if(reti == 0) {
            if(matches[1].rm_so != -1 &&  matches[1].rm_eo != -1 && matches[2].rm_so != -1 &&  matches[2].rm_eo != -1) {
                printf("%.*s",matches[1].rm_eo - matches[1].rm_so, s + matches[1].rm_so);
                printf(" - ");
                printf("%.*s\n",matches[2].rm_eo - matches[2].rm_so, s + matches[2].rm_so);
            }
        }
    }
    regfree(&regex);
    return 0;
}