#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char* res_str = calloc(1, sizeof(char));
    char* str = calloc(1, sizeof(char));
    int n_counter = 0;
    int m_counter = 0;
    int symbol;
    int l_symbol = 0;
    int s_idx = 0;
    int r_idx = 0;
    while (1)
    {
        symbol = getchar();
        if (symbol == '!'){break;}
        if ((symbol != '.' && symbol != ';' && symbol != '?')){
            if (symbol != '\t' && symbol != '\n'){
                str[s_idx] = symbol;
                s_idx++;
                char *tmp = realloc(str, strlen(str) + 2);
                str = tmp;
            }
            else if (symbol == '\n'){
                str[s_idx] = ' ';
                s_idx++;
                char *tmp = realloc(str, strlen(str) + 2);
                str = tmp;
            }
        }
        else if (symbol != '\t' && symbol != '?'){
            char *tmp1 = realloc(res_str, strlen(res_str) + strlen(str) + 2);
            res_str = tmp1;
            int idx = 0;
            for (int i = 0; i < s_idx; i++){
                if (l_symbol == ' ' && str[i] == ' '){continue;}
                if (str[i] != ' ' || i != 0){
                    res_str[r_idx + idx] = str[i];
                    idx++;
                }
                l_symbol = str[i];
                
            }
            res_str[r_idx + idx] = symbol;
            res_str[r_idx + idx + 1] = '\n';
            r_idx = idx + r_idx + 2;
            s_idx = 0;
            n_counter++;

        }
        else if (symbol == '?'){
            m_counter++;
            s_idx = 0;
        }
        
    }
    printf("%s", res_str);
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d", n_counter + m_counter, n_counter);
    return 0;
}
