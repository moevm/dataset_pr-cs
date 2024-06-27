#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define SUPERUSER_MODE_FLAG "#"
#define END_OF_TEXT "Fin."

char **read_text(int *num_of_sentences){
    char **text;
    int sentence_size = 0, sentence_capacity = 1;
    text = calloc(1,sizeof(char*));

    if (text == NULL) {
        fprintf(stderr,"Error of memory allocation");
        exit(1);
    }

    text[*num_of_sentences] = calloc(1,sizeof(char));

    if (text[0] == NULL) {
        fprintf(stderr,"Error of memory allocation");
        exit(1);
    }

    char ch;    
    while (1) {
        ch = getchar();
        if (ch == '\n'){
            text[*num_of_sentences] = realloc(text[*num_of_sentences], (sentence_capacity+1) * sizeof(char));
            
            if (text[*num_of_sentences] == NULL) {
                fprintf(stderr,"Error of memory allocation");
                exit(1);
            }

            text[*num_of_sentences][sentence_size] = '\0';
            
            (*num_of_sentences)++;
            sentence_size=0;
            sentence_capacity = 1;
            
            text = (char**)realloc(text, ((*num_of_sentences)+1)*sizeof(char*));

            if (text == NULL) {
                fprintf(stderr,"Error of memory allocation");
                exit(1);
            }

            text[*num_of_sentences] = calloc(1,sizeof(char));

            if (text[*num_of_sentences] == NULL) {
                fprintf(stderr,"Error of memory allocation");
                exit(1);
            }

            continue;
        }
        if (sentence_size >= sentence_capacity) {
            sentence_capacity *= 2;
            text[*num_of_sentences] = realloc(text[*num_of_sentences], sentence_capacity * sizeof(char));

            if (text[*num_of_sentences] == NULL) {
                fprintf(stderr,"Error of memory allocation");
                exit(1);
            }
        }
        text[*num_of_sentences][sentence_size] = ch;
        sentence_size++;

        if (ch =='.'){
            if(strstr(text[*num_of_sentences], END_OF_TEXT) != NULL){
                text[*num_of_sentences] = realloc(text[*num_of_sentences], (sentence_size) * sizeof(char));
                
                if (text[*num_of_sentences] == NULL) {
                    fprintf(stderr,"Error of memory allocation");
                    exit(1);
                }

                text[*num_of_sentences][sentence_size] = '\0';
                return text;
            }
        }
        

    }
}

int main(){

    int amount_of_sentences=0;
    char** text = read_text(&amount_of_sentences);


    size_t max_groups_amount = 5;
    char *regex_str = "([A-Za-z0-9_]+)@([A-Za-z0-9_-]+)\\:\\s*\\~\\s*(\\$|\\#)\\s(.*)";
    regex_t regex_compiled;
    regmatch_t groups_array[max_groups_amount];

    if(regcomp(&regex_compiled, regex_str, REG_EXTENDED)){
        fprintf(stderr, "Something went wrong");
        return 0;
    }

    for (int t =0; t<amount_of_sentences;t++){
        if (regexec(&regex_compiled, text[t], max_groups_amount, groups_array, 0) == 0) {
            char **groups_content =calloc(max_groups_amount, sizeof(char*));

            if (groups_content == NULL) return 0;

            for(size_t r=0;r<max_groups_amount;r++) {
                groups_content[r] = calloc(100, sizeof(char));
                
                if (groups_content[r] == NULL) {
                    fprintf(stderr,"Error of memory allocation");
                    exit(1);
                }
            }
            
            for (int i = 0; i < max_groups_amount; i++) {
                if (groups_array[i].rm_so == -1) break;
                
                for(int j=groups_array[i].rm_so;j<groups_array[i].rm_eo;j++)
                    groups_content[i][j-groups_array[i].rm_so] = text[t][j];
            }

            if (strcmp(groups_content[3], SUPERUSER_MODE_FLAG) == 0){
                printf("%s - %s\n", groups_content[1], groups_content[4]);
            }
            
            for (int i=0;i<max_groups_amount;i++) {
                free(groups_content[i]);
            }
            free(groups_content);
        } 
    }
    for (int i=0;i<amount_of_sentences;i++){
        free(text[i]);
    }
    free(text);
    regfree(&regex_compiled);
    
    return 0;
}
