#include "ninth_func.h"

void ninth_func() {
    struct Text text = get_text();
    for (int i = 0; i < text.number_of_sentences; i++) {
        for (int j = 0; j < text.text[i]->number_of_letters; j++) {
            if (j >= 5) {
                if (text.text[i]->sentence[j] == L' ' || text.text[i]->sentence[j] == L'\t' || text.text[i]->sentence[j] == L',' || text.text[i]->sentence[j] == L'.') {
                    if (j == 5) {
                        if (towlower(text.text[i]->sentence[j - 5]) == L's' && towlower(text.text[i]->sentence[j - 4]) == L'm' && towlower(text.text[i]->sentence[j - 3]) == L'i' && towlower(text.text[i]->sentence[j - 2]) == L'l' && towlower(text.text[i]->sentence[j - 1]) == L'e')
                        {
                            wprintf(L" :=)%lc", text.text[i]->sentence[j]);
                        }
                        else
                        {
                            wprintf(L"%lc", text.text[i]->sentence[j]);
                        }
                    } else {
                    if ((text.text[i]->sentence[j - 6] == L' ' || text.text[i]->sentence[j - 6] == L'\t' || text.text[i]->sentence[j - 6] == L',') && towlower(text.text[i]->sentence[j - 5]) == L's' && towlower(text.text[i]->sentence[j - 4]) == L'm' && towlower(text.text[i]->sentence[j - 3]) == L'i' && towlower(text.text[i]->sentence[j - 2]) == L'l' && towlower(text.text[i]->sentence[j - 1]) == L'e')
                    {
                        wprintf(L" :=)%lc", text.text[i]->sentence[j]);
                    }
                    else
                    {
                        wprintf(L"%lc", text.text[i]->sentence[j]);
                    }
                    }
                } else {
                    wprintf(L"%lc", text.text[i]->sentence[j]);
                }
            } else {
                wprintf(L"%lc", text.text[i]->sentence[j]);
            }
        }
        wprintf(L"\n");
    }
}