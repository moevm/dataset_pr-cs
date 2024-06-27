#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int z;
    int flag_tchk = 0;//Флажок
    char *str = malloc(1);
    char **pred = malloc(sizeof(char*));
    int kol_del = 0, kol_pred = 0;
    char c;
    
    for (int i=0; (c = getchar()); i++)
    {
        if(flag_tchk && ((c == '\t') || (c == ' ')))
        {
        flag_tchk = 0;
        i --;
        continue;
        }
        flag_tchk = 0;
        str[i] = c;
        str = realloc(str, i + 2);//Обычный ввод.
        
        
        
        if (c == '.' || c == ';' || c =='?' || c =='!')
        {//Разделение на предложения.
        flag_tchk = 1;
        str[i+1] = '\0';
        if ((strstr(str, " 555 ") == NULL) && (strstr(str, "555.") == NULL) && (strstr(str, "555 ") == NULL))//Поиск 555
            {
            pred = realloc(pred, sizeof(char*) * (kol_pred+1));
            pred[kol_pred] = str;
            kol_pred++; 
            }
        else {kol_del++;}
        
        str= malloc(1);
        i = -1;
            if (c == '!')
                break;
        }
    }
    //printf("%s, p= %d", pred[1], kol_pred);
    for (int i = 0; i < kol_pred; i++) {
        printf("%s\n", pred[i]);
        free(pred[i]);
    }
    free(pred);
    free(str);
    printf("Количество предложений до %d и количество предложений после %d", kol_pred - 1 + kol_del, kol_pred - 1);
    return 0;
}