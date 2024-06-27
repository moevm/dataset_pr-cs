#include "first_func.h"

void first_func() {
    struct Text text = get_text();
    int answer = 0;
    for (int i = 0; i < text.number_of_sentences; i++) {
        for (int j = 5; j < text.text[i]->number_of_letters; j++) {
            if (text.text[i]->sentence[j] == L' ') {
                if (text.text[i]->sentence[j - 1] == L'c' && text.text[i]->sentence[j - 2] == L'e' &&
                    text.text[i]->sentence[j - 3] == L's' && text.text[i]->sentence[j - 4] == L' ') {
                    wchar_t c = text.text[i]->sentence[j - 5];
                    int index = 0;
                    while (c != L' ') {
                        answer += pow(10, index) * ((int) c - '0');
                        index++;
                        c = text.text[i]->sentence[j - 5 - index];
                    }
                }
            }
        }
    }
    wprintf(L"В тексте встретилось секунд на %.1lf минут.\n", (float) answer / 60);
    free_space(text);
}