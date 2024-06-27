#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int check(char *str){
	char *fir=strtok(str, ".");
	char *sec=strtok(NULL, ".");
	char *thi=strtok(NULL, ".");
	int flag =1;
	if(strlen(fir)<4 && strlen(sec)<4 && strlen(thi)<4){
		if(flag){
			for(int i=0; i<strlen(fir); i++){if(fir[i]>'9' || fir[i]<'0'){flag=0;}}
		}
                if(flag){
                        for(int i=0; i<strlen(sec); i++){if(sec[i]>'9' || sec[i]<'0'){flag=0;}}
                }
                if(flag){
                        for(int i=0; i<strlen(thi); i++){if(thi[i]>'9' || thi[i]<'0'){flag=0;}}
                }
	}
	if(flag){
		int a=atoi(fir);
		int b=atoi(sec);
		int c=atoi(thi);
		if(a>255 || b>255 || c>255){flag=0;}
	}
return flag;
}
