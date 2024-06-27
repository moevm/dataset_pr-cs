#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char* str= (char*)malloc(sizeof(char));
    int len =0;
    int r =1;
    int n = 0;
    int m =0;
    char c = getchar();
    while(c != '!'){
        if (c != '\t'){
            str[len++] = c;
            if (len >= r) {
                r *= 2; 
                str = (char*)realloc(str, r*sizeof(char)); 
            }
            c = getchar();
        }
    }
    str[len] ='\0';
    
    for(int i = 0; i<len; i++){
        if(((str[i] =='.') || (str[i]==';')||(str[i] == '?')) && ((str[i+1] == ' ')) && (str[i] != str[i-1])){
            n++;
        }
    }
    
    
    for(int i = 0; i<len; i++){
        if(((str[i] =='.') || (str[i]==';')||(str[i] == '?'))&& (str[i+2] != '\n') && ((str[i+1] != str[i]) && (str[i] != str[i-1])) && str[i+1] == ' '){
            str[i+1] = '\n';
            
        }
    }
    
    
    int k = 0;
    for(int i = 0; i<len; i++){
        if(str[i] =='?')
        {
            k++;
            int id = 0;
            for (int j = 0; j<i; j++){
                if(str[j] =='\n'){
                    id = j;
                    
                }
            }
            for (int u = id; u<=i; u++){
                str[u] = '\t';
            }
        }
    }
    
    
    
    m = n - k;
    for(int i = 0; i<len; i++){
            if (str[i] != '\t'){
                printf("%c", str[i]);
            }
    }
    printf("%c\n", '!');
    printf("Количество предложений до %d и количество предложений после %d", n, m);
    return 0;
}
