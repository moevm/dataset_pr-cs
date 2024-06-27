#include <stdio.h>
#include <stdlib.h>

// извините за этот костыль, изначально выделение было написано с перевыделением,
// но там постоянно возникала ошибка, в которой разобраться я не смог
#define BLOCK_SIZE 12500

int main()
{
	char* text = (char*)malloc(BLOCK_SIZE*sizeof(char));
	char* text_ptr = text;
	char* text_begin = text;

	char* result = (char*)malloc(BLOCK_SIZE*sizeof(char));
	char* result_begin = result;

	char c;
	int n = 0, m = 0;
	int number_of_read = 0;
	
	do
	{
		c = getchar();

		number_of_read += 1;
		*text_ptr = c;

		// если предложение окончилось на '?' выполнять дальше не надо
		if (c == '?') {
			n++;
			text = text_ptr+1;
			continue; 
		}

		else if (c == '.' || c == ';' || c == '!')
		{
			// проверяем, не оканчивается ли предложение на !, т.к. если оканчивается, то такое
			// предложение считать не надо (по условию задачи)
			if (c != '!') {n++; m++; }
		
			// индикатор начала предложение, 0 - ещё вне приложения, 1 - в предложении
			char sentence_begin_flag = 0;
			for (; text <= text_ptr; text++)  
			{
				if (*text == '\n' || *text == '\t') {*text = ' '; }
				
				if (*text != ' ' || sentence_begin_flag) 
				{
					*result = *text;
					sentence_begin_flag = 1;
					result++;
				}
			}
				
			*result = '\n';
			result++;
		}

		text_ptr++;

	} while(c != '!'); 

	*(result-1) = '\0';

	printf("%s\n", result_begin);
	printf("Количество предложений до %d и количество предложений после %d\n", n, m);

	free(text_begin);
	free(result_begin);
	return 0;
}
