#include "sio.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

struct Text inttext(){
	struct Text text;
	int sizeoftext = 69; 
	text.p=(struct Sentence*)malloc(sizeoftext*sizeof(struct Sentence));
	if(text.p==NULL){
            	printf("Ошибка выделения памяти");
            	exit(1);
            }
	text.size=0;
	int j=0, k=0, n=30, b=0, a=0;
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
        sen.p = (struct Word*)malloc(n*sizeof(struct Word));
        if(sen.p==NULL){
            	printf("Ошибка выделения памяти");
            	exit(1);
            }
	    sen.len=0;
        do{
			int i = 0;
			int lenofword = 30;
			struct Word word;
            word.p = (wchar_t*)malloc(lenofword*sizeof(wchar_t));
            if(word.p==NULL){
            	printf("Ошибка выделения памяти");
            	exit(1);
            }
			word.len=0;
			b=0;
            while(c!=L' ' && c!=L',' && c!=L'.' && c!=L'\n'){
				word.p[i]=c;
				i++;
				word.len++;
				c=getwchar();
				if(i == lenofword){
					lenofword += 30;
					word.p = (wchar_t*)realloc(word.p, lenofword * sizeof(wchar_t));
					if(word.p==NULL){
				    	printf("Ошибка выделения памяти");
				    	exit(1);
				    }
				}
			}
			
			while((c==L' ' || c==L',' || c==L'.' ) && a==0){
				if(c == '.'){
					a = 1;
				}
				else{
					b = 0;
				}
				word.p[i] = c;
				i++;
				c = getwchar();	
				if(i == lenofword){
                    lenofword += 30;
                    word.p = (wchar_t*)realloc(word.p, lenofword * sizeof(wchar_t));
                    if(word.p==NULL){
				    	printf("Ошибка выделения памяти");
				    	exit(1);
				    }
                }
			}
			while(c==L'\n' && b<2){
				b++;
				if(b<2){
					c = getwchar();
				}
			}
			if(b==1  && a==0){
				word.p[i]='\n';
				i++;
			}
            word.p[i]='\0';
            word.k=0;
            sen.p[j]=word;
	    	sen.len++;
            j++;
            if(j>=n){
                n+=30;
            	sen.p=(struct Word*) realloc(sen.p,n*sizeof(struct Word));
            	if(sen.p==NULL){
		        	printf("Ошибка выделения памяти");
		        	exit(1);
		        }
    		}
        }while(a==0 && b<2);
        text.p[k]= sen;
		text.size++;
        k++;
		j = 0;
		if(k>=sizeoftext){
			sizeoftext+=30;
			text.p=(struct Sentence*)realloc(text.p,sizeoftext*sizeof(struct Sentence));
			if(text.p==NULL){
            	printf("Ошибка выделения памяти");
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


void outword(struct Word word){
	for(int i = 0; i < word.len; i++){
		printf("%C", word.p[i]);
	}
	printf("\n");
}


void outputfunc1(struct Text text){
	for(int i = 0; i < text.size; i++){
		for(int j = 0; j < text.p[i].len; j++){
			if(text.p[i].p[j].k != 2){
				outword(text.p[i].p[j]);
			}
		}
	}
}
	