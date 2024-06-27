#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input(){
    char *str = malloc(sizeof(char));
    str[0] = '\0';
    int k=0;
    unsigned flag = 0;
    char symbol = getchar();
    for(;( (symbol != '.')&&(symbol!=';')&&(symbol!='?')&&(symbol!='!') ); k++){
        if(!flag)
        {
            if( (symbol==' ')||(symbol=='\t')||(symbol=='\n') )
            {
                k--;
                symbol = getchar();
                continue;
            }
            flag=1;
        }
        str = realloc(str, (k+2)*sizeof(char));
        str[k] = symbol;
        str[k+1] = '\0';
        symbol = getchar();
    }
    str = realloc(str, (k+2)*sizeof(char));
    str[k] = symbol;
    str[k+1] = '\0';
    return str;
}

char **make_text(int * before, int * after){
    char * end_str = malloc(sizeof(char)*18);
    end_str = "Dragon flew away!";
    char * str = input();
    char ** text = malloc(sizeof(char*));
    text[0] = end_str;
    int k = 0;

    for(; (strstr(str, end_str)==NULL); k++){

        if (strstr(str, "?")!=NULL)
            {
            k--;
            free(str);
            (*before)++;
            str = input();
            continue;
            }
        (*before)++;
        text = realloc(text, (k+2)*sizeof(char*));
        text[k] = str;
        text[k+1] = end_str;
        str = input();
    }
    *after = k;
    return text;
}

void free_text(char**text)
{
    char end_str[] = "Dragon flew away!";
    unsigned i = 0;
    for(; (strstr(text[i], end_str)==NULL); i++){
            printf("%s\n", text[i]);
            free(text[i]);}
    printf("%s\n", text[i]);
    free(text);
}

int main(){
    int before = 0;
    int after = 0;
    char **text = make_text(&before, &after);
    free_text(text);
    printf("Количество предложений до %d и количество предложений после %d\n", before, after);
    return 0;
}
