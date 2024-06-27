#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BLOCK_SIZE 10

int checking_for_numbers(char* text){
        for (int i = 0; i < strlen(text); i++ ){
            if ((text[i] >= '0' && text[i] <= '9' && text[i-1] >= '0' && text[i-1] <= '9' && text[i+1] >= '0' && text[i+1] <= '9') == 0){
                if (text[i] >= '0' && text[i] <= '9' && (isdigit(text[i-1]) != 0 || isalpha(text[i-1]) != 0) && (isdigit(text[i+1]) != 0 || isalpha(text[i+1]) != 0)){
                return 0;}}}
        return 1;}

int main()
{
    size_t number = 0;
    size_t capacity = BLOCK_SIZE;
    char ch = getchar();
    char* text = (char*)malloc(capacity);
    int n = 0;
    int m = 0;
    int flag = 0;

    while (1) {
        do {
            if (ch == '\n' || ch == EOF || ch == '\0')
                break;
            if (((ch == ' ')&& (flag == 0)) == 0){
            text[number++] = ch;
            flag++;}
            if (ch == '.' || ch == ';' || ch == '?' || ch == '!') {
                text[number] = '\0';
                n++;
                if (checking_for_numbers(text) == 1){
                    printf("%s\n", text);
                    m++;}
                number = 0;
                memmove(text, text + number + 1, strlen(text + number + 1) + 1);
                flag = 0;
            }

            if (number == capacity - 1) {
                capacity += BLOCK_SIZE;
                text = (char*)realloc(text, capacity);
            }
            ch = getchar();
        } while (1);

        if (ch == '\n' || ch == EOF)
            break;
    }

    free(text);
    printf("Количество предложений до %d и количество предложений после %d", n-1, m-1);
    return 0;
}
