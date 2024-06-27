#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 1000
int main() {
 char *offer, *t;
 char a;
 int size = MAX_SIZE;
 offer = (char *)malloc(MAX_SIZE);
 int n = -1, m = -1, len_o = 1;
 int s=10, f=1;
 do {
    do{
        a = getchar();
        if (a=='\n') continue;
        if (a=='7') f = 0;
        if (isblank(a) && len_o==1) continue;
        if (len_o<=size) {
            offer[len_o]='\0';
            offer[len_o-1]=a;
            len_o++;
        } else {
            t = (char *)realloc(offer, (size+s)*sizeof(char));
            size += s;
            if (t!=NULL){
                offer=t;
                offer[len_o-1]=a;
                offer[len_o]='\0';
                len_o++;
            }
            else {
                printf("Memory allocation error.");
                return -1;
            }
        }
        if (a=='.' || a==';' || a=='?' || a=='!') break;
    }while (1);
    if (f==0) {
        n++;
        offer[0]='\0';
        len_o=1;
        size=MAX_SIZE;
        f = 1;
    } else {
        n++;
        m++;
        printf("%s\n", offer);
        if (strcmp(offer, "Dragon flew away!")==0) break;
        offer[0]='\0';
        len_o=1;
        size=MAX_SIZE;
    }
} while(1);
free(offer);
printf("Количество предложений до %d и количество предложений после %d", n, m);
return 0;
}