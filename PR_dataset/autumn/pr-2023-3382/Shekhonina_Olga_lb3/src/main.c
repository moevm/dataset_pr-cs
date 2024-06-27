#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 200
#define LEN 1000

int main()
{   int n = 0;  //количество предложений до
    char c;
    char* end = "Dragon flew away!";

    //считывание текста
    char** text = malloc(N * sizeof(char*));
    for(int i = 0; i<N; i++){
        text[i] = malloc(LEN * sizeof(char));
        for(int j = 0; j<LEN; j++){
            c = getchar();
            text[i][j] = c;
            if(c == '.' || c == ';' || c == '?' || c == '!'){
                text[i][j+1] = '\0';
                break;
            }
        }
        n++;

        //удаление табуляции
        int len = strlen(text[i]);
        while(text[i][0] == '\t' || text[i][0] == ' ' || text[i][0] == '\n'){
            int j = 0;
            while(j<len){
                text[i][j] = text[i][j+1];
                j++;
            }
        }
        if(!(strcmp(text[i], end))){
            break;
        }
    }

    //удаление строк с числом 555
    int m = n;
    int i = 0;
    while(text[i]){
        int len = strlen(text[i]);
        for(int j = 0; j<len-2; j++){
            if((text[i][j] == '5' && text[i][j+1] == '5' && text[i][j+2] == '5') && \
                (len == 4 || (j == 0 && text[i][j+3] == ' ') || \
                   (text[i][j-1] == ' ' && text[i][j+4] == '\0') || (text[i][j-1] == ' ' && text[i][j+3] == ' '))){
                int k = i;
                while(k<m){
                    text[k] = text[k+1];
                    k++;
                }
                m--;
                i--;
                break;
            }
        }
        i++;
    }

    //вывод текста
    for(int i = 0; i<m; i++){
        fputs(text[i], stdout);
        printf("\n");
    }
    n--;
    m--;
    printf("Количество предложений до %d и количество предложений после %d\n", n, m);

    //освобождение памяти
    for(int i = 0; i<N; i++){
        free(text[i]);
    }
    free(text);
    return 0;
}



