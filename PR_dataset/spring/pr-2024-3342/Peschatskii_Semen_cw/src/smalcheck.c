#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int smalcheck(char *str){
        int flag=1;
        if(strlen(str)<4){
                for(int i=0; i<strlen(str); i++){if(str[i]>'9' || str[i]<'0'){flag=0;}}
        }
        if(flag){
                int a=atoi(str);
                if(a>255){flag=0;}
        }
return flag;
}
