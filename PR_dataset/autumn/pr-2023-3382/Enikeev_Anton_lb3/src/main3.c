#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 100
#define STEP 20

int is_valid_word(char *word) { /*эта функция предназначена для проверки слов в строке на наличие цифр и проверку их расположения относительно начала и конца слова*/
     if (strlen(word) == 1) {return 0;}
     int digitInsideWord = 0;
     int word_len;
     int first = 0, second = 0, ind_ch;
     if (word[strlen(word) - 1] == ';' || word[strlen(word) - 1] == '.' || word[strlen(word) - 1] == '?' || word[strlen(word) - 1] == ',' || word[strlen(word) - 1] == '\n') {
         word_len = strlen(word) - 2;
     }
     else word_len = strlen(word) - 1;
     if (isdigit(word[0])) first = 1;
     if (isdigit(word[word_len])) second = 1;
     for (int i = 1; i < word_len; i++){
         if (isdigit(word[i])) {
             digitInsideWord = 1;
             ind_ch = i;
             break;
         }
     }
     if (digitInsideWord == 0) {return 0;}
     else if (first == 0 && second == 0) {return 1;}
     else if (first == 1 && second == 1) {return 0;}
     else if (first == 1 && second == 0){
          for (int j = 0; j < ind_ch; j++){
               if (!isdigit(word[j])) {return 1;}
          }
     }else if (first == 0 && second == 1){
         for (int j = ind_ch; j < word_len; j++){
             if (!isdigit(word[j])) { return 1;}
         }
     }
     return 0;
}

void* checkNull(void* ptr){ //проверяем, что не произошло ошибки при выделении памяти
    if (ptr == 0){
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    return ptr;
}

int main(){
    int st = 0, end = 0; //изначальное кол-во предложений и итоговое 
    char *s = (char *)checkNull(malloc(N)); //выделение памяти на 1 предложение
    char c; //текущий символ
    int size = N;
    int len = 0; //длина предложения
    int flag = 1;  // Флаг для проверки на ошибку
    while (1){
        while(1){
            c = getchar(); //считваем текущий символ
            if (c == '\n') {continue;}
            if ((isblank(c) && len == 0)){ continue;} //убираем таким образом таб в начале предложения;
            if (len > size){ //если веделенной изначально памяти не хватило, выделим новую большего размера
                s = (char *)checkNull(realloc(s, sizeof(char) * (size+STEP)));
                s[len] = c;
                s[len + 1] = '\0';
                size += STEP;
                len++;
            }else{ s[len] = c; s[len+1] = '\0'; len++;}
            if (c == '.' || c == ';' || c == '?') {break;}
            if (c == '!') {break;}
        }
        if (s[0] == '\0') {continue;}
        char* time_s = checkNull(malloc(sizeof(char)*(size)));
        strcpy(time_s, s); //копируем исходную строку, чтобы потом не изменять её 
        char* token = strtok(time_s, " "); // Разбиваем строку на отдельные слова
        
        while (token != NULL) { //пробегаемся по токенам
            if (is_valid_word(token)) {flag = 0;}
            if (flag == 0) {break;}
            token = strtok(NULL, " ");
        }
        free(time_s);
        st++;
        if (flag == 1){
            end++;
            printf("%s\n", s);
        }
        flag = 1;
        len = 0;
        if (strcmp(s, "Dragon flew away!") == 0) {break;} //последнее предложение
        s[0] = '\0';
        size = N;
    }
    printf("Количество предложений до %d и количество предложений после %d", st - 1, end - 1);
    free(s);
    return 0;
}

            

            
