#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define BLOCK_SIZE (size_t)32
#define TERMINATE_SENTENCE "Fin."
#define REGEX "([a-zA-Z0-9_-]+)@[a-zA-Z0-9_-]+: ?~ ?# (.+)"

int main(void)
{
	int end = 0;
	while (!end)
	{
		size_t capacity = BLOCK_SIZE;
		char* str = (char*)malloc(capacity * sizeof(char));
		if(str == NULL)
		{
			free(str);
			exit(0);
		}		
		size_t k = 0;
		while (str[k - 1] != '\n' && !end)
		{
			char c = getchar();
			str[k++] = c;			
			if(k == capacity - 1)
			{
				capacity += BLOCK_SIZE;
				str = (char*)realloc(str, capacity * sizeof(char));
				if(str == NULL)
				{
					free(str);
					exit(0);
				}
			}
			if (c == '.')
			{
				str[k] = '\000';
				if(!strcmp(str, TERMINATE_SENTENCE)) end = 1;
			}
		}
		str[k] = '\000';
		size_t groupsCount = 3;
		regex_t compiledRegex;
		regmatch_t groupsArray[groupsCount];
		if (regcomp(&compiledRegex, REGEX, REG_EXTENDED))
		{
			printf("Error");
			return 0;
		}
		if (!regexec(&compiledRegex, str, groupsCount, groupsArray, 0))
		{
			for(size_t i = groupsArray[1].rm_so; i < groupsArray[1].rm_eo; i++)
				printf("%c", str[i]);
			printf(" - ");
			for(size_t i = groupsArray[2].rm_so; i < groupsArray[2].rm_eo; i++)
				printf("%c", str[i]);
		}
		regfree(&compiledRegex);
		free(str);
	}
	return 0;
}