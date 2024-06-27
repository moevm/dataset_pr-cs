#include <stdio.h>
#include <regex.h>
#include <string.h>


int main(){
    regex_t reg;
    size_t maxG = 5;
    regmatch_t arr[maxG];
    if(regcomp(&reg,"([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+):\\ *~\\ *([$#]) (.*)\n",REG_EXTENDED))
        return 40;
    
    char buf[1000];
    while(1){
        fgets(buf,1000,stdin);
        if (strstr(buf, "Fin.")) {
            break;
        }
        if(regexec(&reg,buf,maxG,arr,0)==0){
            if(buf[arr[3].rm_so]=='#'){
                for(size_t i = arr[1].rm_so;i<arr[1].rm_eo;i++){
                    printf("%c",buf[i]);
                }
                printf(" - ");
                for(size_t i = arr[4].rm_so;i<arr[4].rm_eo;i++){
                    printf("%c",buf[i]);
                }
                printf("\n");
            }
        }
    }
    regfree(&reg);
    return  0;
}