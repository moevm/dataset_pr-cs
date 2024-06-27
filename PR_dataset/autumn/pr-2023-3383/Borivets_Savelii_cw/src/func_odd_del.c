#include "func_odd_del.h"
#include "struct.h"

struct Text func_odd_del(struct Text text) {
    wchar_t **new_text = (wchar_t **) malloc(sizeof(wchar_t*) * text.cnt_sen);
    size_t count_new_text = 0;//счетчик новых предложений
    for (size_t i = 0; i < text.cnt_sen; i++) {
        if (wcschr(text.txt[i], '1') == 0 && wcschr(text.txt[i], '3') == 0 && wcschr(text.txt[i], '5') == 0 && wcschr(text.txt[i], '7') == 0 && wcschr(text.txt[i], '9') == 0) {
            new_text[count_new_text] = text.txt[i];
            count_new_text++;
        }
    }
    struct Text odd_del_text = {new_text, count_new_text};
    return odd_del_text;
}