#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
typedef char ch;
#define BLOCK 8

int main(){
        ch**text=(ch**)malloc(sizeof(ch*)*BLOCK);
        int text_kol = 0;
        int text_mx = BLOCK;
        short flag = 1;
        while(flag){
                if(text_kol+2>text_mx){text_mx+=BLOCK;text=(ch**)realloc(text,sizeof(ch*)*text_mx);}
                int ch_kol = 0;
                text[text_kol]=(ch*)malloc(sizeof(ch)*BLOCK);
                int mx_kol = BLOCK;
                for(ch c = getchar();;c = getchar()){
                        if(ch_kol+2>mx_kol){
                                mx_kol+=BLOCK;
                                text[text_kol]=(ch*)realloc(text[text_kol],sizeof(ch)*mx_kol);
                        }
                        if(c == '\n'){text[text_kol][ch_kol]='\0';break;}
                        text[text_kol][ch_kol++]=c;
                        if(strncmp(text[text_kol],"Fin.",4)==0){flag = 0;break;}
                }
                text_kol++;
        }
        regex_t rx;
        int j=0;
        int prof = regcomp(&rx,"[a-zA-Z0-9_]+@[a-zA-Z0-9_-]+:[ ]?~[ ]?# .*$",REG_EXTENDED);
        for(int i=0;i<text_kol;++i){
                regmatch_t matches[1];
                prof = regexec(&rx, text[i],1,matches,0);
                if(prof == 0){
                        if(j!=0)putchar('\n');
                        ++j;
                        int start = matches[0].rm_so;
                        for(;text[i][start]!='@';++start)putchar(text[i][start]);
                        for(;text[i][start]!='#';++start);
                        start++;
                        printf(" -");
                        for(;start<strlen(text[i]);++start)putchar(text[i][start]);
                }
        }
}