#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE_BLOCK 50

int check_digital(char* sentense, int len_sen) {
    int f = 0;
    for (int i = 0; i < len_sen - 1; i++) {
        if (f == 0 && (isalpha(sentense[i]) || isdigit(sentense[i]))) {
            int  cnt = 0, s = 0, len = 0;
            while (sentense[i + len] != ' ' && !ispunct(sentense[i + len]) && sentense[i + len] != '\0' && i + len < len_sen) {
                if (isdigit(sentense[i + len]) && len == 0) {
                    cnt++;
                    s = 1;
                } else if(isdigit(sentense[i + len])) {
                    cnt++;
                }
                len++;
            }
            if (cnt == len) continue;
            if (s == 1) cnt -= 1;
            if (isdigit(sentense[i + len - 1])) cnt -= 1;
            if (cnt > 0) return 1;
            f = 1;
        }
        if (sentense[i] == ' ' || sentense[i] == ',') f = 0;
    }
    return 0;
}
int main(){
    
    char* str = (char*) calloc(SIZE_BLOCK, sizeof(char));
    char** ans = (char**) calloc(SIZE_BLOCK, sizeof(char*));
    int before = 0, after = 0;
    int len = 0, num =1, num_a=1;
    char c = ' ';
    int f_end_sentense = 0;
    do {
        c = getchar();
        if (c == '\t' || c == '\n') continue;
        if (f_end_sentense == 1  && (c == ' ' || c =='\t')) continue;
        f_end_sentense = 0;
        str[len] = c;
        if(len + 1 == num * SIZE_BLOCK){
            str = (char*) realloc(str, (len + 1) * sizeof(char) + SIZE_BLOCK * sizeof(char));
            if(!str){
                printf("Ошибка выделения памяти");
                return 0;
            }
            num++;
        }
        if (c == '.' || c == ';' || c == '!' || c == '?') {
            f_end_sentense = 1;
            if (check_digital(str,len) == 0) {
                ans[after] = (char*) calloc(len + 2, sizeof(char));
                memcpy(ans[after], str, (len + 1) * sizeof(char));
                
                if (after + 1 == num_a * SIZE_BLOCK){
                    ans = (char**) realloc(ans, (after + 1) * sizeof(char*)+ SIZE_BLOCK * sizeof(char*));
                    if(!ans){
                        printf("Ошибка выделения памяти\n");
                        return 0;
                    }
                    num_a++;
                }
                after++;
            }
            before++;
            len = 0;
            free(str);
            num=1;
            str = (char*) calloc(SIZE_BLOCK, sizeof(char));
        } else{
            len++;
        }

    } while (c != '!');

    for (int i = 0; i < after; i++) {
        printf("%s\n", ans[i]);
        free(ans[i]);
    }
    free(ans);
    printf("Количество предложений до %d и количество предложений после %d\n", before - 1, after - 1);
    free(str);
}