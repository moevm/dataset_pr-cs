#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* text;
    size_t len;
} Text;

int countsentences(const char* input_string) {
    int cnt = 0;
    for (int i = 0; input_string[i] != '\0'; i++) {
        if ((input_string[i] == '.') | (input_string[i] == '?') | (input_string[i] == '!') | (input_string[i] == ';')){
            cnt += 1;
        }
    }
    return cnt;
}

char** split(const Text input) {
    char* text_copy = strdup(input.text);
    char** a = malloc(countsentences(text_copy) * sizeof(char*));// Массив, хранящий указатели на предложения

    int cursentence = 0;
    a[cursentence] = text_copy; // Указатель на первое предложение


    for (int i = 0; text_copy[i] != '!'; i++){ // Вместо пробелов после разделителей вставляем \0 и добавляем в массив указателей указатель на следующее предложение
        if ((text_copy[i] == '.') | (text_copy[i] == ';') | (text_copy[i] == '?')){
            text_copy[i + 1] = '\0';
            a[++cursentence] = &text_copy[i + 2];
        }
    }

    return a;
} 

int main() {
    Text input;
    input.text = malloc(10);
    input.len = 0;
    while (1){  // ввод строки
        input.text[input.len] = getchar();
        input.len += 1;
        if (input.len % 10 == 9){
            input.text = realloc(input.text, input.len + 11);
        } 
        
        if (input.text[input.len-1] == '!') {
            input.text[input.len] = '\0';
            break;
        }
    }
    
    char** sentences = split(input);

    int newcnt = 0;
    for (int i = 1; i < countsentences(input.text); i++){
        if (*(sentences[i] - 2) != '?'){
            printf("%s\n", sentences[i - 1]);
            newcnt++;
        }
    }   
    printf("%s\n", sentences[countsentences(input.text) - 1]);
    printf("Количество предложений до %d и количество предложений после %d\n", countsentences(input.text) - 1, newcnt);

    free(sentences[0]);
    free(input.text);
    return 0; 
}           