#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void change(char * text, int all){
	int count_upper = 0;
	int sentence_start = 0;
	int sentence_before = 0;
	int sentence_after = 0;

	for (int i = 0; text[i] != '\0'; i++){
		
		if (isspace(text[i]) && (text[i-1]=='.' || text[i-1]=='?' || text[i-1]==';')) {
			text[i] = '\n';
			sentence_before += 1;
			sentence_after += 1;
			sentence_start = i + 1; 
		}

		if (text[i] == '.' || text[i] == '?' || text[i] == ';'){

			for(int j = i - 1; (text[j] != '.' && text[j] != '?' && text[j] != ';') && j >= 0; j-- ) {
				if (text[j] >= 60 && text[j] <= 90){
				count_upper++;
				} 

			}

			if (count_upper >= 2){
				
				memmove(text + sentence_start, text + i + 2, all - i);
				i = sentence_start;
				sentence_before += 1;
				count_upper = 0;
			}
			else{
				
				count_upper = 0;
			}
		}
	}
		
	printf("%s\n", text);
	printf("Количество предложений до %d и количество предложений после %d\n", sentence_before, sentence_after);
}


int main()
{	
	char *text;
	int size = 100;
	text = (char *) malloc(size * sizeof(char));
	char symb;
	int i = 0;

	do{
		symb = getchar();
		if (i >= size){
			 char *resized_text = (char *) realloc(text, (size + 50) * sizeof(char));
			size += 50;
			if (resized_text != NULL){
				text = resized_text;
			}
			else printf("Ошибка выделения памяти.\n");
		}
		text[i] = symb;
		i++;
	}
	while(symb != '!');
	text[i] = '\0';
	change(text, i);
	free(text);
	return 0;
}

