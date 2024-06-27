#include <stdio.h>
#include <stdlib.h>

#define Max_symb 10000
#define Max_sent 1000

int main(){
    char c;
    int start = 0;
    int schet = 0;
    int i = 0;
    int j = 0;
    int schet_vopr = 0;
    
    char **input = malloc(Max_sent * sizeof(char*));
    for (int l=0; l<Max_sent; l++)
        input[l] = calloc(Max_symb, sizeof(char));
    
    do{
        scanf("%c", &c);
        if (start == 1){
            start=0;
            continue;
        } else{
            if ((c == '.') || (c == ';')){
                schet++;
                input[i][j] = c;
                input[i][j+1] = '\0';
                start = 1;
                i++;
                j = 0;
            } else{
                if (c == '?'){
                    schet_vopr++;
                    schet++;
                    free(input[i]);
                    for (int l=i; l<Max_sent; l++)
                        input[l]=input[l+1];
                    start = 1;
                    j = 0;
                } else {
                    input[i][j] = c;
                    j++;
                }
            }
        }
    } while (c != '!');
    
    for (int a=0; a<i+1; a++){
        int b = 0;
        while((input[a][b] !='.') && (input[a][b] !=';') && (input[a][b] !='!')){
            printf("%c", input[a][b]);
            b++;
        }
        printf("%c", input[a][b]);
        printf("\n");
    }
    
    for (int l=0; l<Max_sent; l++)
        free(input[l]);
    free(input);
    
    printf("Количество предложений до %d и количество предложений после %d", schet, schet-schet_vopr);
    
    return 0;
}