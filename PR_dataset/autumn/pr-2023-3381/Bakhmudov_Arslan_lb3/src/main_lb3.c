#include <stdio.h>
#include <stdlib.h>


#define MS 2048
#define MT 100500
//#define TERMINATOR "Dragon flew away!"


int main()
{
	char *sentence = malloc(MS*sizeof(char));
	char *sp = sentence;
	
	char *text  = malloc(MT*sizeof(char));
	int ti = 0;
	
	int n = 0, m = 0;

	char do_parse = 1;
	char s = getchar();

	while(do_parse)
	{
		*sp = s;
		sp++;

		switch(s)
		{
			case '!':
				/*// === WIP ===
				char terminator_found = 1;
				int term_iterator = 0;
				while(sentence[term_iterator]!='!')
				{

					if(sentence[term_iterator] != TERMINATOR[term_iterator])
					{
						terminator_found = 0;
						break;
					}
					term_iterator++;
				}
				if(terminator_found)
				{
					do_parse = 0;
				}
				*/
				do_parse = 0;
			
			case '.':
			case ';':
			case '?':
				*sp = '\0';
				sp = sentence;
				n += 1;
				if(s == '?'){break;}

				char begin = 0;
				while(*sp!='\0')
				{
					if(*sp=='\n')
					{
						*sp = ' ';
					}
					if((*sp!=' ' && *sp!='\t') || begin)
					{
						text[ti++] = *sp;
						begin = 1;
					}
					sp++;
				}
				text[ti++]='\n';
				sp = sentence;
				m += 1;
				break;
		}

		if(!do_parse)
		{
			text[ti++] = '\0';
			break;
		}
		s = getchar();
	}

	printf("%sКоличество предложений до %d и количество предложений после %d\n", text, --n, --m);

	free(sentence);
	free(text);
	return 0;
}
