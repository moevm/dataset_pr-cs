#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<regex.h>

#define BUFFER_SIZE 500
#define STOP_INPUT "Fin."
#define COUNT_GROUPS 8
#define NUMBER_DOMEN_GROUP 3
#define NUMBER_FILE_GROUP 7
#define REGULAR_EXPRESSION "([A-z0-9]+[A-z0-9]*:\\/\\/)?(www.)?(([A-z0-9]+[A-z0-9]*\\.)+([A-z]+))\\/([A-z0-9]+\\/)*([A-z0-9]+\\.[A-z0-9]+)"

char ** input_text(int * count_sentences);

char  ** input_text(int * count_sentences){
    char  ** text  = calloc(BUFFER_SIZE,sizeof(char*));
    char * current_sentence;
    do{
        current_sentence = calloc(BUFFER_SIZE,sizeof(char));
        fgets(current_sentence, BUFFER_SIZE, stdin);
        text[(*count_sentences)++] = current_sentence;
    }while (strncmp(current_sentence, STOP_INPUT, strlen(STOP_INPUT)));
    return text;
}

void found_url_func(char ** text, int * count_sentences);

void found_url_func(char ** text, int * count_sentences)
{
    regex_t regex_compiled;
    regmatch_t group_array[COUNT_GROUPS];
    regcomp(&regex_compiled, REGULAR_EXPRESSION, REG_EXTENDED);
    for(int k = 0 ; k < *count_sentences; k++){
        if (regexec(&regex_compiled, text[k], COUNT_GROUPS, group_array, 0) == 0){
            for (int i = 0; i <= COUNT_GROUPS; i++){
                if(i == NUMBER_DOMEN_GROUP || i == NUMBER_FILE_GROUP){
                    for(int j = group_array[i].rm_so;j < group_array[i].rm_eo; j++){
                    	printf("%c",text[k][j]);
                    }
                    if(i == NUMBER_DOMEN_GROUP){
	                    printf(" - ");
                    }else{
                    	printf("\n");
                    }
                }
            }
        }
    }
    regfree(&regex_compiled);
}

int main (){
    int count_sentences = 0;
    char ** text = input_text(&count_sentences);
    found_url_func(text, &count_sentences);
    for (size_t i = 0; i < (size_t)count_sentences; i++){
    	free(text[i]);
    }
    free(text);
    return 0;
}
