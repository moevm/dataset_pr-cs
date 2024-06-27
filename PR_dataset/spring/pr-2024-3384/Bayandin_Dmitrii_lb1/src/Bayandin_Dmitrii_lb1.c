#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    char** array_sentence = malloc(sizeof(char*));
    int quantity = 0;
    int memory;
    char c;
    regex_t regex;
    regmatch_t match[6];
    int kolvo;
    while(1) {
        memory = 40;
        array_sentence[quantity] = malloc(sizeof(char) * memory);
        c = getchar();
        kolvo = 0;
        while(c != '\n' && c != EOF) {
            array_sentence[quantity][kolvo] = c;
            kolvo++;
            if(kolvo + 1 == memory) {
                memory += 40;
                array_sentence[quantity] = realloc(array_sentence[quantity], memory * sizeof(char));
            }
            c = getchar();
        }
        array_sentence[quantity][kolvo] = '\0';
        array_sentence[quantity] = realloc(array_sentence[quantity], (kolvo + 1) * sizeof(char));
        if(strcmp(array_sentence[quantity], "Fin.")==0){
            free(array_sentence[quantity]);
            break;
        }
        quantity++;
        array_sentence = realloc(array_sentence, sizeof(char*) * (quantity + 1));
    }

    regcomp(&regex, "([a-z]+\\:\\/\\/)?(www\\.)?([a-z\\-\\_\\.]+)\\/([a-z\\-\\_]+\\/)*([a-z\\-\\_]+\\.[a-z0-9\\-]+)", REG_EXTENDED | REG_ICASE);
    int op = 0;
    for(int l = 0; l < quantity; ++l){
        if(regexec(&regex, array_sentence[l], 6, match, 0) == 0){
            int index_domen_end = match[3].rm_eo;
            int index_file_end = match[5].rm_eo;
            int index_domen_start = match[3].rm_so;
            int index_file_start = match[5].rm_so;
            array_sentence[l][index_domen_end] = '\0';
            array_sentence[l][index_file_end] = '\0';
            if(strstr(array_sentence[l] + index_domen_start, ".") == NULL){
                continue;
            }
            if (op == 0){
                printf("%s - %s", array_sentence[l] + index_domen_start, array_sentence[l] + index_file_start);
                op = 1;
            }
            else if (op == 1){
                printf("\n%s - %s", array_sentence[l] + index_domen_start, array_sentence[l] + index_file_start);
            }
        }
        free(array_sentence[l]);
    }
    free(array_sentence);
    regfree(&regex);
    return 0;
}
