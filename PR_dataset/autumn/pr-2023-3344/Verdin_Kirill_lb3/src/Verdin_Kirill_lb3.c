#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    
    char** text = malloc(1*sizeof(char*));
    int all_sentences = 0;
    int current_sentences = 0;
    
    while(1){
        all_sentences++;
        int count_chars = 0;
        char* sentence = malloc(1*sizeof(char));
        int is_seven = 0;
        char ch = 'o';

        while (ch != ';' && ch != '!' && ch != '.' && ch != '?'){
            ch=getchar();
            
            if (ch == '7'){
                is_seven = 1; //проверка на то, является ли символ 7-ой
            }
            sentence[count_chars++] = ch;
            sentence = realloc(sentence, (count_chars + 1) * sizeof(char)); //установка нового количества выделенных байтов для предложения
        }
        sentence[count_chars] = '\0';
        
        if (sentence[0] == ' ' || sentence[0] == '\n'){
            memmove(sentence, sentence + 1, strlen(sentence));
        }

        if (is_seven==0){
        text[current_sentences++]=sentence;
        text=realloc(text, (1+current_sentences)*sizeof(char*)); //установка нового количества выделенной памяти для текста(массива указазателей)
        }
        
        if (strstr(sentence, "Dragon flew away")) {
            break;
        }
    }
    
    for(int i=0; i<current_sentences; i++){
        printf("%s\n", text[i]);
        free(text[i]);
        }
        
    free(text);
    printf("Количество предложений до %d и количество предложений после %d\n", all_sentences-1, current_sentences-1);
    return 0;
}