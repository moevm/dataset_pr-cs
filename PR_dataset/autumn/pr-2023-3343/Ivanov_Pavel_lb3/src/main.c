#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_in_str(char* sentence) {
    char* str = strdup(sentence);
    char* temp;
    
    temp = strtok(str, " ");
    while(temp != NULL) {
        if(strcmp(temp, "555") == 0 || strcmp(temp, "555.") == 0 || strcmp(temp, "555;") == 0 || strcmp(temp, "555?") == 0) {
            free(str);
            return 1;
        }
        temp = strtok(NULL, " ");
    }
    free(str);
    return 0;
}

int main() {
    char** text = malloc(sizeof(char*));
    int len_of_text = 0;
    

    char* sentence = malloc(sizeof(char));
    int len_of_sentence = 0;

    char symbol;
  
    do {
        symbol = getchar();

        if(symbol == '\n'){
            continue;
        }

        sentence = realloc(sentence, (len_of_sentence + 2) * sizeof(char));
        sentence[len_of_sentence++] = symbol;

        if(symbol == '?' || symbol == ';' || symbol == '.' || symbol == '!') {
            sentence[len_of_sentence] = '\0';
            text = realloc(text, (len_of_text + 1) * sizeof(char*));
            text[len_of_text] = sentence;
            
            sentence = malloc(sizeof(char));
            len_of_sentence = 0;

            len_of_text++;
            getchar();
        }
    } while(symbol != '!');

    char** result_text = malloc(sizeof(char*) * len_of_text);
    int ct = 0;

    for(int i = 0; i < len_of_text; i++) {
        char* str = text[i];
        if(str[0] == '\t'){
            int len = strlen(str) - 1; 
            char* new_str = malloc(sizeof(char) * (len + 1)); 
            for (int k = 1; k <= len; k++) { 
                new_str[k - 1] = str[k];
            }
            new_str[len] = '\0';
 
            if(number_in_str(new_str) == 0){
                result_text[ct++] = new_str;
            }
        } else if((str[0] != '\t') && (number_in_str(str) == 0)){
            result_text[ct++] = str;
        }
    }

    for(int i = 0; i < ct; i++) {
        printf("%s\n", result_text[i]);
        free(result_text[i]);
    }
    free(result_text);

    printf("Количество предложений до %d и количество предложений после %d\n", len_of_text-1, ct-1);
    return 0;

    for(int i = 0; i<len_of_text; i++){
        free(text[i]);
    }
    free(text);
    
}