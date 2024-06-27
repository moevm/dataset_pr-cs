#include "../include/summ_numbers.h"

void summ_numbers(Text text){
    for (int i = 0; i < text.size; i++){
        int current_sum = 0;
        int current_num = 0;
        for (int k = 0; k < wcslen(text.sentences[i].chars); k++){
            if (text.sentences[i].chars[k] >= L'0' && text.sentences[i].chars[k] <= L'9'){
                current_num = current_num * 10 + (text.sentences[i].chars[k] - L'0');
                if (text.sentences[i].chars[k + 1] < L'0' || text.sentences[i].chars[k + 1] > L'9'){
                    current_sum += current_num;
                    current_num = 0;
                }
            }
        }
        wprintf(L"%d\n", current_sum);
    }
}