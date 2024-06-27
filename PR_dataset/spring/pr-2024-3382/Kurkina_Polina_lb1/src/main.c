#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX 1000

int main()
{
	int r;
    char *regexString = "([a-zA-Z0-9_]+)@[A-Za-z0-9_\\-]+: ?~ ?# ([a-zA-Z0-9 -_:]+)";
   	size_t maxGroups = 3;
    
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
		printf("Wow, no - can't compile regular expression\n");
		return 0;
	}
    
	char buffer[MAX];
	while (!strstr(buffer, "Fin.")) {
		fgets(buffer, MAX, stdin);

		r = regexec(&regexCompiled, buffer, maxGroups, groupArray, 0);
		if (!r) {   /* проверяем что регулярка нормально скомпилировалась */
			for (size_t i = 1; i < maxGroups; i++) {
				if (groupArray[i].rm_so == -1)
					break;

				for (size_t j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++)
					printf("%c", buffer[j]);
				if (i < maxGroups - 1)                    // если мы видим, что данная группа не последняя, то выводим -
					printf(" - ");                    // если так делать не будем, то будет вывод типа:
			}                                                 // "root - sudo exit -" вместо "root - sudo exit"
			printf("\n");
		}
	}
	regfree(&regexCompiled);
	return 0;
}
