#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ADDITIONAL_DATA 20

int is_555_in_sentence(const char* str) {
    char* p_end;
    long num;

    while (*str) {
        if (isdigit(*str)) {
            num = strtol(str, &p_end, 10);
            if (num == 555) {
                if ((str == str || !(isdigit(*(str - 1)) || isalpha(*(str - 1)))) && 
                    (!*p_end || !(isdigit(*p_end) || isalpha(*p_end))))
                    return 1;
            }
            str = p_end;
        } else {
            str++;
        }
    }

    return 0;
}


int main() {
    char** text = (char**) malloc(sizeof(char*)* ADDITIONAL_DATA);
    int cntSentence = 0;
    int processedSentence = 0; // number of sentences displayed
    int capasityText = ADDITIONAL_DATA;
    
    for (int i = 0; ; i++)
    {
    
        text[i] = (char*) malloc(sizeof(char) * ADDITIONAL_DATA);
        int idxSymbol = 0;
        int capasitySentence = ADDITIONAL_DATA;
        char symbol;
        
        while((symbol = getchar()) != EOF)
        {
            if( idxSymbol == 0 && isspace(symbol) )
                continue;
            
            text[i][idxSymbol] = symbol;
            idxSymbol++;
            if (symbol == '.' || symbol == ';' || symbol == '?' || symbol == '!')
                break;
                
            if (idxSymbol == capasitySentence-1)
            {
                capasitySentence += ADDITIONAL_DATA;
                text[i] = (char*) realloc(text[i], sizeof(char)*capasitySentence);
            }
        }
        
        text[i][idxSymbol] = '\0';
        cntSentence++;
        if (strcmp(text[i], "Dragon flew away!") == 0)
            break;
        
        if (cntSentence == capasityText-1)
        {
            capasityText += ADDITIONAL_DATA;
            text = (char**) realloc(text, sizeof(char*)*capasityText);
        }
        
    }
    
    for (size_t i = 0; i < cntSentence; i++)
    {
        if (!is_555_in_sentence(text[i]))
        {
            printf("%s\n", text[i]);
            processedSentence++;
        }
        free(text[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d", cntSentence-1, --processedSentence);
    free(text);
    
    
    return 0;
}
