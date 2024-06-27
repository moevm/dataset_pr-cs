#include <stdio.h>
#include <stdlib.h>

int main() {
    char *text = malloc(sizeof(char));
    char element;
    int len_text = 0;
    int Big_ch = 10;
    int c_pr_b = 0;
    int c_pr_e = 0;

    while (1) {
        element = getchar();

        if (element == '\n'|| element == '\t') {
            continue;
        }

        if (len_text == Big_ch) {
            Big_ch *= 2;
            text = (char *)realloc(text, Big_ch * sizeof(char));
        }

        if(element == ';' || element == '.' || element == '?'){
            c_pr_b += 1;
        }

        if(element == ' ' && (text[len_text - 1] == '.' || text[len_text - 1] == ';' || text[len_text - 1] == '?')){
            element = '\n';
        }

        if(element != '\t'){
            text[len_text++] = element;
        }

        if(element == '!'){
            break;
        }
    }

    text[len_text] = '\0';
    char* text_1 = malloc(sizeof(char) * len_text);
    int flag = 0;
    int lpos = 0;
    int l = 0;
    for(int i = 0; i < len_text; i++){
        if((text[i] == '.' || text[i] == ';' || text[i] == '?') && flag == 0){
            c_pr_e += 1;
            for(int j = lpos; j < i + 2; j++){
                text_1[l] = text[j];
                l++;
            }
            lpos = i + 2;
        }
        if((text[i] == '.' || text[i] == ';' || text[i] == '?') && flag == 1){
            lpos = i + 2;
            flag = 0;
        }
        if (text[i] == '7'){
            flag = 1;
        }
        if((text[i] == '!') && flag == 0){
            for(int j = lpos; j <= i; j++){
                text_1[l] = text[j];
                l++;
            }
        }
    }
    printf("%s\n", text_1);
    printf("Количество предложений до %d и количество предложений после %d", c_pr_b, c_pr_e);
    free(text);
    return 0;
}
