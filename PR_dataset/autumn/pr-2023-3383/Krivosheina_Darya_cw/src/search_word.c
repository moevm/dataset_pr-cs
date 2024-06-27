#include "search_word.h"
#include "struct.h"

void search_word(struct Text our_text, wchar_t *word){
    int cap_current = CURRENT, len_current = 0;
    wchar_t *current = malloc(cap_current * sizeof(wchar_t));
    for (int x = 0; x < our_text.len; x++){
        for (int y = 0; y < wcslen(our_text.text[x]); y++){
            if (our_text.text[x][y] != ' ' && our_text.text[x][y] != '.' && our_text.text[x][y] != ',' && our_text.text[x][y] != '\n'){
                if (len_current % (CURRENT - 1) == 0){
                    cap_current += CURRENT;
                    current = realloc(current, sizeof(wchar_t) * cap_current);
                }
                current[len_current] = our_text.text[x][y];
                len_current ++;
                if (our_text.text[x][y + 1] == ' ' || our_text.text[x][y + 1] == '.' || our_text.text[x][y + 1] == ',' || our_text.text[x][y + 1] == '\n'){
                    if (len_current % (CURRENT - 1) == 0){
                        cap_current += CURRENT;
                        current = realloc(current, sizeof(wchar_t) * cap_current);
                    }
                    current[len_current] = '\0';
                    int flag = 0;
                    for (int c = 0; c < len_current; c++){
                        for (int c1 = 0; c1 < wcslen(word); c1++){
                            if (towlower(current[c]) == towlower(word[c1])){
                                flag++;
                                break;
                            }
                        }
                    }
                    if (flag == len_current){
                        wprintf(L"%ls\n", current);
                    }
                    memset(current, 0, sizeof(current));
                    len_current = 0;
                    cap_current = CURRENT;
                }
            }
        }
    }
}
