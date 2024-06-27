#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define RESET_COLOR "\e[0m"

//preventing allocation error
#define MALLOC_ERR {puts("Error: memory allocation error.");}

//struct for sentences with products for task 4
struct SentencesWithProducts{char* sentence; long long product;};

struct WordSum {char* word; long long sum;};

//function prototypes
int sent_product_compare(const void* a, const void* b);

int word_comp(const void* a, const void* b);

int read_str(char*** main_str);

int strcmp_lc(char** main_str, int sentence_count);

void func_task1(char** main_str, int sentence_count);

void func_task2(char** main_str, int sentence_count);

void func_task3(char** main_str, int sentence_count);

void func_task4(char** main_str, int sentence_count);

void func_task9(char** main_str, int sentence_count);

void print_str(char** main_str, int sentence_count);

void show_help();
void memory_free(char*** main_str, int* sentence_count);

//"main" section
int main() {
        puts("Course work for option 4.12, created by Aleksandr Spiridonov.");

        int option;
        scanf("%lc", &option);
        if(((int)option < 48 || (int)option > 53) && (char)option != '9') {
                puts("Error: wrong option value.");
                return 1;
        }
        
        option = option - 48;

        char** main_str;
        int sentence_count;
        if(option != 5) {
                sentence_count = read_str(&main_str);
        }

        switch(option) {
                case 0: 
                        print_str(main_str, sentence_count);
                        break;
                case 1:
                       func_task1(main_str, sentence_count);
                       break;
                case 2:
                        func_task2(main_str, sentence_count);
                        break;
                case 3:
                        func_task3(main_str, sentence_count);
                        break;
                case 4:
                        func_task4(main_str, sentence_count);
                        break;
                case 5:
                        show_help();
                        break;
                        
                case 9:
                        func_task9(main_str, sentence_count);
                        break;
        }
        
	for (int i = 0; i < sentence_count; i++){free(main_str[i]);}
	free(main_str);
        return 0;
}


//function definitions
int sent_product_compare(const void* a, const void* b){
        struct SentencesWithProducts sent_1 = *(struct SentencesWithProducts*)a;
        struct SentencesWithProducts sent_2 = *(struct SentencesWithProducts*)b;
        
        return sent_1.product - sent_2.product;
}

int word_comp(const void* a, const void* b){
        struct WordSum word1 = *(struct WordSum*)a;
        struct WordSum word2 = *(struct WordSum*)b;
        
        return word1.sum - word2.sum;
}

int read_str(char*** main_str){
        
        int sentence_count = 0;
        int sent_size = 60;
        int current_index = 0;
        
        int line_feed_count = 0;
        int space_count = 0;
        
        (*main_str) = (char**)malloc((sentence_count+2)*sizeof(char*));
        if(!(*main_str)) MALLOC_ERR
        
        (*main_str)[sentence_count] = (char*)malloc(sent_size*(sizeof(char)));
        if(!(*main_str)[sentence_count]) MALLOC_ERR
        
        char sym;
        
        while(line_feed_count != 2){
                if (sent_size - current_index <= 3){
                        sent_size += 20;
                        (*main_str)[sentence_count] = (char*)realloc((*main_str)[sentence_count], sent_size*sizeof(char));
                        if(!(*main_str)[sentence_count]) MALLOC_ERR
                }
                sym = getchar();
                
                if (sym == '\n'){line_feed_count += 1;}
                
                if (isspace(sym)){space_count++;}
                else{space_count = 0; line_feed_count = 0;}
                
                if (isspace(sym) && (space_count > 1 || current_index == 0)){(*main_str)[sentence_count][current_index] = '\0'; continue;}
                
                (*main_str)[sentence_count][current_index] = sym;
                
                if (sym == '.'){
                        if (strcmp_lc((*main_str), sentence_count) || ((*main_str)[sentence_count][0] == '.')){
                                free((*main_str)[sentence_count]);
                                (*main_str)[sentence_count] = (char*)malloc(sent_size*(sizeof(char)));
                        }else{
                                (*main_str)[sentence_count][current_index+1] = '\0';
                                
                                sentence_count += 1;
                                sent_size = 60;  
                                
                                (*main_str)[sentence_count] = (char*)malloc(sent_size*(sizeof(char)));
                                if(!(*main_str)[sentence_count]) MALLOC_ERR
                                
                                (*main_str) = (char**)realloc(*main_str, (sentence_count+2)*sizeof(char*));
                                if(!(*main_str)) MALLOC_ERR
                                
                        }
                        current_index = 0;
                }else{current_index += 1;}
                
        }
        if ((*main_str)[sentence_count][0] == '\0'){free((*main_str)[sentence_count]); sentence_count--;}
        
        if ((*main_str)[sentence_count][strlen((*main_str)[sentence_count])-1] != '.'){
                (*main_str)[sentence_count][strlen((*main_str)[sentence_count])-1] ='.';
                (*main_str)[sentence_count][strlen((*main_str)[sentence_count])] = '\0';
        }
        
        return sentence_count+1;
}

//this function was created because the original one (strcmp) compares in a case-sensitive manner.
int strcmp_lc (char** main_str, int sentence_count){
        int flag;
        for (int i = 0; i < sentence_count; i++){
                flag = 1;
                for (int j = 0; j < strlen(main_str[i]); j++){
                        if (tolower(main_str[i][j]) != tolower(main_str[sentence_count][j])){flag = 0; break;}
                }
                if (flag){return 1;}
        }
        return 0;
}

void func_task1(char** main_str, int sentence_count){
        char* word = malloc(10*sizeof(char));
        int flag = 1;
        for (int i = 0; i < sentence_count; i++){
                if ((strstr(main_str[i], "banana ") || strstr(main_str[i], "apple ") || strstr(main_str[i], "banana.") || strstr(main_str[i], "apple.")) && (strstr(main_str[i], " banana") || strstr(main_str[i], " apple") || main_str[i][0] == 'b')){               
                        for (int j = 0; j < strlen(main_str[i]); j++){
                                if ((main_str[i][j] == ' ' || main_str[i][j] == '.') && (!flag)){printf(RESET_COLOR); flag = 1;}        

                                if ((main_str[i][j] == ' ' && main_str[i][j+1] == 'b' && flag)){
                                        memcpy(word, &main_str[i][j+1], 7);
                                        
                                        if ((!strcmp(word, "banana ")) || (!strcmp(word, "banana."))){printf(YELLOW); flag = 0;}
                                        
                                        free(word);
                                        word = malloc(10*sizeof(char));
                                        
                                }else if ((j == 0 && main_str[i][j] == 'b' && flag)){
                                         memcpy(word, &main_str[i][j], 7);
                                        
                                        if ((!strcmp(word, "banana ")) || (!strcmp(word, "banana."))){printf(YELLOW); flag = 0;}
                                        
                                        free(word);
                                        word = malloc(10*sizeof(char));
                                        
                                }else if ((main_str[i][j] == ' ' && main_str[i][j+1] == 'a' && flag)){
                                        memcpy(word, &main_str[i][j+1], 6);
                                
                                        if ((!strcmp(word, "apple ")) || (!strcmp(word, "apple."))){printf(GREEN); flag = 0;}
                                        
                                        free(word);
                                        word = malloc(10*sizeof(char));
                                        
                                }else if ((j == 0 && main_str[i][j] == 'a' && flag)){
                                        memcpy(word, &main_str[i][j], 6);
                                
                                        if ((!strcmp(word, "apple ")) || (!strcmp(word, "apple."))){printf(GREEN); flag = 0;}
                                        
                                        free(word);
                                        word = malloc(10*sizeof(char));
                                }
                               printf("%c", main_str[i][j]);
                               if (main_str[i][j] == '.'){printf("\n");}
                        }
                }
        }
        free(word);
}

void func_task2(char** main_str, int sentence_count){
        for (int i = 0; i < sentence_count;i++){
                for (int j = 0; j < strlen(main_str[i]); j++){
                        if (isdigit(main_str[i][j])) {main_str[i][j] = 'D';}
                        else{main_str[i][j] = tolower(main_str[i][j]);}
                }
        }
        print_str(main_str, sentence_count);
}

void func_task3(char** main_str, int sentence_count){
        for (int i = 0; i < sentence_count; i++){
                if (strlen(main_str[i]) <= 15){puts(main_str[i]);}
        }
}

void func_task4(char** main_str, int sentence_count){
        struct SentencesWithProducts* sentences_struct = (struct SentencesWithProducts*)malloc(sentence_count*sizeof(struct SentencesWithProducts));
        if(!sentences_struct) MALLOC_ERR
        
        for (int i = 0; i < sentence_count; i++){
                char* str_ind_i = main_str[i];
                int str_i_len = strlen(str_ind_i);
                
                struct SentencesWithProducts sent_struct;
                sent_struct.sentence = (char*)malloc(str_i_len);
                if(!sent_struct.sentence) MALLOC_ERR
                
                sent_struct.product = 1;
                memcpy(sent_struct.sentence, str_ind_i, str_i_len);
                
                for (int j = 0; j < str_i_len; j++){
                        if (isdigit(str_ind_i[j])){
                                int digit = (int)str_ind_i[j] - 48;
                                sent_struct.product *= digit;
                        }
                }

                sentences_struct[i] = sent_struct;
        }
        qsort(sentences_struct, sentence_count, sizeof(struct SentencesWithProducts), sent_product_compare);
        int j;
        for (int i = 0; i < sentence_count; i++){
                j = 0;
                while (sentences_struct[i].sentence[j] != '.'){
                        printf("%c", sentences_struct[i].sentence[j]);
                        j++;
                }
                printf(".\n");
        }
        
        for (int i = 0; i < sentence_count; i++){free(sentences_struct[i].sentence);}
        free(sentences_struct);
}

void func_task9(char** main_str, int sentence_count){
        for (int i = 0; i < sentence_count; i++){
                char* sent_ = strdup(main_str[i]);
                
                int n = 10;
                struct WordSum* words = malloc(sizeof(struct WordSum)*n);
                if (!words) MALLOC_ERR
                
                char* word_tok = strtok(sent_, " ,");
                int count = 0;
                while(word_tok != NULL){
                      if (n - count <= 3){n += 10; words = realloc(words, sizeof(struct WordSum)*n);}
                      struct WordSum word_;
                      
                      if (!word_.word) MALLOC_ERR
                      word_.word = word_tok;   
                      
                      if (word_tok != NULL){words[count] = word_; count++;}
                      
                      word_tok = strtok(NULL, " ,");
                }
                int o = 0;
                while (words[count-1].word[o] != '.') {o++;}
                      words[count-1].word[o] = '\0';
                    
                
                for (int j = 0; j < count; j++){
                        words[j].sum = 0;
                        for (int u = 0; u < strlen(words[j].word); u++){
                                if (isdigit(words[j].word[u])){
                                        int digit = (int)words[j].word[u] - 48;
                                        words[j].sum += digit;
                          }
                        }
                
                }
                qsort(words,count, sizeof(struct WordSum), word_comp);
                
                for (int j = 0; j < count; j++){
                        for(int u = 0; u < strlen(words[j].word); u++){
                                printf("%c", words[j].word[u]);
                        }
                        if (count - j != 1){printf(" ");}
                        
                }
                printf(".\n");
                
                free(words);
        }
}

void print_str(char** str, int sentence_count){
        for(int i = 0; i < sentence_count; i++) {puts(str[i]);}
}

void show_help(){
        puts("This program is a text processor.");
        puts("First, you need to select mode from range 0-5, where:");
        puts("0 - print text after primary processing;");
        puts("1 - print all sentences containing words 'banana' or 'apple', colored with yellow or green respectively.");
        puts("2 - print text, replacing all letters with lower case ones and all digits with 'D'.");
        puts("3 - print text, removing all sentences longer than 15.");
        puts("4 - print text, sorting sentences in it by product of all numbers in sentence.");
        puts("5 - show this help.");
}
