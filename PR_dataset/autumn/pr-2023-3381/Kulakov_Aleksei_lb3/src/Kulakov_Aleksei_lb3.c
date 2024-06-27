
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    int buf_sz = 1024, rl_size = 0;
    char* buffer = malloc(buf_sz * sizeof(char));
    int c;
    while(1){
        c = getchar();
        if(buf_sz == rl_size){
            buf_sz *= 2;
            buffer = realloc(buffer,buf_sz);
        }
        buffer[rl_size++] = (char)c;
        if((char)c == '!'){
            break;
        }
    }
    buffer[rl_size] = '\0';
    int k = 0, del = 0, pos = 0, len = 0;
    while(pos < rl_size){
        if(buffer[pos] == '.' || buffer[pos] == ';' || buffer[pos] =='?' ){
            k++;
            buffer[pos+1] = '7';
            pos+=2;
            len = 0;
        }
        else{
            len++;
            if(buffer[pos] == '\t' && len == 1){
                buffer[pos] = '7';
            }
            else if(buffer[pos] == '7'){
                int j = pos+1;
                while(buffer[j] != '.' && buffer[j] != ';' && buffer[j] !='?'){
                    j++;
                }
                for(int i = pos - len+1; i <= j+1;i++){
                    buffer[i] = '7';
                }
                pos = j+2;
                len = 0;
                k++;
                del++;
            }
            else{
                pos++;
            }
        }
    }
    for(int i = 0; i < rl_size;i++){
        if(buffer[i] != '7'){
            printf("%c",buffer[i]);
        }
        if(buffer[i] == '.' || buffer[i] == ';' || buffer[i] =='?' || buffer[i] == '!'){
            printf("\n");
        }
    }
    free(buffer);
    printf("Количество предложений до %i и количество предложений после %i",k,k-del);
    return 0;
}

