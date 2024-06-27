#include "func_obr_text.h"
#include "struct.h"

struct Text func_obr_text(struct Text text) {
    wchar_t **new_text = (wchar_t **) malloc(sizeof(wchar_t*) * text.cnt_sen);
    size_t count_new_text = 0;//счетчик новых предложений
    int flag;
    for (size_t i = 0; i < text.cnt_sen; i++) {
        flag = 0;
        for (size_t j = 0; j < count_new_text; j++) {
            if (wcscasecmp(text.txt[i], new_text[j]) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            new_text[count_new_text] = text.txt[i];
            count_new_text++;
        }
    }
    struct Text obr_text = {new_text, count_new_text};
    return obr_text;
}