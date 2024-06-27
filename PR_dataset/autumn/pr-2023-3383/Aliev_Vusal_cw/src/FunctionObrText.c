#include "Common.h"
#include "FunctionObrText.h"

void FunctionObrText(char** text, int* count_sent) {
	for (int i = 0; i < *count_sent; i++) {
        if (text[i] == NULL) {
            // Проверка на NULL для текущей строки
            continue;
        }

        for (int j = i + 1; j < *count_sent; j++) {
            if (text[j] == NULL) {
                // Проверка на NULL для сравниваемой строки
                continue;
            }

            if (strcasecmp(text[i], text[j]) == 0) {
                free(text[j]);
                text[j] = NULL;

                for (int k = j; k < *count_sent - 1; k++) {
                    text[k] = text[k + 1];
                }

                text[*count_sent - 1] = NULL;
                (*count_sent)--;
                j--;
            }
        }
    }
}