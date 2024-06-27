#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max_sent 200                                  // максимум предложений
#define sent_symbol 1000                             // максиммум символов в предложении

int main()
{
    char* close = "Dragon flew away!";
    char* red_flag = "?";
    int kol_before = 0;                                 // кол-во предложений до 
    char** text = malloc(max_sent * sizeof(char*));
    
    for (int i = 0; i < max_sent; i++){
        text[i] = malloc((sent_symbol+1) * sizeof(char));
        for (int j = 0; j < sent_symbol; j++){
            char sent = getchar();
            text[i][j] = sent;
            if (sent == '.' || sent == ';' || sent == '?' || sent == '!') {
                text[i][j+1] = '\0';
                break;
            }
        }
        kol_before++;
        
        int sent_len = strlen(text[i]);                     
        while (text[i][0] == '\n' || text[i][0] == ' ' || text[i][0] == '\t'){
            int q = 0;
            while (q < sent_len){
                text[i][q] = text[i][q+1];
                q++;
            }
        }
        
        if(!(strcmp(text[i], close))){
            break;
        }
    }
    int kol_after = kol_before;

//удаление предложений оканчивающихся на "?"
    for (int i = 0; i < kol_after; i++){
        if (!(strcmp(&text[i][strlen(text[i])-1], red_flag))){
            int k = i;
            while (k < kol_after) {
                text[k] = text[k+1];
                k++;
            }
            kol_after--;
            i--;
        }
    }

//вывод текста
    for (int i = 0; i < kol_after; i++){
        printf("%s\n",text[i]);
    }
    kol_before--;           //т.к. "Dragon flew away!"
    kol_after--;            //      не считается
    printf("Количество предложений до %d и количество предложений после %d\n", kol_before, kol_after);

//освабождение памяти
    for(int i = 0; i < max_sent; i++){
        free(text[i]);
    }
    free(text);
    return 0;
}
