#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>



#include "change_text.h"
#include "cmps.h"
#include "structures.h"
#include "input.h"
#include "last.h"


int main() {
    setlocale(LC_CTYPE, "");
    wprintf(L"Course work for option 5.2, created by Yurii Serbinovskii.\n");

    wint_t order;
    wscanf(L"%ld", &order);
    getwchar();
    wchar_t* mask;
    int first_len = 0;


    if ((order > 5 || order < 0) && order != 9) {
        fwprintf(stderr, L"Error: Некорркетное число\n");
        exit(0);
    }
    else if (order == 5) {
        wprintf(L"Опция 0: вывести все неповторяющиеся предложения.\n");
        wprintf(L"Опция 1: вывести все предложения, в которых каждое слово удовлетворяет введенной строке-условию. Строка условия содержит: символы, * - 0 или больше любых символов, ? – один любой символ. В строке-условия не может быть больше одного *.\n");
        wprintf(L"Опция 2: отсортировать предложения по средней длине слов в предложении.\n");
        wprintf(L"Опция 3: преобразовать предложения так, чтобы слова располагались в порядке уменьшения длины слова.\n");
        wprintf(L"Опция 4: удалить все предложения, в котором больше 5 или меньше 2 слов.\n");
        exit(0);
    }
    else if (order == 1) {
        mask = mask_input();

    }
    else if (order == 9) {
        wchar_t c = getwchar();
        while (!iswspace(c))
        {
            first_len++;
            c = getwchar();
        }
        
    }



    struct Text *text = malloc(sizeof(struct Text));
    if (text == NULL) {
        fwprintf(stderr, L"Error: Ошибка выделения памяти");
        exit(0);
    }




    int sent_index = text_input(text);



    int* bad_memory;

    switch (order)
    {
        case 0:
            for(int i = 0; i < sent_index; i++) {
                wprintf(L"%ls", text->t[i]->s);
            }
            break;
        case 1:
            for (int i = 0; i<sent_index; i++) {
                if (mask_approved(text->t[i]->s, mask)) {
                    wprintf(L"%ls", text->t[i]->s);
                }
            }
            free(mask);
            break;
        case 2:
            qsort(text->t, sent_index, sizeof(struct Sentence*), cmp);
            for (int i = 0; i < sent_index; i++) {
                wprintf(L"%ls", text->t[i]->s);
            }
            break;
        case 3:
            for (int i = 0; i < sent_index; i++) {
                words_sort(text->t[i]->s);
            }
            for (int i = 0; i < sent_index; i++) {
                wprintf(L"%ls", text->t[i]->s);
            }
            break;
        case 4:
            bad_memory = malloc(sizeof(int)*sent_index);
            if (bad_memory == NULL) {
                fwprintf(stderr, L"Error: Ошибка выделения памяти");
                exit(0);
            }
            int bad_count = 0;
            for (int i = 0; i < sent_index; i++){
                if (delete_sent(text->t[i]->s)) {
                    bad_memory[i] = i;
                    free(text->t[i]->s);
                    free(text->t[i]);
                }
                else
                    bad_memory[i] = -1;
            }
                for (int i = 0; i < sent_index; i++) {
                    if (bad_memory[i] == -1)
                        wprintf(L"%ls", text->t[i]->s);
                }
            for (int i = 0; i < sent_index; i++) {
                if (bad_memory[i] == -1){
                    free(text->t[i]->s);
                    free(text->t[i]);
                }
            }
            break;
        case 9:
            for (int i = 0; i < sent_index; i++) {
                wprintf(L"%ls", big_word(first_len, text->t[i]->s));
            }

        default:
            break;
    } 

    for (int i = 0; i < sent_index; i++) {
        if (order != 4){
            free(text->t[i]->s);
            free(text->t[i]);
        }
    }
    free(text->t);
    free(text);

    return 0;
}