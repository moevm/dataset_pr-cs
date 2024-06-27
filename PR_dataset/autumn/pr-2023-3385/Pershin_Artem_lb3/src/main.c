#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TEXTBLOCK 20
#define SENBLOCK 10
#define WORDBLOCK 10


int check(char* word){
	unsigned key = 0;
	for(int i = 0; word[i]; i++){
		if(key & 1){
			if(isdigit(word[i])){
				key++;
			}
		}else{
			if(isalpha(word[i])){
				key++;
			}
		}
	}
	return (key >= 3);
}


void freetext(char*** text, int i){
	for(int ri = 0; ri < i; ri++){
    		for(int rj = 0; text[ri][rj]; rj++){
			free(text[ri][rj]);
		}
		free(text[ri]);
	}
	free(text);
}


int main(){
	int textsize = TEXTBLOCK;
	int sensize = SENBLOCK;
	int wordsize = WORDBLOCK;
	int i = 0;
	int j = 0;
	int k = 0;
	int sensbefore = 0;
	int dragon = 1;
	int flag = 1;
	char c = getchar();
	char*** text = (char***)malloc(textsize * sizeof(char**));
	if(text == NULL){
		freetext(text, i);
		printf("Ошибка выделения памяти\n");
		exit(1);
	}
	while(dragon){
		sensize = SENBLOCK;
		char** sen = (char**)malloc(sensize * sizeof(char*));
		if(sen == NULL){
			freetext(text, i);
			printf("Ошибка выделения памяти\n");
			exit(1);
		}
		while(c == ' ' || c == '\t'|| c == '\n'){
			c = getchar();
		}
		while(c != '.' && c != ';' && c != '?' && c != '!' ){
			wordsize = WORDBLOCK;
			char* word = (char*)malloc(sizeof(char) * wordsize);
			if(word == NULL){
				freetext(text, i);
				printf("Ошибка выделения памяти\n");
				exit(1);
			}
			if(c == ' '|| c  == ','){
				c = getchar();
			}
			while(c != '.' && c != ';' && c != '?' && c != '!' && c != ',' && c != ' '  && c != '\t'){
				if(c != '\n'){
					word[k] = c;
					k++;
				}
				c = getchar();
				while((k-1) >= wordsize){
				    wordsize += WORDBLOCK;
				    word = (char*)realloc(word, sizeof(char) * wordsize);
				    if(word == NULL){
				    		freetext(text, i);
						printf("Ошибка выделения памяти\n");
						exit(1);
					}		
				}
			}
			word[k] = c;
			word[k+1] = '\0';
			k = 0;
			if(check(word)){
				flag = 0;
			}
			sen[j] = word;
			j++;
			if(j == sensize){
				sensize += SENBLOCK;
				sen = (char**)realloc(sen, sizeof(char*) * sensize);
				if(sen == NULL){
					freetext(text, i);
					printf("Ошибка выделения памяти\n");
					exit(1);
				}
			}
			
		}
		sen[j] = '\0';
		if( c == '!' ){
			dragon = 0;
		}
		if(flag){
			text[i] = sen;
			i++;
			if(i == textsize){
				textsize += TEXTBLOCK;
				text = (char***)realloc(text, textsize * sizeof(char**));
				if(text == NULL){
					freetext(text, i);
					printf("Ошибка выделения памяти\n");
					exit(1);
				}
			}
		}
		sensbefore++;
		flag = 1;
		c = getchar();
		j = 0;
        }
	for(int ri = 0; ri < i; ri++){
        	for(int rj = 0; text[ri][rj]; rj++){
			printf("%s", text[ri][rj]);
		}
		printf("\n");
	}
	printf("Количество предложений до %d и количество предложений после %d\n", sensbefore - 1 , i - 1);
	for(int ri = 0; ri < i; ri++){
    	for(int rj = 0; text[ri][rj]; rj++){
			free(text[ri][rj]);
		}
		free(text[ri]);
	}
	free(text);
	return 0;
}
