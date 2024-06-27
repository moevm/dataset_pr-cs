#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_end_of_sentence(int letter);
int is_555_in_sent(char *sent, int len);


int main() {

    char **main_array = malloc(sizeof(char *));
    int start_count_sent = 0, count_sent = 0;

    while (1) {

        char *sub_array = malloc(sizeof(char));
        char letter = 1;
        int len_arr = 0;

        // Чтение символов
        while (!is_end_of_sentence(letter)) {

            letter = getchar();

            sub_array[len_arr++] = letter;
            sub_array = realloc(sub_array, sizeof(char) * (len_arr + 1));

        }

        // Завершение строки
        sub_array[len_arr] = '\0';
        start_count_sent++;

        // Проверка на наличие 555 в предложении и запись предложения в основной массив
        if (!is_555_in_sent(sub_array, len_arr)) {

            /* Удаление пробелов и табуляций в начале предложений и
             добавление переноса строки в случае его отсутствия */
            if (strchr(" \t", sub_array[0])) {
                if (sub_array[1] == '\n') {
                    memmove(sub_array, sub_array + 1, strlen(sub_array));
                } else {
                    sub_array[0] = '\n';
                }
            }

            main_array[count_sent++] = sub_array;
            main_array = realloc(main_array, sizeof(char *) * (count_sent + 1));
        }

        // Остановка цикла при вводе последнего предложения
        if (strstr(sub_array, "Dragon flew away!")) break;

    }

    // Вывод скорректированного текста и очистка памяти
    for (int i = 0; i < count_sent; i++) {
        printf("%s", main_array[i]);
        free(main_array[i]);
    }
    printf("\nКоличество предложений до %d и количество предложений после %d", start_count_sent - 1, count_sent - 1);

    free(main_array);

}


int is_555_in_sent(char *sent, int len) {
    int count = 0;
    int left_pos = 0, right_pos = 0;
    for (int i = 0; i < len - 4; i++) {
        if (strchr(" \n\t" ,sent[i]) && sent[i+1] == '5' && sent[i+2] == '5' && sent[i+3] == '5' && strchr(" \n\t.;?", sent[i+4])) return 1;
    }

    return 0;
}


int is_end_of_sentence(int letter) {
    if (strchr(".;?!", letter)) {
        return 1;
    }

    return 0;
}