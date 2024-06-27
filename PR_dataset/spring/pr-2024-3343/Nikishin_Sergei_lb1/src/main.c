#include <stdio.h>
#include <regex.h>

int main() {
    regex_t r;
    regcomp(&r,"(\\w+)@[--w]+: *~ *# (.+)",1);
    char t[77];
    regmatch_t m[3];
    while (fgets(t, 77, stdin))        
        if (!regexec(&r, t, 3, m, 0)) 
            printf("%.*s - %.*s", (int)(m[1].rm_eo - m[1].rm_so), &t[m[1].rm_so], (int)(m[2].rm_eo - m[2].rm_so), &t[m[2].rm_so]);
    return 0;
}
