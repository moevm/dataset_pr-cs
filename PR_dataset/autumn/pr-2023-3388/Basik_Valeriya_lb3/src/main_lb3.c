#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define BUFF_SIZE 16

int findIndex(char *string, char *symbol);

int findSepIndex(char *string, int start);

int upperCount(char *string);

int main() {
    processinput();
    return 0;
}

void processinput(){
    //Cчетчики предложений
    int sentenceCount = 0;
    int trashCount = 0;

    //Буферы для ввода и текущего предложения
    int maxSentenceSize = BUFF_SIZE;
    char *buffer = calloc(BUFF_SIZE, sizeof(char));
    char *sentence = calloc(maxSentenceSize, sizeof(char));

    //Обработка ввода
    while (fgets(buffer, BUFF_SIZE, stdin) != NULL) {
        int sIndex = 0;

        //Перенос значений буфера в предложения
        while (TRUE) {
            unsigned int endIndex = findSepIndex(buffer, sIndex);

            //Предложение тут не кончается
            if (endIndex == -1) {
                maxSentenceSize += BUFF_SIZE;
                char *temp = realloc(sentence, maxSentenceSize * sizeof(char));
                if (temp) sentence = temp;

                strcat(sentence, sIndex + buffer);
                break;
            }

            //Удаление двойного пробела при конкатенации
            if (sentence[strlen(sentence) - 1] == ' ' && buffer[sIndex] == ' ')
                sIndex++;

            strncat(sentence, buffer + sIndex, endIndex - sIndex + 1);

            if (upperCount(sentence) > 1) {
                memset(sentence, 0, BUFF_SIZE);
                trashCount++;
                sIndex = endIndex + 1;
                continue;
            }

            //Вывод текущего преложения
            short startSentence = 0;
            if (isspace(sentence[strlen(sentence) - 1])) sentence[strlen(sentence) - 1] = '\0';
            if (isspace(sentence[0])) startSentence = 1;

            printf("%s\n", startSentence + sentence);

            //Окончание вывода на териминальном предложении
            if (strstr(sentence, "Dragon flew away!")) {
                break;
            }

            //Подготовка переменных к следующей итерации
            memset(sentence, 0, maxSentenceSize);
            maxSentenceSize = BUFF_SIZE;
            char *temp = realloc(sentence, maxSentenceSize);
            if (temp) sentence = temp;

            sentenceCount++;
            sIndex = endIndex + 1;
        }
    }


    char *formatStr = "Количество предложений до %d и количество предложений после %d";
    printf(formatStr, trashCount + sentenceCount, sentenceCount);

    //Освобождение памяти и завершение программы
    free(buffer);
    free(sentence);
    return 0;
}


int upperCount(char *string) {
    int counter = 0;
    for(int i = 0; i < strlen(string); i++)
        if (isupper(string[i])) counter++;

    return counter;
}


int findIndex(char *string, char *symbol) {
    char *ptr = strstr(string, symbol);

    if (ptr == NULL) return -1;
    return ptr - string;
}

//Возвращает индекс ближайшего конеца предложения
int findSepIndex(char *string, int start) {
    unsigned int dotIndex = findIndex(string + start, ".");
    unsigned int semicolonIndex = findIndex(string + start, ";");
    unsigned int exclamationIndex = findIndex(string + start, "!");
    unsigned int questionIndex = findIndex(string + start, "?");

    if (dotIndex == -1 && semicolonIndex == -1 && exclamationIndex == -1 && questionIndex == -1)
        return -1;

    int sepIndex = semicolonIndex;
    if (dotIndex < semicolonIndex) sepIndex = dotIndex;
    if (exclamationIndex < sepIndex) sepIndex = exclamationIndex;
    if (questionIndex < sepIndex) sepIndex = questionIndex;

    return start + sepIndex;
}
