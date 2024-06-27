#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXTRA_BUF 50

char* readSentence(){
    char *tmp = (char*)malloc(sizeof(char));
    char *sentence;
    if (tmp) { //проверка на возможность выделения памяти
        sentence = tmp;
        tmp = NULL;
    }
    char c;
    int capacity = 1;
    int len = 0;
    while(c = getchar()){
        if(len >= capacity){ //проверяем, нужна ли дополнительная память
            capacity += EXTRA_BUF;
            tmp = (char*)realloc(sentence, capacity*sizeof(char));
            if (tmp){ //проверка на возможность выделения доп памяти
                sentence = tmp;
                tmp = NULL;
            }
        }

        if (c == '!') {
            sentence[len] = c;
            sentence[++len] = '\0';
            if (strcmp(sentence, "Dragon flew away!") == 0)
                return sentence;
        }

        if (len >= 1 || c != ' ' && c != '\t' && c != '\n') //убирание лишних символов в начале строки
            sentence[len++] = c;

        if (c == '.' || c == ';' || c == '?')
            break;
    }
    sentence[len] = '\0';
    return sentence;
}

int formatText(char **text, int size){ //удаление строки с ? из массива
    int new_size = size;
    for (int i = 0; i < new_size; ++i){
        if (strchr(text[i], '?')){
            free(text[i]); // очищение памяти строки с ?

            for (int j = i; j < new_size - 1; ++j){ // смещение элементов массива влево
                text[j] = text[j+1];
            }
            new_size--;
            i--; // для проверки только что сместившийся строки
        }
    }

    char **tmp = (char**)realloc(text, sizeof(char *) * new_size); // уменьшение массива до new_size
    if (tmp){
        text = tmp;
        tmp = NULL;
    }
    return new_size;

}

char** readText(int *size){ // создание массива указателей
    char **text = (char**)malloc(sizeof(char*));
    char *s;
    int count = 0;
    while(s = readSentence()){
        text[count++] = s;
        text = (char**)realloc(text, sizeof(char*)*(count+1)); // увеличение массива для нового указателя
        if (strcmp(s, "Dragon flew away!") == 0)
            break;
    }
    *size = count;
    return text;
}

int main(){
    int size;
    char** text = readText(&size);
    int after_size = formatText(text, size);
    for (int i = 0; i < after_size; ++i) {
        puts(text[i]);
        free(text[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d\n", size - 1, after_size - 1);
    free(text);
    return 0;
}
