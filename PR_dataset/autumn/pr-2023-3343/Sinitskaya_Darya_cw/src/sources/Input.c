#include"../include/Input.h"

//метод считывания текста
void Input(Text *text) {
    text->size = 0;  //инициализация размера массива предложений
    Sentence *sentences = NULL;
    sentences = malloc(sizeof(Sentence)*10);  //выделение памяти для первого предложения
    
    //обработка ошибки выделения памяти для первого предложения
    if(sentences == NULL){
    wprintf(L"Error: Memory allocation\n");
    free(sentences);
    return;
    }
    
    wchar_t *sentence = malloc(sizeof(wchar_t)*10);  //выделение памяти для первого символа предложения

    //обработка ошибки выделения памяти для первого символа предложения
    if(sentence == NULL){
    wprintf(L"Error: Memory allocation\n");
    free(sentences);
    }
    
    int sentence_size = 0;  //размер предложения
    wint_t c;  //переменная для считывания символов
    int flag = 1;  //флаг, указывающий на наличие пробела в начале предложения

    while ((c = getwchar())!= WEOF) {

        if (c == L'\n') { 

            c = getwchar();

            if (c == L'\n') { //проверка на конец текста
                break; 
            } else {

                sentence[sentence_size++] = c;  //добавление символа к предложению
                sentence = realloc(sentence, sizeof(wchar_t) * (sentence_size + 10));  //перевыделение памяти для предложения
                
                //обработка ошибки перевыделения памяти для предложения
                if(sentence == NULL){
    		        wprintf(L"Error: Memory allocation\n");
                    free(sentence);
                    free(sentences);
                    break;
  		        }

                flag = 0;  //обнуление флага пробела в начале предложения

            }

        } else {

            if (flag && c == L' ') { //проверка на пробел в начале предложения
                continue;  //игнорирование пробела в начале предложения
            }

            if (c == L'.') { //проверка на конец предложения

                sentence[sentence_size] = c;  //добавление символа к предложению
                sentence[sentence_size+1] = L'\0';  //завершение предложения
                sentence_size = 0;  //сбрасывание размера предложения
                text->size++;  //увеличение размера массива предложений
                sentences = realloc(sentences, sizeof(Sentence) * text->size);  //перевыделение памяти для массива предложений
                
                //обработка ошибки перевыделения памяти для массива предложений
                if(sentences == NULL){
   		            wprintf(L"Error: Memory allocation\n");
                    free(sentence);
                    free(sentences);
                    break;
    		    }

                sentences[text->size - 1].sentence = sentence;  //сохранение предложения в массиве
                sentence = malloc(sizeof(wchar_t)*10);  //выделение памяти для следующего предложения

                //обработка ошибки выделения памяти для следующего предложения
                if(sentence == NULL){
                    wprintf(L"Error: Memory allocation\n");
                    free(sentence);
                    free(sentences);
                    break;
                }

                flag = 1;  //устанавление флага пробела в начале предложения

            } else {

                sentence[sentence_size++] = c;  //добавление символа к предложению
                sentence = realloc(sentence, sizeof(wchar_t) * (sentence_size + 10));  //перевыделение памяти для предложения
                
                //обработка ошибки перевыделения памяти для предложения
                if(sentence == NULL){
                    wprintf(L"Error: Memory allocation\n");
                    free(sentence);
                    free(sentences);
                    break;
                }

                flag = 0;  //обнуление флага пробела в начале предложения

            }

        }

    }

    text->sentences = sentences;  //сохранение массива предложений в структуре Text
    free(sentence);  //освобождение памяти, выделенной для последнего предложения
}
