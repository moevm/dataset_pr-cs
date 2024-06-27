#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#define BLOCK_SIZE 8
typedef struct Text{
    char **str;
    int size;
} Text;

int check(char *s){
    return strncmp(s, "Fin.", 4);
}

Text *input(){
    Text *text=malloc(sizeof(Text));
    text->size=0;
    text->str=malloc((text->size+1)*sizeof(char *));
    text->str[text->size]=malloc(sizeof(char)*BLOCK_SIZE);
    char c=getchar(); int len=0;
    for(;;c=getchar()){
        if(c=='\n'){
            text->str[text->size][len++]='\0';
            text->str[text->size]=realloc(text->str[text->size], (len)*sizeof(char));
            ++text->size;
            text->str=realloc(text->str, (text->size+1)*sizeof(char *));
            text->str[text->size]=malloc(sizeof(char)*BLOCK_SIZE);
            len=0;
            continue;
        }
        text->str[text->size][len++]=c;
        if(c=='.'){
            if(check(text->str[text->size])==0)
                break;
        }
        if(len%BLOCK_SIZE==0){
            text->str[text->size]=realloc(text->str[text->size], sizeof(char)*(len+BLOCK_SIZE));
        }
    }
    return text;
}

void clear(Text *text){
    for(int i=0;i<text->size;++i){
        free(text->str[i]);
    }
    free(text->str);
    free(text);
}

int main(void){
    Text *text=input();
    regmatch_t match[3];
    regex_t regex;
    regcomp(&regex, "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: ?~ ?# (.+)", REG_EXTENDED);
    for(int i=0;i<text->size;++i){
        if(regexec(&regex, text->str[i], 3, match, 0)==0)
        {
            for(int j=match[1].rm_so;j<match[1].rm_eo;++j) printf("%c", text->str[i][j]);
            printf(" - ");
            for(int j=match[2].rm_so;j<match[2].rm_eo;++j) printf("%c", text->str[i][j]);
            printf("\n");
        }
    }
    regfree(&regex);
    clear(text);
    return 0;
}
