#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN 10
#define TERMINATING_PHRASE "Dragon flew away!"

void read_input(char** array, int* size) {
    *array = (char*)malloc(*size * sizeof(char)); // выделение памяти для массива

    if (*array == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }

    int count = 0; // количество символов в массиве
    char ch;
    while ((ch = getchar()) != '\n') { // считываем символы с клавиатуры
        (*array)[count] = ch;
        count++;

        if (count >= *size) { // если массив заполнен, увеличиваем его размер
            *size *= 2;
            *array = (char*)realloc(*array, *size * sizeof(char)); // перевыделяем память
            if (*array == NULL) {
                printf("Ошибка перевыделения памяти\n");
                exit(1);
            }
        }
    }
}

void format_text(char* array, int* proposals_before_editing, int* sentences_after_editing) {
    for(int i = 0; i < strlen(array); i++ )
    {
        if(isspace(array[i]) && (array[i-1]=='.' || array[i-1]==';' || array[i-1]=='?')) 
        {
            array[i] = '\n';
            (*proposals_before_editing)++;
        }
    }

    char dot_sign[] = "\n";
    char *istr;
    istr = strtok(array, dot_sign);
    while(istr != NULL)
    {
        if(strstr(istr, " 555 ") == NULL && strstr(istr, "555;") == NULL && strstr(istr, "555.") == NULL && strstr(istr, "555?") == NULL && strstr(istr, "555 ") == NULL)
        {
            printf("%s\n", istr);
            (*sentences_after_editing)++;
        }
        istr = strtok(NULL, dot_sign);
    }
}

int main() 
{
    char *array = NULL;
    int size = LEN; // начальный размер массива
    int proposals_before_editing = 0;
    int sentences_after_editing = 0;

    read_input(&array, &size);
    
    format_text(array, &proposals_before_editing, &sentences_after_editing);

    printf("Количество предложений до %d и количество предложений после %d\n", proposals_before_editing, sentences_after_editing-1);
    free(array); // Освобождаем память

    return 0;
}