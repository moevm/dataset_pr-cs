#include "struct.h"
#include "sio.h"
#include <wchar.h>
#include <wctype.h>
#include <locale.h>


void func1(struct Text text){
	for(int i=0;i<text.size;i++){
		for(int j=0; j<text.p[i].len-1;j++){
			for(int l=j+1;l<text.p[i].len;l++){
				if(!(wcsncasecmp(text.p[i].p[j].p,text.p[i].p[l].p, text.p[i].p[j].len))){
					text.p[i].p[j].k = 2;
					text.p[i].p[l].k = 2;
				}
			}	
			for(int k=i+1; k<text.size; k++){
				for(int u=0; u<text.p[k].len; u++){
					if(!(wcsncasecmp(text.p[i].p[j].p,text.p[k].p[u].p, text.p[i].p[j].len))){
						text.p[i].p[j].k = 2;
						text.p[k].p[u].k = 2;
					}
				}
			}
		}	
		int j = text.p[i].len - 1;
		for(int k=i+1; k<text.size; k++){
            for(int u=0; u<text.p[k].len; u++){
                    if(!(wcsncasecmp(text.p[i].p[j].p,text.p[k].p[u].p, text.p[i].p[j].len))){
						text.p[i].p[j].k = 2;
						text.p[k].p[u].k = 2;
                    }
            }
		}
	}
	outputfunc1(text);
}
