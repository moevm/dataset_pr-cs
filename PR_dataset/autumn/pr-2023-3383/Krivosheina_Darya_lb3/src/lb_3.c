#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT 15
#define SENT 30

int main(){
    char **text = malloc(TEXT * sizeof(char*));
    char *sent = malloc(SENT * sizeof(char));
    int len_sent = 0, len_text = 0;
    int before = 0, after = 0;
    int cap_sent = SENT, cap_text = TEXT;
    char g;
    
    while(1){
        g = getchar();
        if (g == '.' || g == ';' || g == '?'){
            before++;
            // расширение памяти для того, чтобы положить туда знак препинания
            if (len_sent % (SENT - 1) == 0){
                cap_sent += SENT;
                sent = realloc(sent, cap_sent * sizeof(char));
            }
            sent[len_sent] = g;
            len_sent ++;
            // проверка на наличие 555
            int flag = 0;
            for (int i = 0; i < len_sent - 4; i++){
                if ((sent[i] == ' ') && (sent[i + 1] == '5') && (sent[i + 2] == '5') && (sent[i + 3] == '5') && ((sent[i + 4] == ' ') || (sent[i + 4] == '.') || (sent[i + 4] == ';') || (sent[i + 4] == '?'))){
                    flag = 1;
                    break;
                } else if ((i == 0) && (sent[i] == '5') && (sent[i + 1] == '5') && (sent[i + 2] == '5') && ((sent[i + 3] == ' ') || (sent[i + 3] == '.') || (sent[i + 3] == ';') || (sent[i + 3] == '?'))){
                    flag = 1;
                    break;
                }
            }
            // добавление в text предложения только в случае отсутствия в нем числа 555
            if (flag == 0){
                if (len_text % (TEXT - 1) == 0){
                    cap_text += TEXT;
                    text = realloc(text, cap_text * sizeof(char*));
                }
                text[len_text] = malloc((len_sent + 1) * sizeof(char));
                // добавление предложения в текст со знаком конца строки
                for (int k = 0; k < len_sent; k++){
                    text[len_text][k] = sent[k];
                }
                text[len_text][len_sent] = '\0';
                len_text++;
            }
            memset(sent, 0, sizeof(sent));
            len_sent = 0;
        } else if (g == '!'){
            if (len_text % (TEXT - 1) == 0){
                text = realloc(text, (len_text + 1) * sizeof(char*));
            }
            text[len_text] = malloc((len_sent + 2) * sizeof(char));
            // добавление предложения в текст с символом конца строки
            for (int k1 = 0; k1 < len_sent; k1++){
                    text[len_text][k1] = sent[k1];
                }
                text[len_text][len_sent] = '!';
                text[len_text][len_sent + 1] = '\0';
                break;
        } else {
            // корректировка табуляций, пробелов и переносов
            if (g == '\t' || (g == ' ' && len_sent == 0) || (g == '\n' && len_sent == 0)){
                continue;
            } else if (g == '\n'){
                g = ' ';
            }
            if (len_sent % (SENT - 1) == 0){
                cap_sent += SENT;
                sent = realloc(sent, cap_sent * sizeof(char));
            }
            sent[len_sent] = g;
            len_sent++;
        }
    }
    // вывод
    for (int t = 0; t < len_text + 1; t++){
        printf("\n");
        for (int t1 = 0; t1 < strlen(text[t]); t1 ++){
            printf("%c", text[t][t1]);
        }
    }
    printf("\nКоличество предложений до %d и количество предложений после %d", before, len_text);
    // очистка
    for (int w = 0; w < len_text + 1; w++){
        free(text[w]);
    }
    free(text);
    free(sent);
    
    return 0;
}
