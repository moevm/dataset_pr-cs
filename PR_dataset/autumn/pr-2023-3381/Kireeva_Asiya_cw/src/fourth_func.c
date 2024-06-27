#include "fourth_func.h"

void fourth_func() {
    struct Text text = get_text();
    wchar_t symbols[] = {L'b', L'c', L'd', L'f', L'g', L'h', L'j', L'k', L'l', L'm', L'n', L'p', L'q', L'r', L's',
                           L't', L'v', L'w', L'x', L'z', L'б', L'в', L'г', L'д', L'ж', L'з', L'й', L'к', L'л', L'м',
                           L'н', L'п', L'р', L'с', L'т', L'ф', L'х', L'ц', L'ч', L'ш', L'щ'};
    for (int i = 0; i < text.number_of_sentences; i++) {
        int cur_count = 0, flag = 0;
        for (int j = text.text[i]->number_of_letters - 1; j >= 0; j--) {
            int cur_fl = 0;
            if (text.text[i]->sentence[j] == L' ' || text.text[i]->sentence[j] == L',') {
                break;
            }
            for (int k = 0; k < 41; k++) {
                if (towlower(text.text[i]->sentence[j]) == symbols[k]) {
                    cur_count++;
                    cur_fl = 1;
                    if (cur_count >= 3) {
                        flag = 1;
                    }
                    break;
                }
            }
            if (!cur_fl) {
                cur_count = 0;
            }
        }
        if (!flag) {
            wprintf(L"%ls\n", text.text[i]->sentence);
        }
    }
    free_space(text);
}