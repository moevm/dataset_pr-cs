#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>


#define BSIZE 128
#define NGROUPS 4
#define NAME 1
#define CMD 3


int main()
{
	regex_t regex;
	if (regcomp(&regex, "([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+) ?: ?~ ?# ?(.+)$", REG_EXTENDED) != 0)
	{
		printf("[ERROR] Regex wasn\'t compiled :(\n");
		return 1;
	}

	regmatch_t pm[NGROUPS];
	int status;
	char * string = malloc(BSIZE*sizeof(char));
	int i;
	
	while (1)
	{
		fgets(string, BSIZE, stdin);
		for (i = 0; string[i] != '\n' && string[i] != '\0'; i++);
		string[i] = '\0';
		if (!strcmp(string, "Fin."))
		{
			break;
		}

		status = regexec(&regex, string, NGROUPS, pm, 0);
		if (!status)
		{
			string[pm[NAME].rm_eo] = '\0';
			string[pm[CMD].rm_eo] = '\0';
			printf("%s - %s\n", string + pm[NAME].rm_so, string + pm[CMD].rm_so);

		}
	}

	free(string);
	regfree(&regex);
	return 0;
}
