//created by niks (student LETI)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(){
    char c;
    char *local_str=malloc(sizeof(char)*1);
    local_str[0]=NULL;
    int cnt=1;
    int cnt_before=0, cnt_after=0;
    const char stop[] = "Dragon flew away!";
    do{
        c = getchar();
        if(c == '\n')continue;
        if(isspace(c)){
            if(cnt == 1 )continue;
            else{
                local_str = realloc(local_str,sizeof(char)*(cnt+1));
                local_str[cnt-1]=c;
                local_str[cnt++]=NULL;
            }
        }else{
            local_str = realloc(local_str,sizeof(char)*(cnt+1));
            local_str[cnt++]=NULL;
            local_str[cnt-2]=c;
            if(c == '.' || c == ';' || c == '?'){
                cnt_after++;
                int up = 0;
                for(int i=0;i<cnt-1;++i){
                    if(isupper(local_str[i]))up++;
                }
                if(up<=1){
                cnt_before++;
                puts(local_str);
                }
                free(local_str);
                local_str = malloc(sizeof(char)*1);
                local_str[0]=NULL;
                cnt=1;
            }
        }
    }while(strcmp(local_str,stop)!=0);
    free(local_str);
    printf("%s\nКоличество предложений до %d и количество предложений после %d",stop,cnt_after,cnt_before);
    return 0;
}
