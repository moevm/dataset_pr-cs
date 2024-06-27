#include <stdio.h>
#include <regex.h>

int main(void) {
    regex_t r;
    regcomp(&r, "(.*:\\/*)*(w*\\.)*(([a-z]+\\.)+[a-z]+)\\/(.*\\/)*(.*\\..*)\n", REG_EXTENDED);
    char t[81];
    regmatch_t m[7];
    while (fgets(t, 81, stdin))        
        if (!regexec(&r, t, 7, m, 0)) 
            printf("%.*s - %.*s\n", (int)(m[3].rm_eo - m[3].rm_so), &t[m[3].rm_so], (int)(m[6].rm_eo - m[6].rm_so), &t[m[6].rm_so]);
    regfree(&r);
    return 0;
}
