#ifndef stdio
#include <stdio.h>
#endif
#ifndef stdlib
#include <stdlib.h>
#endif
#ifndef ctype
#include <ctype.h>
#endif

#include "readtext.h"


size_t readtext(char ***sentences){
    *sentences = NULL;
    size_t cnt_sentences = 0;
    size_t cnt_chars = 0;
    short cnt_line_breaks = 1;
    short issentence = 0;
    char cur_char;
    
    while (1){
        cur_char = getchar();

        // Проверка на переносы строки
        if (cur_char == '\n'){
            cnt_line_breaks += 1;
            if (cnt_line_breaks == 2){
                if (issentence){
                    (*sentences)[cnt_sentences-1] = realloc((*sentences)[cnt_sentences-1], (cnt_chars+1)*sizeof(char));
                    (*sentences)[cnt_sentences-1][cnt_chars-1] = '.';
                    (*sentences)[cnt_sentences-1][cnt_chars] = '\0';
                    issentence = 0;
                    cnt_chars = 0;
                }
                break;
            }
        }
        else{
            cnt_line_breaks = 0;
        }

        // Проверка на неожиданные символы
        if (!isalnum(cur_char) && cur_char != '.' && cur_char != ',' && !isspace(cur_char)){
            printf("Error: Unexpected symbol\n");
            *sentences = NULL;
            return 0;
        }
        
        // Удаление первых пробельных символов и пустых предложений
        if (!issentence && (isspace(cur_char) || cur_char == '.')) continue;

        // Запись предложения
        if (issentence && cur_char == '.'){
            cnt_chars++;
            (*sentences)[cnt_sentences-1] = realloc((*sentences)[cnt_sentences-1], (cnt_chars+1)*sizeof(char));
            (*sentences)[cnt_sentences-1][cnt_chars-1] = cur_char;
            (*sentences)[cnt_sentences-1][cnt_chars] = '\0';
            issentence = 0;
            cnt_chars = 0;
            continue;
        }

        // Запись символа
        if (!issentence){
            cnt_sentences++;
            (*sentences) = realloc((*sentences), cnt_sentences*sizeof(char*));
            (*sentences)[cnt_sentences-1] = NULL;
            issentence = 1;
        }
        cnt_chars++;
        (*sentences)[cnt_sentences-1] = realloc((*sentences)[cnt_sentences-1], (cnt_chars+1)*sizeof(char));
        (*sentences)[cnt_sentences-1][cnt_chars-1] = cur_char;
    }

    if (!*sentences) printf("Error: Text is missing\n");
    return cnt_sentences;
}
