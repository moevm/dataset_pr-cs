#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 300
#define M 800

int string_compare(char *str_one, char *str_two){
      while (*str_one && *str_two && (*str_one == *str_two)) {
            str_one++;
            str_two++;
        }
        if (!*str_two) {
            return 1;
        }
        return 0;

}

int substr_search(char *str, char *substr) {
    int count = 0;
    while (*str) {
        char *s = str;
        char *ss = substr;
        if (string_compare(s,ss)) {
            return count;
        }

        str++;
        count++;
    }
    return -1;
}


int is_letter(char letter){
    if ((letter>='A' && letter<='Z') || (letter>='a' && letter<='z')){
        return 1;
    }
     return 0;
}
int is_not_letter_nearby(char *massiv, int index,int len_el){
    if((index==0 || !(is_letter(massiv[index-1])))  && !(is_letter(massiv[index+len_el]))){
        return 1;
    }
     return 0;
}
int format_text(char **text,int *del_str) {
    char *all_text = (char *)malloc(N * M * sizeof(char));
    fgets(all_text, N * M * sizeof(char), stdin);
    int number_el = 0;
    for (int i = 0; i < N; i++, number_el++) {
        text[i] = malloc(M *sizeof(char));
        int j;
        for (j = 0; j < M && number_el < N * M; number_el++) {
            if (j==0 && (all_text[number_el] == '\t' || all_text[number_el] == ' ')) {
                continue;
            }
            else{
                text[i][j] = all_text[number_el];
                j++;
            }
            if (all_text[number_el] == '.' || all_text[number_el] == '?' || all_text[number_el] == ';' || string_compare(text[i],"Dragon flew away!")) {
                break;
            }

        }
        text[i][j] = '\n';
        text[i][j+1] = '\0';
        int three_five_index = substr_search(text[i], "555");
        if (three_five_index>=0 && is_not_letter_nearby(text[i],three_five_index,3)){
            free(text[i]);
            i--;
            (*del_str)++;
            continue;
        }
        if (all_text[number_el + 1] == '\0') {
            free(all_text);
            return i;
        }
    }
    free(all_text);
    return 0;
}

int main() {
    int count_del_str = 0;
    int *del_str = &count_del_str;
    char **text = malloc(N * sizeof(char*));
    int count_str = format_text(text, del_str);
    for (int i = 0; i < count_str; i++) {
        fputs(text[i], stdout);
        free(text[i]);
    }
    free(text);
    count_str--;
    printf("Количество предложений до %d и количество предложений после %d", count_str+count_del_str, count_str);


    return 0;
}
