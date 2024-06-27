#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define ORIGINAL_SIZE 100
#define EXTRA_SIZE 50

int main(){
	int size = ORIGINAL_SIZE;
	char* text = calloc(size, sizeof(char));
	int n = 0;
	int m = 0;
	if (text == NULL){
		puts("Memory allocation error!");
		return 1;
	}
	char symbol;
	int index = 0;
	while ((symbol = getchar()) != '!'){
		if ((index + 6) >= size){
			size += EXTRA_SIZE;
			char* new_text = realloc(text, size * sizeof(char));
			if (new_text == NULL){
				free(text);
				puts("Memory allocation error!");
				return 1;
			}
			text = new_text;
		}
		if (index == 0 && symbol == ' '){
			continue;
		}
		if (index == 0 && symbol == '\n'){
			continue;
		}
		if (index > 0){
			if (symbol == '.' && text[index - 1] == '.'){
				text[index] = symbol;
				index++;
				continue;
			}
			if (text[index - 1] == '.' || text[index - 1] == '?' || text[index - 1] == ';'){
				n++;
				if (symbol == ' ' || symbol == '\n'){
					text[index] = '\n';
				}
				else{
					text[index] = '\n';
					index++;
					text[index] = symbol;
				}
			}
			else{
				if (text[index - 1] == '\n' && symbol == ' '){
					continue;
				}
				if (text[index - 1] == '\n' && symbol == '\n'){
					continue;
				}
				text[index] = symbol;
				if (isdigit(symbol)){
					if (text[index - 1] == ' ' || text[index - 1] == '\n' || (isdigit(text[index - 1]))){
						index++;
						continue;
					}
					else{
						index++;
						symbol = getchar();
						if (symbol == '.' || symbol == ';' || symbol == '?'){
							text[index] = symbol;
							index++;
							continue;
						}
						if (symbol == ' '){
							text[index] = symbol;
							index++;
							continue;
						}
						if (isdigit(symbol)){
							text[index] = symbol;
							index++;
							symbol = getchar();
							while (isdigit(symbol)){
								text[index] = symbol;
                                                               	index++;
                                                               	symbol = getchar();
							}
							if (symbol == ' '){
								text[index] = symbol;
                                                               	index++;
								continue;
                                                        }
							if (symbol == '.' || symbol == ';' || symbol == '?'){
                                                       		text[index] = symbol;
								index++;
								continue;
							}
						}
						while (symbol != '.' && symbol != ';' && symbol != '?'){
							index--;
							if (index < 0){
								index = -1;
								n++;
								break;
							}
							else{
								symbol = text[index];				
							}
						}
						symbol = getchar();
						while (symbol != '.' && symbol != ';' && symbol != '?'){
							symbol = getchar();
						}	
					}	
				}
			}
		}
		else{
			text[index] = symbol;
		}
		index ++;

	}
	text[index] = '\0';
	for (int i = 0; i < index; i++){
		if (text[i] == '.' || text[i] == ';' || text[i] == '?'){
			m++;
		}
	}
	printf("%s", text);
	free(text); 
	printf("!\nКоличество предложений до %d и количество предложений после %d\n", n, m);
	return 0;
}
