#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


char* input_text(){
    int count_char = 1;
    int summ_memory = 200;
    char* text = malloc(summ_memory*sizeof(char));
    if(text == NULL){
        puts("Eror! Failed to allocate memory.");
        exit(1);
    }
    char ch = getchar();
    char ch_old = ' ';
    int flag = 1;
    while(1){
        if(ch == '\n' && ch_old == '\n'){
            if (text[count_char - 3] != '.'){
                text[count_char - 2] = '.';
                text[count_char - 1] = '\0';
                break;
            }
            text[count_char - 2] = '\0';
            break;
        }
        if(count_char == summ_memory){
            summ_memory += 20;
            text = realloc(text, summ_memory*sizeof(char));
        }
        if(ch_old == '.'){
            flag = 1;
        }
        if(!(ch_old == '.' && (ch == ' ' || ch == '\t')) && !(ch_old == '.' && ch == '\n') && !((ch_old == ' ' || ch_old == '\t') && (ch == ' ' || ch == '\t') && flag == 1)){
            text[count_char - 1] = ch;
            flag = 0;
            count_char++;
        }
        ch_old = ch;
        ch = getchar();
    }
    return text;
}

char** primary_text_processing(char* text, int *count_sentence){
    int quantity = 0;
    char* sentence = strtok(text, ".");
    char** array_text = malloc(sizeof(char*));
    if(array_text == NULL){
        puts("Eror! Failed to allocate memory.");
        exit(1);
    }
    while(sentence != NULL){
        int flag = 0;
        for(int j = 0; j < quantity; j++){
            if(strcasecmp(sentence, array_text[j]) == 0){
                flag = 1;
                break;
            }
        }
        if(!flag){
            array_text = realloc(array_text, (quantity + 1)*sizeof(char*));
            array_text[quantity] = malloc(sizeof(char)*(strlen(sentence) + 1));
            if(array_text[quantity] == NULL){
                puts("Eror! Failed to allocate memory.");
                exit(1);
            }
            strcpy(array_text[quantity], sentence);
            quantity++;
        }
        sentence = strtok(NULL, ".");

    }
    *count_sentence = quantity;
    return array_text;

}

void print_text(char** array_text, int *count_sentence){
    for(int i = 0; i < *count_sentence; i++){
        printf("%s.\n", array_text[i]);
    }
}


void search_time(char** array_text, int *count_sentence){
    for(int i = 0; i < *count_sentence; i++){
        int hours = 0;
        int minutes = 0;
        int seconds = 0;
        int flag = 0;
        char* word;
        while((word = strtok(array_text[i], " ,")) != NULL){
            array_text[i] = NULL;
            if(strstr(word, "sec") != NULL){
                int sec;
                if (sscanf(word, "%dsec", &sec) == 1){
                    seconds += sec;
                    flag = 1;
                }
            }
        }
        if(flag){
        minutes = seconds / 60;
        seconds = seconds % 60;
        hours = minutes / 60;
        minutes = minutes % 60;
        printf("%02d:%02d:%02d\n", hours, minutes, seconds);
        }
    }
}


void delete_first_word(char** array_text, int *count_sentence){
    for(int i = 0; i < *count_sentence; i++){
        char* sentence = malloc(sizeof(char)*(strlen(array_text[i]) + 1));
        sentence[0] = '\0';
        char* next_word = strtok(array_text[i], " ");
        next_word = strtok(NULL, " ");
        while(next_word != NULL){
            strcat(sentence, next_word);
            next_word = strtok(NULL, " ");
            if(next_word != NULL){
                strcat(sentence, " ");
            }
            else{
                strcat(sentence, ".");
            }
        }
        sentence = realloc(sentence, (strlen(sentence)+1)*sizeof(char));
        printf("%s\n", sentence);
        free(sentence);
    }
}

void delete_sentence(char** array_text, int *count_sentence){
    for(int i = 0; i < *count_sentence; i++){
        int flag = 0;
        int qantity_word = 0;
        char* sentence = malloc(sizeof(char)*(strlen(array_text[i]) + 1));
        if(sentence == NULL){
            puts("Eror! Failed to allocate memory.");
            exit(1);
        }
        sentence[0] = '\0';
        char* word;
        word = strtok(array_text[i], " ");
        size_t len_word = strlen(word);
        if(word[len_word-1] == ','){
            len_word -= 1;
        }
        while(word != NULL){
            strcat(sentence, word);
            if(len_word == strlen(word)){
                flag++;
            }
            else if(word[strlen(word)-1] == ',' && len_word == strlen(word) - 1){
                flag++;
            }
            word = strtok(NULL, " ");
            if(word != NULL){
                strcat(sentence, " ");
            }
            qantity_word++;
        }
        sentence[strlen(sentence)] = '\0';
        if(flag != qantity_word){
            printf("%s.\n", sentence);
            free(sentence);
        }
    }
}


int number_of_lowercase_letters(const char *sentence){
    int count = 0;
    for(int i = 0; sentence[i] != '\0'; i++){
        if(islower(sentence[i])){
            count++;
        }
    }
    return count;
}


int cmp(const void *a, const void *b){
    const char *sentence1 = *(const char **)a;
    const char *sentence2 = *(const char **)b;
    return number_of_lowercase_letters(sentence2) - number_of_lowercase_letters(sentence1);
}


void sort_sentence(char** array_text, int *count_sentence){
    qsort(array_text, *count_sentence, sizeof(char *), cmp);
    for(int i = 0; i < *count_sentence; i++){
        printf("%s.\n", array_text[i]);
    }
}
char** count_word(char** array_text, int *count_sentence, int *count){
    char** word = malloc(sizeof(char*));
    int k = 0;
    char* istr;
    for(int i = 0; i < *count_sentence; i++){
        char* sent = malloc((strlen(array_text[i])+1)*sizeof(char));
        strcpy(sent, array_text[i]);
        istr = strtok(sent, " ,");
        while(istr != NULL){
            int flag = 0;
            if(flag == 0){
                word = realloc(word, sizeof(char*)*(k+1));
                word[k] = malloc((strlen(istr) + 1) * sizeof(char));
                strcpy(word[k], istr);
                k += 1;
            }
            istr = strtok(NULL, " ,");
        }
        free(sent);

    }
    *count = k;
    return word;
}
void print_zashita(char** array_text, char** word, int *count_sentence, int *count){
    char* istr;
    for(int j = 0; j < *count_sentence; j++){
        char* sentence = malloc((strlen(array_text[j])+1)*sizeof(char));
        sentence[0] = '\0';
        istr = strtok(array_text[j], " ,");
        int y = 0;
        while(istr != NULL){
            int flag = 0;
            for(int i = 0; i < *count; i++){
                if(strcasecmp(istr, word[i]) == 0){
                    flag += 1;
                }
            }
            if(flag == 1){
                if(y != 0){
                strcat(sentence, " ");
                }
                strcat(sentence, istr);
                y += 1;
            }
            istr = strtok(NULL, " ,");
        }
        if(sentence[0] != '\0'){
        printf("%s.\n", sentence);
        }
        free(sentence);
    }
}

int main(){
    puts("Course work for option 4.11, created by Dmitrii Bayandin");
    int number;
    scanf("%d", &number);
    getchar();
    int count_sentence = 0;
    int count= 0;
    char** array_text;
    switch(number)
    {
    case 0:
        array_text = primary_text_processing(input_text(), &count_sentence);
        print_text(array_text, &count_sentence);
        break;
    case 1:
        array_text = primary_text_processing(input_text(), &count_sentence);
        search_time(array_text, &count_sentence);
        break;
    case 2:
        array_text = primary_text_processing(input_text(), &count_sentence);
        delete_first_word(array_text, &count_sentence);
        break;
    case 3:
        array_text = primary_text_processing(input_text(), &count_sentence);
        delete_sentence(array_text, &count_sentence);
        break;
    case 4:
        array_text = primary_text_processing(input_text(), &count_sentence);
        sort_sentence(array_text, &count_sentence);
        break;
    case 5:
        puts(
            "List of commands:\n"
            "0 - Text output after the initial mandatory processing\n"
            "1 - In each sentence, find all words of the form <number>sec and print the sum of the hours\n"
            "2 - Delete the first word in each sentence.\n"
            "3 - Delete all sentences that have the same length of all words.\n"
            "4 - Sort the sentences by reducing the number of lowercase letters in it.\n"
            "5 - Output help about the functions that the program implements."
        );
        break;
    case 9:
        array_text = primary_text_processing(input_text(), &count_sentence);
        char** text = count_word(array_text, &count_sentence, &count);
        print_zashita(array_text, text, &count_sentence, &count);
        for(int l = 0; l < count_sentence; l++){
            //printf("%s\t", text[l]);
            free(text[l]);
        }
        free(text);
        break;
    default:
        puts("Error, the entered number must be between 0 and 5!");
        return 0;
    }
    if(number != 5){
    for (int i = 0; i < count_sentence; i++){
        free(array_text[i]);
    }
    free(array_text);
    }
    return 0;
}
