#include <stdio.h>
#include <stdlib.h>

int main() {
    char c;
    c = getchar();
    int str_len = 0, str_cnt = 0, str_dlt = 0, flag = 1;
    char* str = (char*)malloc(1*sizeof(char));
    while(c!='!')
    {
        flag = 1;
        if(c == '7')
        {
            flag = 0;
            while(c != '!')
            {
                if(c == ';'|| c == '.' || c == '?')
                {
                    str_len = 0;
                    str_dlt++;
                    
                    break;
                } 
                c = getchar();
            }
        }
        else if (!((c == ' ' || c == '\t' || c == '\n' || c == '\0') && str_len == 0))
        {
            str = (char*)realloc(str, (str_len+1)*sizeof(char));
            str[str_len] = c;
            str_len++;
        }
        if(c == ';'|| c == '.' || c == '?')
        {
            if(flag)
            {
                for(int i = 0; i < str_len; i++)
                {
                    printf("%c", str[i]);
                }
                printf("\n");
            }
            str_len = 0;
            str_cnt++;
        }
        c = getchar();
    }
    free(str);
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d\n", str_cnt, str_cnt-str_dlt);
    return 0;
}