#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 32ULL
#define END "Dragon flew away!"

int main()
{
	char* text;
	char c;
	int k = 0;
	int capacity = BLOCK_SIZE;
	int sentencesCount = 0;
	int newSentencesCount = 0;

	text = (char*)malloc(capacity);
	c = getchar();
	while (strcmp(text, END))
	{
		if (!((k == 0) && ((c == '\t') || (c == ' ')))) text[k++] = c;
		if (c == '.' || c == '?' || c == ';')
		{
			int flag = 1;
			sentencesCount++;
			text[k] = '\0';
			for (int i = 0; i <= k; i++)
				if (text[i] == '7')
					flag = 0;
			if (flag)
			{
				newSentencesCount++;
				printf("%s\n", text);
			}
			k = 0;
			capacity = BLOCK_SIZE;
			free(text);
			text = (char*)calloc(capacity, sizeof(char));
		}

		if (k == capacity - 1)
		{
			capacity += BLOCK_SIZE;
			text = (char*)realloc(text, capacity);
			if (text == NULL)
			{
				printf("%s\n", "Недостаточно памяти для выполнения операции.");
				return -1;
			}
		}
		c = getchar();
	}
	text[k] = '\0';
	printf("%s\n", text);
	free(text);
	
	printf("Количество предложений до %d и количество предложений после %d\n", sentencesCount, newSentencesCount);
	return 0;
}