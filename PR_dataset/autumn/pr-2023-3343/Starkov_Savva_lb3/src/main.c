#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_CHUNK 20
char* get_text_input(const char* end_symbol);
void remove_lead_spaces(char* str);
char** Format_text(char** split_text,int* sentence_number,int* sentense_number_after);
char** split_text(char* input_text,int* sentence_number,const char* splitters);
int main() {
    // main
    int sentence_number =0;
    int sentence_number_after = 0;
    char* end_symbol ="!";
    const char* splitters = ".?;";
    char* input_text = get_text_input(end_symbol);
    char** text = split_text(input_text,&sentence_number,splitters);
    char ** formatted_text = Format_text(text,&sentence_number,&sentence_number_after);
    for(int i = 0;i<=sentence_number_after;i++){
        printf("%s\n", formatted_text[i]);
        free(formatted_text[i]);
    }

    printf("Количество предложений до %i и количество предложений после %i",sentence_number-1,sentence_number_after);
//    printf("%i\n",sentence_number_after-1);

    return 0;
}

char* get_text_input(const char* end_symbol) {
    unsigned int size = 0, capacity = MEMORY_CHUNK;
    char ch;
    char *text = malloc(sizeof(char *));
    while ((ch = getchar()) != *end_symbol) {
        if (ch != '\n') {
            if (size >= capacity - 1) {
                capacity += MEMORY_CHUNK;
                text = realloc(text, capacity * sizeof(char));
            }
            text[size++] = ch;
        }
    }
    text = realloc(text, (size + 2) * sizeof(char));
    text[size++] = *end_symbol;
    text[size] = '\0';
//    printf("Инпут текст попало\n");
    return text;

}

char** split_text(char* input_text,int* sentence_number,const char* splitters){
    int count_sentences = 0;
    int end = 0;
    char** splitted_text = malloc(sizeof(char*));
    for (int i = 0;i<=(int)strlen(input_text);i++){
//        printf("Залетел в массив\n");
        if (strchr(splitters,input_text[i])!=NULL){
            count_sentences++;
//            printf("нашел строку и пытается ее аллоцировать\n");
            splitted_text = realloc(splitted_text,count_sentences*sizeof(char*));
            splitted_text[count_sentences-1] = malloc((end+2)*sizeof(char));

//            printf("Добавляет в аллоцированную память строку из инпут текста\n");
            int chr_counter = 0;
            for (int j = end; j >= 0; j--) {
                splitted_text[count_sentences - 1][chr_counter++] = input_text[i - j];
            }
//            printf("Попало в сплит текст\n");
            splitted_text[count_sentences - 1][chr_counter] = '\0';
            remove_lead_spaces(splitted_text[count_sentences - 1]);
            end = 0;
            continue;

        }
        end++;



    }
    *sentence_number = count_sentences;
    return splitted_text;

}

void remove_lead_spaces(char* str) {
    char* start = str;

    while (*start && (*start == ' ' || *start == '\t' ||  *start == '\n')) {
        start++;
    }

    memmove(str, start, strlen(start) + 1);
}
//
char** Format_text(char** split_text,int* sentence_number,int* sentense_number_after){
    int j = 0;
    int count_sentenc = 0;
    char** new_text_splitted = (char**)malloc(*sentence_number *  sizeof (char*)+1);
    for(int i = 0;i<=*sentence_number;i++){
        //перебор предложений
        //проверка на присутствие в предложении цифры 7 и добавление предложения без 7
            if (((strchr(split_text[i],'7')==NULL) && (strchr(split_text[i],'!')==NULL)&&split_text[i]!=NULL)){
                    //копирование
                    //выделение памяти для строки
                    //копирование строки из изходного массива
                    if(strndup(split_text[i], strlen(split_text[i])*sizeof(char))!=NULL)
                        new_text_splitted[j] = strndup(split_text[i], strlen(split_text[i])*sizeof(char));
        //          //strcpy(new_text_splitted[j],split_text[i]);
                    //итератор нового массива
                    j++;
                    count_sentenc++;
    //            printf("Скопировал\n");
            }
        if(strchr(split_text[i],'!') != NULL){
            //копирование
            //выделение памяти для строки
//            new_text_splitted[j] = (char*) malloc((strlen((split_text[i]))) * sizeof(char)+1);
            //копирование строки из изходного массива
            if(strndup(split_text[i], strlen(split_text[i])*sizeof(char))!=NULL){
                new_text_splitted[j] = strndup(split_text[i], strlen(split_text[i])*sizeof(char));
//                printf("Зашел сюда");
                break;
            }
//            strcpy(new_text_splitted[j],split_text[i]);

        }
    }
    *sentense_number_after = count_sentenc;
    return new_text_splitted;
}


//
//
//}

