#include <stdio.h>
#include <stdlib.h>

int main(){
	char* sentence; //запихивай предложение сюда
	int sentence_len; //минимальная длина символа по умолчанию
	int not_dragon = 1; //контроль !

	char c; //временное место поб символ
	int i; //индексы символа в предложении
	       //
	int count_fives; //для проверки на трипятёрочность
			 //
	int count_sent = 0;
	int count_555_sent = 0;


	do{
		//обнуляем счётчик индексов и мин длину массива, заводим динамический массив под предложение
		i = 0;
		sentence_len = 50;
		sentence = malloc(sizeof(char)*sentence_len);
		
		//собираем пробелы и табы
		do{
			c = getchar();
		}while(c == ' ' || c == '\t');
		//собираем пробелы и табы

		//собираем 5
		count_fives = -1;
		if(c == '5'){
			count_fives = 1;
		}
		
		do{
			sentence[i] = c;
			c = getchar();
			i++; //i - текущая длина массива всесь заполнен, нужно дописать ещё 2

			if(i == sentence_len - 2){
				sentence_len += 20;
				sentence = realloc(sentence, sentence_len*sizeof(char));
			}
			
			if(count_fives == -1){
				if(c == ' '){
					count_fives++;
				}
			}else if(count_fives > -1 && count_fives < 3){
				if(c == '5'){
					count_fives++;
				}else{
					count_fives = -1;
				}
			}else if(count_fives == 3){
				if(c == '.' || c == ';' || c == ' ' || c == '?'){
					count_fives++;
				}else{
					count_fives = -1;
				}	
			}



		}while(c != ';' && c != '.' && c != '?' && c != '!');
		if(count_fives != 4){
			sentence[i] = c;
			sentence[i+1] = '\0';
			count_sent++;
			printf("%s\n", sentence);
		}else{
			count_555_sent++;
		}
		free(sentence);
		if(c == '!'){
			not_dragon = 0;
		}
	
	}while(not_dragon);


	printf("Количество предложений до %d и количество предложений после %d", count_sent + count_555_sent - 1, count_sent - 1);
	return 0;
}
