#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ADDITIONAL_DATA 10

int main()
{
	char** text = (char**)malloc(sizeof(char*) * ADDITIONAL_DATA);
	if (!text)
		return 0;
	
	int cntSentence = 0;
	int capacityText = ADDITIONAL_DATA;
	for (int i = 0; ; i++)
	{
		text[i] = (char*)malloc(sizeof(char) * ADDITIONAL_DATA);
		if (!text[i])
		{
			free(text);
			return 0;
		}

		char symbol;
		int idxSymbol = 0;
		int capacitySentence = ADDITIONAL_DATA;
		while ((symbol = getchar()))
		{
            if (symbol == '\n' || symbol == EOF)
                break;
                
			text[i][idxSymbol++] = symbol;

			if (idxSymbol == capacitySentence)
			{
				capacitySentence += ADDITIONAL_DATA;
				text[i] = (char*)realloc(text[i], sizeof(char) * capacitySentence);
				if (!text[i])
				{
					free(text);
					return 0;
				}
			}
		}
		text[i][idxSymbol] = '\0';
		cntSentence++;

		if (strcmp(text[i], "Fin.") == 0)
			break;

		if (cntSentence == capacityText)
		{
			capacityText += ADDITIONAL_DATA;
			text = (char**)realloc(text, sizeof(char*) * capacityText);
			if (!text)
				return 0;
		}

	}

	char* regexString = "([a-zA-Z]+:\\/\\/)?(w{3}\\.)?(\\w+(\\.\\w+)+)+\\/(\\w+\\/)*(\\w+\\.\\w+)";
    int maxGroup = 7;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroup];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Can't compile regular expression");
        return 0;
    }

    for (int i = 0; i < cntSentence; i++)
    {
        if(regexec(&regexCompiled, text[i], maxGroup, groupArray, 0) == 0)
        {
            for (int j = groupArray[3].rm_so; j < groupArray[3].rm_eo; j++)
            {
                printf("%c", text[i][j]);
            }
            printf(" - ");
            for (int j = groupArray[6].rm_so; j < groupArray[6].rm_eo; j++)
            {
                printf("%c", text[i][j]);
            }
            printf("\n");
        }
        free(text[i]);
    }
    free(text);
    regfree(&regexCompiled);

	return 0;
}