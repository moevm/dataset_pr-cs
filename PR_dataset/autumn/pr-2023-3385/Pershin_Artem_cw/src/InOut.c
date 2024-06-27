#include "InOut.h"

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>


#define TEXTBLOCK 50
#define SENBLOCK 20
#define WORDBLOCK 30


struct Text intext(){
    struct Text text;
    int textsize = TEXTBLOCK;
    int senlen, wordlen;
    text.p=(struct Sentence*)malloc(textsize*sizeof(struct Sentence));
    if(text.p == NULL){
    	printf("Не удалось выделить память");
    	exit(1);
    }
    text.size=0;
    int i=0, j=0, k=0, a=0, b=0;
    wchar_t c;
    c = getwchar();
    while((c==L' ' || c==L',' || c==L'.' || c==L'\n') && b < 2){
        if(c == '\n'){
            b++;
        }
        else{
            b=0;
        }
        if(b < 2){
            c = getwchar();
        }
    }
    do{
        struct Sentence sen;
        a=0;
        senlen = SENBLOCK;
        sen.p = (struct Word*)malloc(senlen*sizeof(struct Word));
        if(sen.p == NULL){
    		printf("Не удалось выделить память");
    		exit(1);
    	}
        sen.len=0;
        do{
            i = 0;
            struct Word word;
            wordlen = WORDBLOCK;
            word.p = (wchar_t*)malloc(wordlen*sizeof(wchar_t));
            if(word.p == NULL){
    			printf("Не удалось выделить память");
    			exit(1);
    		}	
            word.len=0;
            b = 0;
            while(c!=L' ' && c!=L',' && c!=L'.' && c!=L'\n'){
                word.p[i]=c;
                i++;
                word.len++;
                c=getwchar();
                if(i == wordlen){
                    wordlen += WORDBLOCK;
                    word.p = (wchar_t*)realloc(word.p, wordlen * sizeof(wchar_t));
                    if(text.p == NULL){
    					printf("Не удалось выделить память");
    					exit(1);
   					}
                }
            }
            while((c==L' ' || c==L',' || c==L'.') && a==0){
                if(c == '.'){
                    a = 1;
                }
                word.p[i] = c;
                i++;
                c = getwchar();
                if(i >= wordlen){
                    wordlen += WORDBLOCK;
                    word.p = (wchar_t*)realloc(word.p, wordlen * sizeof(wchar_t));
                    if(word.p == NULL){
    					printf("Не удалось выделить память");
    					exit(1);
    				}
                }
            }
            while(c == L'\n' && a == 0 && b < 2){
            	b++;
            	if(b < 2){
            		c = getwchar();
            	}
            }
            if(b == 1 && a == 0){
            	word.p[i] = '\n';
            	i++;
            }
            word.p[i]='\0';
            sen.p[j]=word;
            sen.len++;
            j++;
            if(j >= senlen){
                senlen += SENBLOCK;
                sen.p=(struct Word*)realloc(sen.p, senlen * sizeof(struct Word));
                if(text.p == NULL){
    				printf("Не удалось выделить память");
    				exit(1);
    			}
            }
        }while(a==0 && b<2);
        text.p[k]= sen;
        text.size++;
        k++;
        j = 0;
        if(k >= textsize){
            textsize += TEXTBLOCK;
            text.p=(struct Sentence*)realloc(text.p, textsize * sizeof(struct Sentence));
            if(text.p == NULL){
    			printf("Не удалось выделить память");
    			exit(1);
    		}
        }
        while((c==L' ' || c==L',' || c==L'.' || c==L'\n') && b < 2){
            if(c == '\n'){
                b++;
            }
            else{
                b=0;
            }
            if(b < 2){
                c = getwchar();
            }
        }
    }while(b<2);
    return text;
}


void outtext(struct Text text){
    for(int i = 0; i < text.size; i++){
        for(int j = 0; j < text.p[i].len; j++){
            printf("%S" ,text.p[i].p[j].p);
        }
        printf("\n");
    }
}
