#include <stdio.h>
#include <stdlib.h>
int main(){
        char *text=malloc(sizeof(char)*100);
        int len_text=100;
        int symb_inp=0;
        char symbol;
        int before_string=0;
        int after_string=0;
        int i=0;
        int j=0;
        int k=0;
        while(symbol!='!'){
                symbol=getchar();
                if ((symbol=='.')||(symbol==';')){
                    j=i+1;
                }
                if ((symbol=='.')||(symbol=='?')||(symbol==';')){
                    before_string++;
                }
                if (symb_inp>len_text){
                    len_text+=50;
                    char *text1=realloc(text,sizeof(char)*len_text);
                    if (text1!= NULL){
                        text=text1;
                    }
                }
                if (symbol=='?'){
                    for(i;i>j;i--){
                        text[i]='\0';
                    }
                    
                }
                
                if((symbol=='\t')||(symbol=='\n')){
                    continue;
                }
                if (symbol!='?'){
                    text[i]=symbol;
                    i++;
                }
                symb_inp++;
        }
        for(i=0;text[i-1]!='!';i++){
            if((text[i]==' ')&&((text[i-1]=='.')||(text[i-1]==';'))){
                continue;
            }
            printf("%c",text[i]);
            if ((text[i]=='.')||(text[i]==';')){
                after_string+=1;
                printf("\n");
            }
        }
        free(text);
        printf("\nКоличество предложений до %d и количество предложений после %d",before_string,after_string);
        return 0;
}
