#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TEXT_SIZE 100
#define EXAMPLE 10

int readText(char **text);
int isFive( char *sentence);
char** splitting(char* text, int* count_sentence);

int main() {
    char** text = (char**)malloc(sizeof(char*));
    int count_of_sentences = readText(text);
    int new_count_of_sentences = 0;
    char** new_text = splitting(*text,&new_count_of_sentences);
    //printf("------------------\n");
    for (int i = 0; i < new_count_of_sentences; i++){
        
        for (int j = 0; j < strlen(new_text[i]); j++){
            
            if (new_text[i][j] != '\t' || new_text[i][j] != '\n') {
                printf("%c", new_text[i][j]);
            }
        }
        
        printf("\n");
    }
    
    printf("Dragon flew away!\n");
    printf("Количество предложений до %i и количество предложений после %i", count_of_sentences, new_count_of_sentences);
    free(text);
    free(new_text);
    
return 0;

}



int readText(char **text){
    int size = TEXT_SIZE;
    char *buf = (char*)malloc(size*sizeof(char));
    int n=0;
    int count_sentence = 0;
    char temp;
    
    do{
        if(n >= size-2){
            char *t = (char*)realloc(buf, size+TEXT_SIZE);
            size+=TEXT_SIZE;
            buf = t;
        }
        temp = getchar();
        if (temp=='.' || temp==';' || temp=='?') 
            count_sentence++;
        buf[n]= temp;
        n++;
    }while(temp!='!');
    
    buf[n]= '\0';
    *text = buf;
    
    
    return count_sentence;
}

int isFive(char* sentence) {
char* sentence1 = strdup(sentence);
char* word = strtok(sentence1, " "); // разбиваем предложение на отдельные слова

while (word != NULL) {
    if (strcmp(word, "555") == 0 || strcmp(word, "555.") == 0 || strcmp(word, "555;") == 0 || strcmp(word, "555?") == 0) 
        {
        return 1; 
        }
    word = strtok(NULL, " "); // переходим к следующему слову
}

return 0; 
}


char** splitting(char* text, int* count_of_sentence) {
    int len_text = strlen(text);
    int capacity = EXAMPLE;
    char** new_text = (char**)malloc(capacity * sizeof(char*));
    int start = 0;
    
    for (int i = 0; i < len_text; i++) {
        if (text[i] == '.' || text[i] == ';' || text[i] == '?') 
        {
            if (text[start] == ' ') 
            {
                start++;
            }
            int len_sentence = i - start + 2;
            char* sentence = (char*)malloc((len_sentence) * sizeof(char));
            strncpy(sentence, text + start, len_sentence - 1);
            sentence[len_sentence-1] = '\0';
            
            if (isFive(sentence) == 0) 
            {
                if (*count_of_sentence >= capacity)
                {
                    capacity += EXAMPLE;
                    new_text = (char**)realloc(new_text, capacity * sizeof(char*));
                }
                
                new_text[*count_of_sentence] = sentence;
                (*count_of_sentence)++;
            } 
            else 
            {
                free(sentence);
            }
            start = i + 1;
        }
    }
    return new_text;
}
