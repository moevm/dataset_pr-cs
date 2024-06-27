#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//функция проверки наличия "7" в предложении
int if_seven_in_string(char* string){

    for (int i = 0; i < strlen(string); i++){
        if (string[i] == '7'){
            return 1;
        }
    }

    return 0;
}



int main(){

    //выделяем память под массив предложений
    char** string_array = (char**)malloc(sizeof(char*));
    //счетчики предложений до и после работы программы
    int string_count = 0;
    int changed_string_count = 0;

    while(1){

        //выделяем память под массив символов
        char* symbols_array = (char*)malloc(sizeof(char));
        //счетчик длины предложения и текущий символ
        int len_count = 0;
        char symbol = '1';

        //чтение строки и увеличение памяти под каждый следующий символ
        while(symbol != '.' && symbol != ';' && symbol != '?' && symbol != '!'){

            symbol = getchar();
            symbols_array[len_count++] = symbol;
            symbols_array = realloc(symbols_array, sizeof(char)*(len_count + 1));

        } 

        //окончание считанной строки
        symbols_array[len_count] = '\0';

        //проверка на "7"
        if (if_seven_in_string(symbols_array) == 0){
            
            //убираем табуляцию/пробел в начале строки, путем сдвига массива символов на 1 элемент в сторону младших разрядов
            if(symbols_array[0] == ' ' || symbols_array[0] == '\t'){

                memmove(symbols_array, symbols_array + 1, strlen(symbols_array));

            }

            //запись строки в массив строк, если "7" отсутствует и +1 к счетчику "после"
            string_array[changed_string_count++] = symbols_array;
            //увеличиваем память под следующую строку в массиве строк
            string_array = realloc(string_array, sizeof(char*) * (changed_string_count + 1));
            //+1 к счетчику предложений "до"
            string_count++;
            
            //если это конечное предложение, то завершаем цикл
            if (strstr(symbols_array, "Dragon flew away!")){
                break;
            }

        } else{
            
            //иначе просто +1 к сетчику предложений "до"
            string_count++;

        }
        
    }

    //выводим измененный текст и очищаем память массива строк
    for(int i = 0; i < changed_string_count; i++){

        printf("%s\n", string_array[i]);
        free(string_array[i]);

    }

    free(string_array);

    //выводим результат счетчиков "до" и "после"
    printf("Количество предложений до %d и количество предложений после %d", string_count - 1, changed_string_count - 1);

    return 0;

}