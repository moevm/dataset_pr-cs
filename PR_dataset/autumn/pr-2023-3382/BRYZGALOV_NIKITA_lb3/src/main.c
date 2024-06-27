#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num_sent = 0, num_del_sent = 0, fact_num_sent, len_sent = 0, flag_del = 0;
    char **answer = malloc(sizeof(char*));
    char *sent = malloc(sizeof(char));
    char symbol;
    
    while (symbol != '!') {
        symbol = getchar();
        
        if (((symbol == '\t') && (len_sent == 0)) || (symbol == '\n') || ((symbol == ' ') && (len_sent == 0)))
            continue;
            
        len_sent ++;
        sent = realloc(sent, sizeof(char) * len_sent);
        sent[len_sent -1] = symbol;
        
        if ((len_sent >= 4) && ((sent[len_sent -2] == '5') && (sent[len_sent -3] == '5') && (sent[len_sent -4] == '5'))) {
            if (((sent[len_sent -1] == ' ') || (sent[len_sent -1] == '.') || (sent[len_sent -1] == ';') || (sent[len_sent -1] == '?') || (sent[len_sent -1] == '!')) && ((len_sent == 4) || (sent[len_sent -5] == ' ')))
                flag_del = 1;
        }
        
        if ((symbol == '.') || (symbol == ';') || (symbol == '?') || (symbol == '!')) {
            num_sent += 1;
            if (flag_del == 1) {
                num_del_sent ++;
            } else {
                fact_num_sent = num_sent - num_del_sent;
                answer = realloc(answer, sizeof(char*) * fact_num_sent);
                answer[fact_num_sent - 1] = malloc(sizeof(char) * (len_sent + 1));
                for (int i = 0; i < len_sent; i ++)
                    answer[fact_num_sent - 1][i] = sent[i];
                answer[fact_num_sent - 1][len_sent] = '\0';
            }
            free(sent);
            sent = malloc(sizeof(char));
            len_sent = flag_del = 0;
        }
    }
    
    for (int i = 0; i < fact_num_sent; i ++) {
        printf("%s\n", answer[i]);
        free(answer[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d\n", (num_sent - 1), (fact_num_sent - 1));
    free(answer);
    free(sent);
    return 0;
}