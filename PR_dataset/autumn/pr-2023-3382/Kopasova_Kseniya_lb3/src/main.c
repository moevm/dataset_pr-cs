#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 100

char** split(char* arr,char* chars, int n, int* m);

int main()
{
    char last_sm = '!';
    int n = 0;
    int m = 0;
    int len = 0;
    int constan = N;
    char c = 0;
    char* arr = malloc(sizeof(char) * constan);

    while ((c = getchar()) != last_sm) {
        if ((c != '\n') && (c != '\t')){
            if (len >= constan){
                constan += N;
                arr = realloc(arr, constan * sizeof(char));
            }
            
            if ((c == '.') || (c == ';') || (c == '?')) {
                n++;
            }
            arr[len++] = c;
        }
    }
    arr = realloc(arr, (len + 2) * sizeof(char));
    arr[len++] = (last_sm);
    arr[len] = '\0';
    
    char** spl_arr = split(arr, "?.;!", n, &m);
    
    //вывод 
    for (int i = 0; i < m; i++) {
        printf("%s\n", spl_arr[i]);
        free(spl_arr[i]);
    }
    
    printf("Количество предложений до %d и количество предложений после %d", n, m-1);
    free(arr);
    free(spl_arr);
    return 0;
}

char** split(char* arr,char* chars, int n, int* m) {
    int c= 0;
    int ind=0;
    int rem_sen=0;
    char** spl_arr = malloc(sizeof(char*));

    for (int i = 0; i < (int)strlen(arr); i++) {

            if (arr[i] == '7') {
                    rem_sen = 1;
            }

            if (strchr(chars, arr[i])){        
                if (rem_sen == 1) {
                    rem_sen = 0;
                    ind = 0;
                    continue;
                }

                c++;
                spl_arr = realloc(spl_arr, c * sizeof(char*));
                spl_arr[c - 1] = malloc((ind + 2) * sizeof(char));

                int chr=0;
                for (int j = ind; j >=0; j--) {
                    //пропускаем пробел в начале предложения(если он есть)
                    if (j == ind && arr[i - j] == ' ')
                        continue;
                    spl_arr[c - 1][chr++] = arr[i - j];
                }
                spl_arr[c - 1][chr] = '\0';
                ind = 0;
                continue;
            }
            ind++;
        }
        *m = c;
        return spl_arr;
}