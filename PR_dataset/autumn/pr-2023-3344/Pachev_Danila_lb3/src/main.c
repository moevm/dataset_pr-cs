#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char check_sentence(char* sentence, int len);

int main(void){
    int count_sentences = 0;
    int count_sentences_before = 0;
    char **text = (char**)malloc(sizeof(char*));
    while (1){
        int len_sentence = 0;
        char *sentence = (char*)malloc(sizeof(char));
        char ch='0';
        while (ch!='.' && ch!=';' && ch!='?' && ch!='!'){
            ch = getchar();
            sentence[len_sentence++]=ch;
            sentence = (char*)realloc(sentence,sizeof(char)*(len_sentence+1));
        }
        sentence[len_sentence]='\0';
        // убираем пробелы и табуляцию в начале предложения
        if (sentence[0]==' ' || sentence[0]=='\t'){
            memmove(sentence, sentence+1, strlen(sentence));
        }
        if (strstr(sentence, "Dragon flew away!")){
            text[count_sentences] = sentence;
            break;
        }
        
        // проверяем на наличие цифр внутри слов предложения, если нет таких случаев, то добавляем в массив
        if (check_sentence(sentence, len_sentence)==0){
            text[count_sentences++] = sentence;
            count_sentences_before++;
            text = (char**)realloc(text, sizeof(char*)*(count_sentences+1));
        }
        else
            count_sentences_before++;
    }
    for (int i = 0; i<=count_sentences;i++){
        printf("%s\n",text[i]);
        free(text[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d",count_sentences_before,count_sentences);
    free(text);
    return 0;
}

char check_sentence(char* sentence, int len){
    char* copy_sent = malloc(sizeof(char)*(len+1));
    strcpy(copy_sent, sentence);
    char* token = strtok(copy_sent, " ");
    char digit_in_word_flag = 0;
    
    while (token != NULL) {
        int first_letter_in_word=0;
        int last_letter_in_word=0;
        char first_flag = 0;
        for (int j = 0; j<strlen(token);j++){
            if (isalpha(token[j])){
                if (first_flag==0){
                    first_flag = 1;
                    first_letter_in_word = j;
                }
                else
                    last_letter_in_word = j;
            }
            
        }

        // если слово состоит из цифр - ничего не делаем, иначе - проверяем на наличие цифр внутри слова
        if (first_letter_in_word==0 && last_letter_in_word==0 && isdigit(token[0])){}
        else{
            for (int k = first_letter_in_word; k<=last_letter_in_word;k++){
                if (isdigit(token[k])){
                    digit_in_word_flag = 1;
                }
            }
        }
        token = strtok(NULL, " ");
    
    }
    free(copy_sent);
    return digit_in_word_flag;
}
