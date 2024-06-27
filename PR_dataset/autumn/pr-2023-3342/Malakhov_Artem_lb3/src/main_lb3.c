#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 10
#define FINAL_OUTPUT "Количество предложений до %d и количество предложений после %d\n"

int check_num_of_capital(char *sentence)
{
	size_t len = strlen(sentence);
    int capital_count = 0;
    for(int i = 0; i < len; i++){
        if (sentence[i] >= 'A' && sentence[i] <= 'Z'){
            capital_count++;
        }
    }
    if (capital_count > 1)
        return 1;
    return 0;    

}

char* get_sentence(char *end_of_sentence)
{
	size_t length = 0, capacity = BLOCK_SIZE;
	char* sentence = malloc(sizeof(char) * capacity);
	char ch;
	while (ch = getchar()) {
		if (length >= capacity-1){
			capacity += BLOCK_SIZE;
			sentence = realloc(sentence, sizeof(char) * capacity);
		}
		if(!sentence)
			return NULL;
		
		if (ch == '\t' || ch == '\n' || ((ch == ' ') && (length == 0))) 
			continue; 
		sentence[length] = ch; 
		length++;
		if(ch == '.' || ch == ';' || ch == '?' || ch == '!'){
			*end_of_sentence = ch;
        	break;
		}
	}	
	sentence[length] = '\0';
	return sentence;
}

char** get_format_text(int *num_of_sen, int *num_of_sen_after){
	char** text = malloc(BLOCK_SIZE * sizeof(char*));
	size_t size_text = 0, capacity = BLOCK_SIZE;
	char last_ch_of_sen;
	int num_of_bad_sen = 0;

	while (1){
		if (size_text >= capacity - 1){
			capacity += BLOCK_SIZE;
			text = realloc(text, sizeof(char*) * capacity);
		}	
		if (!text)
			return NULL;	
		text[size_text++] = get_sentence(&last_ch_of_sen);
		if (last_ch_of_sen == '!')
			break;
		if (check_num_of_capital(text[size_text-1])){
			++num_of_bad_sen;
			free(text[size_text - 1]);
			text[size_text - 1] = NULL;
		}			
	}
	*num_of_sen = size_text - 1;
	*num_of_sen_after = *num_of_sen - num_of_bad_sen;
	return text;
}

void complete_clean(char **text, int num_of_sen)
{
   for(int i = 0; i < num_of_sen; i++){
       if (text[i] != NULL)
           free(text[i]);
   }
   free(text);
}

int main(){
	int n = 0, m = 0;
	char **text = get_format_text(&n, &m);
	for (int i =0; i <= n; ++i)
		if (text[i] != NULL)
			printf("%s\n", text[i]);
	printf(FINAL_OUTPUT, n, m);
	complete_clean(text, n);
	return 0;
}