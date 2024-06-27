#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_triplefive(char *str);

int main(void)
{
	char *data = (char*)malloc(sizeof(char));
	char ch = getchar();
	int signs = 1;

	while (ch != '!'){	
		data[signs-1] = ch;
		data = (char*)realloc(data, ++signs * sizeof(char));
		ch = getchar();
	}

	data[signs-1] = '\0';
	char *sentence = (char*)malloc(sizeof(char));
	int cnt = 1;
	int sents_amount = 0;
	int new_sents_amount = 0;

	for(int i = 0; i < signs; i++){
		if(data[i] != '\n' && data[i] != '\t'){
			sentence[cnt-1] = data[i];
			sentence = (char*)realloc(sentence, ++cnt * sizeof(char));
		}
		if(data[i] == '.' || data[i] == ';' || data[i] == '?'){
			if(data[i] == '.' && data[i + 1] == '.' && data[i + 2] == '.'){
				sentence[cnt-1] = data[++i];
				sentence = (char*)realloc(sentence, ++cnt * sizeof(char));
				sentence[cnt-1] = data[++i];
				sentence = (char*)realloc(sentence, ++cnt * sizeof(char));
				continue;
			}
			sentence[cnt-1] = '\0';
			if(!check_triplefive(sentence)){
				printf("%s\n", sentence);
				new_sents_amount++;
			}
			free(sentence);
			sents_amount++;
			cnt = 1;
			sentence = (char*)malloc(sizeof(char));
			i++;
		}
	}
	printf("%s!\n", sentence);
	free(sentence);
	free(data);
	printf("Количество предложений до %d и количество предложений после %d", sents_amount, new_sents_amount);
	return 0;
}

int check_triplefive(char *str){
	const char* substr = "555";
	char *res = strstr(str, substr);
	if(res != NULL && (res-str == 0 && str[res-str+3] == ' '))
		return 1;
	if(res != NULL && (str[res-str-1] == ' ' && str[res-str+3] == ' '))
		return 1;
	if(res != NULL && (str[res-str-1] == ' ' && str[res-str+3] == '.'))
		return 1;
	if(res != NULL && (str[res-str-1] == ' ' && str[res-str+3] == '?'))
		return 1;
	if(res != NULL && (str[res-str-1] == ' ' && str[res-str+3] == ';'))
		return 1;
	return 0;
}