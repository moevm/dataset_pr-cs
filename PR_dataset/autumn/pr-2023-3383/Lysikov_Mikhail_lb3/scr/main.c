#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buffer 100
#define end "Dragon flew away!"

int main() {
    int size = buffer;
    char* text = (char*)malloc(sizeof(char) * size);
    int i = 0, orig = 0, redact = 0;
    char input;

    while (1) {
        input = getchar();
        
        if ((i == 0) && ((input == '\t') || (input == ' ')))
            continue;
        
        if (i == size - 2) {
            size += buffer;
            text = (char*)realloc(text, size * sizeof(char));
        }

        text[i] = input;
        i++;

        if ((input == '.') || (input == ';') || (input == '?')) {
            text[i] = '\0';
            
            if (strchr(text, '?') == NULL) {
                printf("%s\n", text);
                redact++;
            }
            
            free(text);
            text = (char*)calloc(size, sizeof(char));
            orig++;
            i = 0;
        }
        
        if (input == '!'){
            break;
        }
    }
    printf("%s\n",end);
    printf("Количество предложений до %d и количество предложений после %d", orig, redact);
    free(text);

    return 0;
}
