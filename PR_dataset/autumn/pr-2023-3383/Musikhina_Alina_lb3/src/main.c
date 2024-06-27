#include <malloc.h>
#include <string.h>
#include "stdio.h"
char const* END_STR = "Dragon flew away!";

int is_edge(char c){ // Проверка на границу слова
    return c == ' ' || c == '\n' || c== ';' || c == '.' || c == '?' || c == '!';
    // return !is_number(c) && !is_symbol(c) // Опционально
}

int is_number(char c){
    if((int) c >= '0' && (int) c <= '9')
        return 1;
    return 0;
}

int is_symbol(char c){
    if((int) c >= 'A' && (int) c <= 'Z')
        return 1;
    if((int) c >= 'a' && (int) c <= 'z')
        return 1;
    return 0;
}

int main(void){
    char* str = (char*) malloc(100 * sizeof(char)); // Хранится весь текст
    //char* new_str; // Новая строка входных данных
    int flag = 0; // 1 если есть слово с числом внутри
    int j = 0; // индекс начала предложения
    int counter = 0; // счетчик пробелов
    int number_counter = 0; // счетчик для проверки на цифру внутри
    int n = 0, m = 0;
    size_t size = 100;
    size_t length = 0;

    // "             (null_ptr)"
    // null_ptr = 10
    while(strcmp(str + length - strlen(END_STR), END_STR) != 0){
        char c;
        scanf("%c", &c);
        if(length >= size){
          str = (char*) realloc(str, length * 2 * sizeof(char));
          size *= 2;
        }
        str[length++] = c;
    }


    for(int i = 0; i < length - 1; i++){ // Подсчет n до изменений
        if(str[i] == '.' || str[i] == '?' || str[i] == ';')
            n++;
    }

    m = n;

    for(int i = 0; i < length - 1; i++){ // Разделяет предложения по /n и удаляет w4e
        if((str[i] == '.' || str[i] == '?' || str[i] == ';')){ // Процесс удаления
            str[i+1] = '\n';
            if(flag == 1){ // flag == 1 -> надо удалять                m--;
                flag = 0;
                m--;
                for(int k = j; k < i + 2; k++){
                    str[k] = ' ';
                }
            }
            j = i + 2;
        }

        // Проверка на удаление
        if(number_counter == 0 && is_symbol(str[i]) == 1)
            number_counter++;
        else if(number_counter == 1 && is_number(str[i]) == 1) // Есть цифры среди букв
            number_counter++;
        else if(number_counter == 2 && is_symbol(str[i]) == 1)
            flag = 1;
        if(is_edge(str[i]) == 1) // Сброс счетчика при переходе на новое слово
            number_counter = 0;
    }



    j = 0; // Индекс начала предложения
    flag = 1; // flag == 1 -> Мы в начале предложения

    char* result = (char*) malloc(strlen(str)*sizeof(char)+1);
    
    for(int i = 0; i < length; i++){ // Удаление пробелов
        if((str[i] == ' ' || str[i] == '\n')  && flag == 1) // Считает количество пробелов
            counter++;
        else
            flag = 0;

        if(str[i] == '.' || str[i] == '?' || str[i] == ';' || str[i] == '!'){ // Удаляет пробелы когда доходит до конца
            // Hello.    World.   asd!
            //       j c      i
            strncat(result, str+j+counter, i-j-counter+2);
            result[strlen(result) - 1] = '\n';
            j = i + 1;
            flag = 1;
            counter = 0;
        }
    }
    result[strlen(result) - 1] = '!';
    printf("%s\n", result);
    printf("Количество предложений до %d и количество предложений после %d", n, m);
    free(str);
    free(result);
    return 0;
}
