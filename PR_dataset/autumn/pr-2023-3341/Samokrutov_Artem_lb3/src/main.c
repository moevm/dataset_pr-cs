#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define END '\0'

char *input(int *, int *);
char **split(char *, int);
void trim(char **, int);
void del_sentences_w_ninf_numbers(char **, int, int *);
void output(char **, int, int);
int check(char *);

int main() {
	int text_size = 1, num_of_sentences = 0;
	char *text = input(&text_size, &num_of_sentences);

	char **paragraphs = split(text, num_of_sentences);

 	trim(paragraphs, num_of_sentences);

   	int deleted = 0;
   	del_sentences_w_ninf_numbers(paragraphs, num_of_sentences, &deleted);
  
   	output(paragraphs, num_of_sentences, deleted);
  	return 0;
}

char *input(int *size, int *num) {
  	int capacity = 1;
  	char *text = (char *)malloc(sizeof(char));

  	char ch = getchar();
  	char pre_ch = ' ';
  	while (1) {
    		text[(*size) - 1] = ch;
    		if ((*size) >= capacity) {
      			capacity *= 2;
			text = (char *)realloc(text, capacity * sizeof(char));
   		 }

   	 (*size)++;
	
	int ch_is_punc = (ch == '.' || ch == ';' || ch == '?' || ch == '!');
	int pre_ch_is_punc = (pre_ch == '.' || pre_ch == ';' || pre_ch == '?');
   	if (ch_is_punc && !pre_ch_is_punc) {
     		(*num)++;
   	}

  	if (ch == '!') {
 		break;
        }
    
    	pre_ch = ch;    
    	ch = getchar();
  	}
  	return text;
}

char **split(char *text, int num) {
  	char **split_text = (char **)calloc(num + 1, (sizeof(char *)));
  	char *separators = ".;?!";
  	char *sentence;
	char *copy_text = (char *)calloc(strlen(text), sizeof(char));
   	strncpy(copy_text, text, strlen(text) + 1);

  	int i = 0;
  	sentence = strtok(copy_text, separators);
  	int size = 0;
  	while (sentence != NULL) {
      		size = strlen(sentence);
      		int diff = sentence - copy_text;
    		split_text[i] = (char *)calloc(size + 1, sizeof(char));
    		strncpy(split_text[i], sentence, size);
    		split_text[i][size] = *(text + diff + size);
		i++;
   		sentence = strtok(NULL, separators);
	}

	

 	free(copy_text);
  	return split_text;
}

void trim(char **paragraphs, int num) {
	int i = 0;
  	while (i < num) {
    		if (paragraphs[i][0] == ' ' || paragraphs[i][0] == '\t') {
     			int end = strlen(paragraphs[i]);
      			for (int j = 0; j < end; j++)
        			paragraphs[i][j] = paragraphs[i][j+1];
      			paragraphs[i][end] = END;
   	 	}
		if (paragraphs[i][0] != ' ' && paragraphs[i][0] != '\t') 
			i++;
  	}
}

void del_sentences_w_ninf_numbers(char **paragraphs, int num, int *deleted) {
   	for (int i = 0; i < num; i++){
        	for (int j = 0; j < strlen(paragraphs[i]); j++) {
            		if (check(paragraphs[i])){
                		paragraphs[i][0]=END;
                		(*deleted)++;
            		}
        	}
    	}
}

void output(char **paragraphs, int num, int deleted) {
  	for (int i = 0; i < num; i++) {
    		if (paragraphs[i][0] != '\0') {
		  	printf("%c", paragraphs[i][0]);	
      			for (int j = 1; j < strlen(paragraphs[i]); j++) {
				char ch = paragraphs[i][j - 1];
				if (ch != '.' && ch != ';' && ch != '?') {
					printf("%c", paragraphs[i][j]);
				}
			}
			printf("\n");
		}
  	}
  	printf("Количество предложений до %d и количество предложений после %d\n", num - 1, num - 1 - deleted);
}  

int check(char *str) {
        int len = strlen(str) - 1;
        int is_num = 1;
        for (int i = 1; i < len - 1; i++) {
                if (isalpha(str[i - 1])) {
                        is_num = 0;
                } else if (!isalpha(str[i - 1]) && !isdigit(str[i - 1])) {
                        is_num = 1;
                }
                if (!is_num && isdigit(str[i]) && (isdigit(str[i + 1]) || isalpha(str[i + 1])))
                        return 1;
        }
    return 0;
}
