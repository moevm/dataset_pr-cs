#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N 30

int main(){
	char* sent; //для хранения предложения
	int len; //длина слова
	int chek = 1; //контроль !

	char c; //символ
	int i; //индексы символа в предложении//
	int count_fives; //для хранения '_555_' //
	int count_answer = 0;
	int count_555 = 0;


	do{
		//считываем новое предложение
		i = 0;
		len = N;
		sent = malloc(sizeof(char)*len);
		
		//проверка на разделитель
		do{
			c = getchar();
		}while(isspace(c));

		//поиск первой 5 из 555
		count_fives = -1;
		if(c == '5'){
			count_fives = 1;
		}
		
		do{
			sent[i] = c;
			c = getchar();
			i++; 

			if(i == len - 2){
				len += N;
				sent = realloc(sent, len*sizeof(char));
				if(sent==NULL){
				    exit(1);
				}
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
			sent[i] = c;
			sent[i+1] = '\0';
			count_answer++;
			printf("%s\n", sent);
		}else{
			count_555++;
		}
		free(sent);
		if(c == '!'){
			chek = 0;
		}
	
	}while(chek);


	printf("Количество предложений до %d и количество предложений после %d", count_answer + count_555 - 1, count_answer - 1);
	return 0;
}

