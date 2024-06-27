#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SARM '!'
void format(char * text, int N) {
    int sent_before = 0;
    int sent_after = 0;
    int cnt_words = 1;
    int ind_sent_start = 0;
    int ind_sent_end = 0;
    int k;
    int is_word;
    int delete = 0;
    for (int a = 0; text[a] != '\0'; a++){
        if (isspace(text[a])) {
        if (text[a-1] == '.' || text[a-1] == ';' || text[a-1] == '?') {
        text[a] = '\n';
        ind_sent_start = a+1;
        sent_before += 1;
        sent_after += 1;
        }
        }
        else if (isdigit(text[a])) {
            if (isspace(text[a-1]) || a==0) {
                k = a;
                is_word = 0;
                while (!isspace(text[k])) {
                    if (isalpha(text[k])) {
                        is_word = 1;
                    }
                    k++;
                }
                if (is_word==1) {
                    for (int g = a+1; g < k-1; g++) {
                        if (isdigit(text[g])) {
                        delete = 1;
                        break;
                        }
                    }
                }
                else {
                    a = k-1;
                    continue;
                }
        }
        else if (!isspace(text[a+1]) && text[a+1]!='.' &&text[a+1]!=';' && text[a+1]!='?' && text[a+1]!=',') {
            delete = 1;
        }
        if (delete) {
            sent_before += 1;
            ind_sent_end = ind_sent_start;
            int j = 0;
            do {
                ind_sent_end += 1;
                j++;
            } while (text[ind_sent_start+j]!='.' && text[ind_sent_start+j]!=';' && text[ind_sent_start+j]!='?');
            memmove(text+ind_sent_start, text+ind_sent_end+2, N-ind_sent_start);
            a = ind_sent_start;
            delete = 0;
        }
        int is_word = 0;
    }
    }
    printf("%s\n", text);
    printf("Количество предложений до %d и количество предложений после %d\n", sent_before, sent_after);
    }
int main () {
    int size = 100;
    int real_size = size;
    char * text = (char *) malloc(sizeof(char)*size);
    char * test_mem = text;
    int cnt = 0;
    char a;
    do {
        a = getchar();
        if (cnt >= real_size) {
            real_size += 20;
            test_mem = (char *) realloc(text, sizeof(char)*real_size);
            if (test_mem!=NULL) {
                text = test_mem;
            } else {
                puts("Memory allocation error!");
                free(text);
                return 1;
            }
        }
        text[cnt] = a;
        cnt++;
    } while (a != SARM);
    text[cnt] = '\0';
    format(text, cnt);
    free(text);
    return 0;}

