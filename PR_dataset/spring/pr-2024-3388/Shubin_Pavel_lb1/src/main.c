#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define SENTENCE_BASE_SIZE 100
#define TEXT_BASE_SIZE 10
#define END_STRING '\0'
#define FINISH "Fin."
#define MAX 8
#define WEBSITE 3
#define FILE 7
#define REGEX "([A-z0-9]+[A-z0-9]*:\\/\\/)?(www.)?(([A-z0-9]+[A-z0-9]*\\.)+([A-z]+))\\/([A-z0-9]+\\/)*([A-z0-9]+\\.[A-z0-9]+)"


void find_right_links(char*** text, int text_size){
    regex_t regex_compiled;
   regcomp(&regex_compiled, REGEX, REG_EXTENDED);
   regmatch_t match_group[MAX];
   
    for(int ind = 0 ; ind < text_size; ind++){
       if (regexec(&regex_compiled, (*text)[ind], MAX, match_group, 0) == 0){
                   for(int j = match_group[WEBSITE].rm_so;j < match_group[WEBSITE].rm_eo; j++){
                       printf("%c",(*text)[ind][j]);
                    }
                    printf(" - ");
                    for(int j = match_group[FILE].rm_so;j < match_group[FILE].rm_eo; j++){
                        printf("%c",(*text)[ind][j]);
                    }
                    printf("\n");
                  
               }
           }
   regfree(&regex_compiled);
}
void input_sentence(char* sentence,int* buf_len){
    int ind = 0;
    int flag = 1;
    char tmp_char = getchar();
    while(flag){
        if(ind == *buf_len - 1){
            *buf_len *=2;
            sentence = realloc(sentence, *buf_len*sizeof(char));
        }

        sentence[ind]= tmp_char;
        ind +=1;

        tmp_char = getchar();
        if(tmp_char == '\n'|| tmp_char == EOF || tmp_char == '\0'){
            flag = 0;
        }
    }
    sentence[ind] = END_STRING;
}
void input_text(char*** text,char* sentence, int* buf_len, int *text_size, int* buf_text_len){
    input_sentence(sentence, buf_len);
    while(strcmp(sentence, FINISH)){
        if((*text_size) == (*buf_text_len) - 1 ){
            (*buf_text_len)*=2;
            (*text) = realloc((*text), (*buf_text_len)*sizeof(char*));
        }
        (*text)[(*text_size)++] = strdup(sentence);
        input_sentence(sentence, buf_len);
    }

}
int main() {
    int buf_len = SENTENCE_BASE_SIZE;
    int buf_text_len = TEXT_BASE_SIZE;
    int text_size = 0;
    char* sentence = (char*)malloc(SENTENCE_BASE_SIZE*sizeof (char));
    char** text = (char**)malloc(TEXT_BASE_SIZE*sizeof(char*));
    input_text(&text, sentence, &buf_len, &text_size, &buf_text_len);
    find_right_links(&text, text_size);
   
    return 0;
}