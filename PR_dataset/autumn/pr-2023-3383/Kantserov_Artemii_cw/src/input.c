#include "input.h"
#include <stdio.h>
#include "struct.h"
#include <string.h>

void input_9 (struct text* text, int repeat){
    for (int i = 0; i < text->count_sentence; i++) {
        if (text->sentence[i].print == 1){
            char* token = strtok(text->sentence[i].str, ".");
            for (int j = 0; j < repeat-1; j++) {
                printf("%s ", token);
            }
            printf("%s.\n", token);
        }
    }
}

void input(struct text* text) {
    for (int i = 0; i < text->count_sentence; i++){
        if (text->sentence[i].print == 1) {
            printf("%s", text->sentence[i].str);
            printf("\n");
        }
    }
}

