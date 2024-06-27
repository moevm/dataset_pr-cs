#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int checksent(char* sent, int j){
	int flagstart = 0;
	int flagend = 0;
	for(int i = 0; i < j; i++){
		if(sent[i] == ' ' || sent[i] == '\t' || sent[i] == ',' || sent[i+1]  == '!' || sent[i+1]  == '.' || sent[i+1]  == ';' || sent[i+1]  == '?'){
			flagstart = 0;
			flagend = 0;
		}
		else{
			if(isalpha(sent[i]) && isdigit(sent[i+1])){
				flagstart = 1;
			}
			if(isdigit(sent[i]) && isalpha(sent[i+1]) && flagstart){
				flagend = 1;
			}
		}
		if(flagstart && flagend){
			return 0;
		}
	}
	return 1;
}


void freetext(char** text, int lentxt){
	for(int o = 0; o < lentxt; o++){
		free(text[o]);
	}
	free(text);
}


int main(){
	int text_len = 20;
	int sent_len = 40;
	int i = 0;
	int j = 0;
	int countersent = 0;
	int dragon = 1;
	char c = getchar();
	char** text = (char**)malloc(text_len * sizeof(char*));
	while(dragon){
		sent_len = 40;
		char* sent = (char*)malloc(sent_len * sizeof(char*));
		while(c == ' ' || c == '\t'|| c == '\n'){
			c = getchar();
		}
		while(c != '.' && c != ';' && c != '?' && c != '!' ){
			if(c != '\n'){
				sent[j] = c;
				j++;
				if(j+1 == sent_len){
					sent_len+= 10;
					sent = (char*)realloc(sent, sizeof(char) * sent_len);
					if(sent == NULL){
						freetext(text, i);
						exit(1);
					}
            	}
			}
			c = getchar();
		}
		sent[j] = c;
		sent[j+1]='\0';
		if(c == '!'){
			dragon = 0;
		}
		if(checksent(sent, j)){
			text[i] = sent;
			i++;
			if(i == text_len){
				text_len += 30;
				text = (char**)realloc(text, text_len * sizeof(char*));
				if(text == NULL){
					freetext(text, i);
					exit(1);
				}
			}
		}
		countersent++;
		c = getchar();
		j = 0;
	}
	for(int k = 0; k <i; k++)
		printf("%s\n", text[k]);
	printf("Количество предложений до %d и количество предложений после %d\n", countersent -1,i-1);
	freetext(text, i);
	return 0;
}


