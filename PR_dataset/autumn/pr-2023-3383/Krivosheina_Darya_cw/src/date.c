#include "date.h"
#include "struct.h"

void date(struct Text our_text){
    int count_words = 1; // для подсчета количества слов
    int length = 0;  // для длины каждого слова
    int month = 0;  // для длины максимального слова
    for (int p = 0; p < our_text.len; p++){  
        count_words = 1;  // обнуление переменных при переходе к новому предложению
        length = 0;
        month = 0;
        for (int p1 = 0; p1 < wcslen(our_text.text[p]) - 1; p1++){
            length++; // увеличение длины слова при переходе к новому символу
            if (our_text.text[p][p1] != ' ' && our_text.text[p][p1] != ',' && (our_text.text[p][p1 + 1] == ' ' || our_text.text[p][p1 + 1] == ',' || our_text.text[p][p1 + 1] == '.')){  // условие, выявляющее конец слова (нужно для поиска месяца)
                if (length > month){  // изменение значения месяца, если новое слово длиннее прошлого рекордсмена
                    month = length;
                }
                length = 1;  // обнуление длины для нового подсчета
            }
            if (our_text.text[p][p1] != ' ' && (our_text.text[p][p1 - 1] == ' ' || our_text.text[p][p1 - 1] == ',') && our_text.text[p][p1] != '.' && our_text.text[p][p1] != ','){  // условие, выявляющее начало слова (нужно для подсчета слов и обнуления длины при встрече нового слова) 
                length = 1;
                count_words++;
            }
        }
        int day = count_words;
        int year = 1900 + wcslen(our_text.text[p]); 
        if (day < 10){  // приведение даты в необходимый вид за счет добавления нулей где необходимо
            if (month < 10){
                wprintf(L"0%d-0%d-%d\n", day, month, year);
            } else {
                wprintf(L"0%d-%d-%d\n", day, month, year);
            }
        } else {
            if (month < 10){
                wprintf(L"%d-0%d-%d\n", day, month, year);
            } else {
                wprintf(L"%d-%d-%d\n", day, month, year);
            }
        }
    }
}

