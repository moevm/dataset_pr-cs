#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int main()
{
	regex_t regex;
	regmatch_t regex_group[3];
	char* pattern = "([_A-Za-z0-9]+)@[-_A-Za-z0-9]+:\\s?~\\s?#\\s(.+\n)";
	regcomp(&regex, pattern, REG_EXTENDED);
	
	char sentence[1000];
	char fin_sentence[5] = "Fin.";
	
	while (strstr(sentence,fin_sentence) == 0)
	{
		fgets(sentence,1000,stdin);

		if (regexec(&regex, sentence, 3, regex_group, 0) == 0)
		{
			for (int i = regex_group[1].rm_so; i < regex_group[1].rm_eo; i++)
			{
				printf("%c", sentence[i]);
			}
			printf(" - ");
			for (int j = regex_group[2].rm_so; j < regex_group[2].rm_eo; j++)
			{
				printf("%c", sentence[j]);
			}
		}
	}
	regfree(&regex);
	return 0;
}
