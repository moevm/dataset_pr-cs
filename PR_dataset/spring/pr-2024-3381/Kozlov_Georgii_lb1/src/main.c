#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 500
#define MAX_SIZE 4

int main()
{
	regex_t reegex;
	regmatch_t array1[MAX_SIZE];
	int status_compare;
	char string[SIZE];
	regcomp(&reegex, "([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+):[ ]*~[ ]*# (.+)\n", REG_EXTENDED);
	while(!strstr(string, "Fin."))
	{
		fgets(string, SIZE, stdin);
		status_compare = regexec(&reegex, string, MAX_SIZE, array1, 0);
		if (status_compare == 0)	
		{
			for (int i = array1[1].rm_so; i < array1[1].rm_eo; i++)
			{
				printf("%c", string[i]);
			}
			printf(" - ");
			for (int i = array1[3].rm_so; i < array1[3].rm_eo; i++)
			{
				printf("%c", string[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
