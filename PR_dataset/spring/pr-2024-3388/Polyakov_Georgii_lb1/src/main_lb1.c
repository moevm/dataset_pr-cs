#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define SENTENCE_SIZE 150
#define LAST_SENTENCE "Fin."
#define REGULAR_EXPRESSION "([A-z0-9]+[A-z0-9]*:\\/\\/)?(www\\.)?(([A-z0-9]+[A-z0-9]*\\.)+([A-z]+))\\/([A-z0-9]+\\/)*([A-z0-9]+\\.[A-z0-9]+)"
#define MAX_GROUP 8
#define WEBSITE_GROUP 3
#define FILE_GROUP 7
void search_for_url(char** text,int text_length){
    regex_t regex_compilation;
    regmatch_t regex_group[MAX_GROUP];

    regcomp(&regex_compilation, REGULAR_EXPRESSION, REG_EXTENDED);
    for (int text_index = 0; text_index<text_length; text_index++){
        if (regexec(&regex_compilation, text[text_index], MAX_GROUP, regex_group, 0) == 0){
            for (int group_ind = 0; group_ind<=MAX_GROUP; group_ind++){
                if (group_ind == WEBSITE_GROUP || group_ind == FILE_GROUP){
                    for(int j=regex_group[group_ind].rm_so;j<regex_group[group_ind].rm_eo;j++){
                        printf("%c",text[text_index][j]);

                    }
                    if (group_ind==FILE_GROUP){
                        printf("\n");
                    }
                    else{
                        printf(" - ");
                    }
                }
            }
        }
    }
}
void data_input(){
    char** text = malloc(SENTENCE_SIZE*sizeof(char*));
    int text_index = 0;
    char* sentence = (char*)malloc(SENTENCE_SIZE*sizeof(char));
    char letter;
    int letter_index = 0;
    int size_sentence = SENTENCE_SIZE;

    while(strcmp(sentence,LAST_SENTENCE)){
        if (letter_index == size_sentence-1){
            size_sentence += SENTENCE_SIZE;
            sentence = (char*)realloc(sentence, size_sentence*sizeof(char));
        }
        letter = getchar();

        sentence[letter_index] = letter;
        letter_index++;
        if (letter== '\n'){
            sentence[letter_index]='\0';
            text[text_index] = sentence;
            text_index+=1;
            sentence = (char*)calloc(size_sentence, sizeof(char));
            letter_index = 0;
        }
    }
    search_for_url(text, text_index);
}
int main(){
    data_input();
    return 0;
}
