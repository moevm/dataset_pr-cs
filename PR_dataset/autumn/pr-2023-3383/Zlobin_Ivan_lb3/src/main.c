#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void){
    char **str=(char**)malloc(sizeof(char*)*2);
    int it=0,i=0,cnt=0;
    for(;1;){
        str[it]=(char*)malloc(sizeof(char));
        char sim=getchar();
        for(i=0;;sim=getchar(),++i)
        {
            if(i>0 && isspace(sim) && (str[it][i-1]=='?' || str[it][i-1]=='.' || str[it][i-1]==';')){
                str[it][i]='\n'; str[it][i+1]='\0';
                break;
            }
            if(i>0 && str[it][i-1]=='!') { str[it][i]='\n'; str[it][i+1]='\0';
                break;}
            str[it][i]=sim;
            str[it]=(char*)realloc(str[it], sizeof(char)*(i+3));
        }
        if(str[it][i-1]=='!') break;
        if(str[it][i-1]=='?'){
            ++cnt;
        }
        ++it;
        str=(char**)realloc(str, sizeof(char*)*(it+1));
    }
    for(int u=0;u<=it;++u){
        if(str[u][strlen(str[u])-2]!='?')
        printf("%s", str[u]);
        free(str[u]);
    }
    free(str);
    printf("Количество предложений до %d и количество предложений после %d", it, it-cnt);
    return 0;
}

