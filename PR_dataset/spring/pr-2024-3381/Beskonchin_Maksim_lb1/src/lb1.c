#include <stdio.h>
#include <regex.h>
#include <string.h>

int main ()
{
    char * regexString = "([a-z]+:\\/\\/)?(www\\.)?((\\w+\\.)+[a-z]+)\\/((\\w+\\/)+)?(\\w+\\.\\w+)";
    size_t maxGroups = 8;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Wowm no - can't compile regular expression\n");
        return 1;
    };
    char s[1024];
    while (!strstr(s, "Fin.")){
        fgets(s,1024,stdin);
        if (regexec(&regexCompiled, s, maxGroups, groupArray, 0) == 0)
        {
            puts("");
            int i =3;
            while(i <= 7)
            {
                for(int j=groupArray[i].rm_so;j<groupArray[i].rm_eo;j++){
                    printf("%c",s[j]);}
                if (i == 3)
                    printf(" - ");
                i +=4;
            }
        }
    }
    regfree(&regexCompiled);
    return 0;
}
