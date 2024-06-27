#include "functions.h"

#include "subfunctions.h"
#include "structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>


struct Text format(struct Text text){
    struct Text newtext;
    int n=30, k=0, b=1;
    newtext.p=(struct Sentence*)malloc(n*sizeof(struct Sentence));
    if(newtext.p == NULL){
    	printf("Не удалось выделить память");
    	exit(1);
    }
    for(int i=0;i<(text.size-1);i++){
        for(int j=i+1;j<text.size;j++){
            if(sencmp(text.p[i],text.p[j])){
                b=0;
            }
        }
        if(b){
            newtext.p[k]=text.p[i];
            k++;
            if(k>=n){
                n+=30;
                newtext.p=(struct Sentence*)realloc(newtext.p,n*sizeof(struct Sentence));
            	if(text.p == NULL){
    				printf("Не удалось выделить память");
    				exit(1);
    			}
            }
        }
        b = 1;
    }
    newtext.p[k]=text.p[text.size-1];
    k++;
    newtext.size = k;
    return newtext;
}


void func1(struct Text text){
    for(int i = 0; i < text.size; i++){
        if(text.p[(i+1) % text.size].len >= 2){
            copywordfunc1(&text.p[i].p[0], &text.p[(i + 1) % text.size].p[1]);
        }
        else{
            free(text.p[i].p[0].p);
            text.p[i].p[0].p[0] = '\0';
            text.p[i].p[0].len = 0;
        }
    }
}


void func2(struct Text text){
    qsort(text.p, text.size, sizeof(struct Sentence), cmpfunc2);
}


void func3(struct Text text){
    int f;
    for(int i = 0; i < text.size; i++){
        f = 0;
        for(int j = 0; j < text.p[i].len; j++){
            text.p[i].p[j].f = 0;
            if(checkwordfunc3(text.p[i].p[j].p)){
                text.p[i].p[j].f = 1;
                f = 1;
            }
        }
        if(f){
            for(int j = 0; j < text.p[i].len; j++){
                if(text.p[i].p[j].f){
                    printspecialwordfunc3(text.p[i].p[j]);
                }
                else{
                    printf("%S", text.p[i].p[j].p);
                }
            }
            printf("\n");
        }
    }
}


void func4(struct Text text){
    for(int i = 0; i < text.size; i++){
        for(int j = 0; j < text.p[i].len; j++){
            func4word(text.p[i].p[j]);
        }
    }
}

void func9(struct Text text){
	int k;
	for(int i = 0; i < text.size; i++){
		for(int j = 0; j < text.p[i].len; j++){
			wchar_t* newword = (wchar_t*)malloc((wcslen(text.p[i].p[j].p) * 2 + 2) * sizeof(wchar_t));
			if(newword == NULL){
				printf("0");
				exit(1);
			}
			k = 0;
			for(int g = 0; g < text.p[i].p[j].len; g++){
				newword[k] = text.p[i].p[j].p[g];
				k++;
			}
			newword[k] = ' ';
			k++;
			for(int h = 0; h < text.p[i].p[j].p[h]; h++){
				newword[k] = text.p[i].p[j].p[h];
				k++;
			}
			newword[k] = '\0';
			free(text.p[i].p[j].p);
			text.p[i].p[j].p = newword;
			long n = 2 * text.p[i].p[j].len + 1;
			text.p[i].p[j].len = n;
		}
	}
}
