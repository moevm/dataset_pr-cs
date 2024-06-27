# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int main() {
    int N = 100;
    int k = 1;
    char *sentence = (char*)malloc(N * sizeof(char));  
    int index = 0;  
    int before_count = 0;  
    int after_count = 0;  
    char symbol;
    while (1) {
        symbol = getchar();
        if ((symbol == '\t' || symbol == ' ' || symbol == '\n') && index == 0){
            continue;
        }
        if (index == N){
            k++;
            sentence = (char *)realloc(sentence, (N * k)* sizeof(char)); 
        }
        if (symbol == '.' || symbol == ';' || symbol == '?') {
            sentence[index++] = symbol;
            sentence[index] = '\0';  
            if ((strstr(sentence, " 555.") == NULL) && (strstr(sentence, " 555,") == NULL) && (strstr(sentence, " 555;") == NULL) && (strstr(sentence, " 555:") == NULL) && (strstr(sentence, " 555 ") == NULL)  && (strstr(sentence, "555 ") == NULL))  {
                puts(sentence);
                after_count++;
            }      
            before_count++;
            free(sentence);
            sentence = (char*)malloc(N * sizeof(char));
            index = 0; 
        } else {
            sentence[index++] = symbol;
        if (symbol == '!') {
            sentence[index] = '\0'; 
            puts(sentence);
            break;
        }
        }
    }
    printf("Количество предложений до %d и количество предложений после %d\n", before_count, after_count);
    free(sentence);
    return 0;
}
