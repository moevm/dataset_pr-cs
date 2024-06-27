#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 10000
#define END "Dragon flew away!"
#define SENT_END '\0'

void get_text_with_tabs(char *input, char *output, int *before, int *after){
    char *text = output;
    int input_index = 0, text_index = 0;
    int start_of_sentence = 0;
    char symbol;
    
    while (strstr(text, END) == 0) {
        symbol = input[input_index];
        
        while (symbol == '\t' || symbol == ' ') {
            input_index++;
            symbol = input[input_index];
        }
        text[start_of_sentence] = symbol;
        
        while ((symbol == '.' || symbol == ';' || symbol == '?') == 0) {
            symbol = input[++input_index];
            text[++text_index] = symbol;
        }
        
        if (symbol == '?') {
            text_index = start_of_sentence;
            text[start_of_sentence] = SENT_END;
            input_index++;
            (*before)++;
        } else {
            text[++text_index] = '\n';
            start_of_sentence = ++text_index;
            text[start_of_sentence] = SENT_END;
            input_index++;
            (*before)++;
            (*after)++;
        }
    }
    
    *(strstr(text, END) + sizeof(END)) = SENT_END;
    
}

void print_with_numbers(char* text, int before, int after){
    for (int i = 0; text[i]; i++) {
            printf("%c", text[i]);
     }
    printf("Количество предложений до %d и количество предложений после %d", before, after);
}

int main(){
    char* scanned = (char*)malloc(LEN*sizeof(char));
    char* text = (char*)malloc(LEN*sizeof(char));
    
    fgets(scanned, LEN, stdin);
    
    int before = -1, after = -1;
    get_text_with_tabs(scanned, text, &before, &after);
    print_with_numbers(text, before, after);
    
    free(scanned);
    free(text);
    
    return 0;
}
