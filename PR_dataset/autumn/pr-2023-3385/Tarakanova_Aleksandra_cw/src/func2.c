#include "func2.h"
#include "sio.h"
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

int vesoc(int a){
	if(a%4){
		return 0;
	}
	if(a%100==0 && a%400){
		return 0;
	}
	return 1;
}


int mes(struct Word word){
	wchar_t* m1=L"января \0";
	wchar_t* m2=L"февраля \0";
	wchar_t* m3=L"марта \0";
	wchar_t* m4=L"апреля \0";
	wchar_t* m5=L"мая \0";
	wchar_t* m6=L"июня \0";
	wchar_t* m7=L"июля \0";
	wchar_t* m8=L"августа \0";
	wchar_t* m9=L"сентября \0";
	wchar_t* m10=L"октября \0";
	wchar_t* m11=L"ноября \0";
	wchar_t* m12=L"декабря \0";
	if(!wcscasecmp(word.p,m1)){     
		return 131;
	}
	if(!wcscasecmp(word.p,m3)){ 
		return 331;
	}
	if(!wcscasecmp(word.p,m5)){ 
		return 531;
	}
	if(!wcscasecmp(word.p,m7)){ 
		return 731;
	}
	if(!wcscasecmp(word.p,m8)){ 
		return 831;
	}
	if(!wcscasecmp(word.p,m10)){ 
		return 1031;
	}
	if(!wcscasecmp(word.p,m12)){ 
		return 1231;
	}
	if(!wcscasecmp(word.p,m4)){ 
		return 430;
	}
	if(!wcscasecmp(word.p,m6)){ 
		return 630;
	}
	if(!wcscasecmp(word.p,m11)){ 
		return 1130;
	}
	if(!wcscasecmp(word.p,m9)){ 
		return 930;
	}
	if(!wcscasecmp(word.p,m2)){ 
		return 228;
	}
	return 0;
}


void func2(struct Text text){
	for(int i=0; i<text.size; i++){
		wchar_t* g = L"г.\0";
		int l= text.p[i].len -1, b=0, a=0, c=0;
		if(! wcscasecmp(text.p[i].p[l].p, g)){
			if(text.p[i].p[l-1].len <= 4){
				for(int j=0;text.p[i].p[l-1].p[j]!=' ';j++){
					if(iswdigit(text.p[i].p[l-1].p[j])){
						b=b*10+(int)text.p[i].p[l-1].p[j]-48;
					}
					else{
						b=0;
					}
				}
				if(b){
					if(vesoc(b)){
						a=1;
					}
					int m=mes(text.p[i].p[l-2])%100;
					wchar_t d=(mes(text.p[i].p[l-2])/1000) + 48;
					wchar_t e=((mes(text.p[i].p[l-2])/100)%10) + 48;
					if(m==28){
						m+=a;
					}
					if(m){
						if(text.p[i].p[l-3].len <= 2){
							for(int k=0; text.p[i].p[l-3].p[k]!=' ';k++){
								if(iswdigit(text.p[i].p[l-3].p[k])){
									c=c*10+(int)text.p[i].p[l-3].p[k]-48;
								}
								else{
									c=0;
								}
							}
							if(c){
								if(c<=m){
									text.p[i].len-=3;
									text.p[i].p[l-3].p[2]='/';
									text.p[i].p[l-3].p[3]=d;
									text.p[i].p[l-3].p[4]=e;
									text.p[i].p[l-3].p[5]='/';
									text.p[i].p[l-3].p[6]=text.p[i].p[l-1].p[0];
									text.p[i].p[l-3].p[7]=text.p[i].p[l-1].p[1];
									text.p[i].p[l-3].p[8]=text.p[i].p[l-1].p[2];
									text.p[i].p[l-3].p[9]=text.p[i].p[l-1].p[3];
									if(c<10){
										text.p[i].p[l-3].p[0]='0';
										text.p[i].p[l-3].p[1]=text.p[i].p[l-3].p[0];
									}
									else{
										text.p[i].p[l-3].p[0]=text.p[i].p[l-3].p[0];
										text.p[i].p[l-3].p[1]=text.p[i].p[l-3].p[1];
									}
								}
							}
						}
					}		
				}
			}	
		}	
	}
	outtext(text);
}

