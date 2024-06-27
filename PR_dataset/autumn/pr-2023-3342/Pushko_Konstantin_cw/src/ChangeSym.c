#include"Structs.h"
#include"ChangeSym.h"
#include<stdlib.h>
#define ALPHABET L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюяABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
struct Text change_sym(struct Text text)
{
    wchar_t alphabet[120] = ALPHABET;

    for (size_t i = 0; i < text.sentences_count; i++)
    {
        for (size_t j = 0; j < text.sentences[i].words_count; j++)
        {
            int k = 0;

            while (k < text.sentences[i].words[j].letters_count)
            {

                int is_letter = 0;

                for (int l = 0; l < 120; ++l) {
                    if (text.sentences[i].words[j].letters[k] == alphabet[l])
                    {
                        is_letter = 1;


                        break;
                    }
                }

                if (!is_letter) {
                    int sym_code = (int)text.sentences[i].words[j].letters[k];

                    wchar_t buf[15];
                    swprintf(buf, 15, L"%d", sym_code);
                    text.sentences[i].words[j].letters_count += wcslen(buf);
                    text.sentences[i].words[j].letters = (wchar_t*)realloc(text.sentences[i].words[j].letters,
                        (text.sentences[i].words[j].letters_count + 1) *
                        sizeof(wchar_t));

                    for (int l = text.sentences[i].words[j].letters_count; l >= k + wcslen(buf) - 1; l--) {
                        text.sentences[i].words[j].letters[l] = text.sentences[i].words[j].letters[l - wcslen(buf) + 1];
                    }

                    for (int l = 0; l < wcslen(buf); l++) {
                        text.sentences[i].words[j].letters[k + l] = buf[l];
                    }
                    text.sentences[i].words[j].letters[text.sentences[i].words[j].letters_count] = '\0';
                    k += wcslen(buf) - 1;


                }


                k++;
            }

        }
    }
    return text;
}