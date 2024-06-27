#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  

#define INITIAL_CAPACITY 10

char* my_strdup(const char* src) {
    size_t len = strlen(src) + 1; 
    char* res = malloc(len);
    if (res != NULL) {                              
        strcpy(res, src);
    }
    return res;
}

char* format_sentence(char* sentence) {
    while (sentence[0] == '\t' || sentence[0] == ' ' || sentence[0] == '\n') {
        for (size_t i = 0; i < strlen(sentence)+1; i++)                           
            sentence[i] = sentence[i + 1];
    }
    return sentence;
}

void print_text(char** text){
    for(int i = 0; text[i]!=NULL; i++){
        printf("%s.\n", format_sentence(text[i]));
    }
}

void reference(){
    printf("При выборе '1' будет выведено каждое предложение, и если в нем есть словосочетание 'define BLUE', то все слова после этого словосочетания будут выведены голубым цветом.\n");
    printf("При выборе '2' во всем тексте будет заменена последовательность подряд идущих букв без учета регистра подстрокой вида '<кол-во подряд идущих букв><буква в верхнем регистре>'\n");
    printf("При выборе '3' будут удалены все предложения в которых количество слов кратно трем.\n");
    printf("При выборе '4' будут отсортированы предложения по уменьшению суммарной длины первого и последнего слова.\n");
}

char** input_text() {
    int sentence_count = 0;
    int sentence_capacity = INITIAL_CAPACITY;
    char** text = (char**)malloc(sentence_capacity * sizeof(char*));
    char input[1000];
    size_t i = 0;
    char c;
    int index = 0;

    while (((c = getchar()) != EOF) && i < sizeof(input) - 1) {
        if (c == '\n') {
            index++;
            if (index == 2) {
                input[i++] = '\0';
                break;
            }
        } else {
            index = 0;
            input[i++] = c;
        }
    }
    input[i] = '\0';

    char* token = strtok(input, ".");
    while (token != NULL) {
        if (sentence_count >= sentence_capacity - 1) {
            sentence_capacity *= 2;
            text = (char**)realloc(text, sentence_capacity * sizeof(char*));
        }
        text[sentence_count++] = my_strdup(token);
        token = strtok(NULL, ".");
    }
    text[sentence_count] = NULL;

    return text;
}

void free_memory(char** text){
    for (int i = 0; text[i] != NULL; i++) {
        free(text[i]);                                         
    }
    free(text);
}


void repainting(char** text) {
    for (int i = 0; text[i] != NULL; i++) {
        char* sentence = text[i];
        char* define_blue = strstr(sentence, "define BLUE");
        char* print_start = sentence;

        if (isspace(*print_start)) {
            print_start++;
        }

        if (define_blue != NULL) {
            printf("%.*s", (int)(define_blue - sentence), sentence);
            printf("define BLUE");
            printf("\033[1;34m%s.\033[0m\n", define_blue + strlen("define BLUE"));
        } else {
            printf("%s.\n", print_start);
        }
    }
}

void replace_sequence(char* text, int start, int end, char letter, int count) {
    char replacement[50];
    sprintf(replacement, "%d%c", count, (char)toupper(letter));

    memmove(&text[start], replacement, strlen(replacement));                            
    memmove(&text[start + strlen(replacement)], &text[end], strlen(&text[end]) + 1);
}

void format_text(char** text) {
    char* input = *text;
    int len = strlen(input);

    int i = 0;
    while (i < len) {
        int count = 1;
        int start = i;
        char current = input[i];

        int j = i + 1;
        while (j < len && (input[j] == current || input[j] == (char)(current + 32) || input[j] == (char)(current - 32))) {
            count++;
            j++;
        }

        if (count > 1) {
            replace_sequence(input, start, j, current, count);
            len = strlen(input); 
            i = start + 2;
        } else {
            i++;
        }
    }
}

int compare_sentences(const char* sentence1, const char* sentence2) {
    while (*sentence1 && *sentence2) {
        if (tolower(*sentence1) != tolower(*sentence2)) {
            return 0; 
        }
        sentence1++;                                                               
        sentence2++;
    }
    return (*sentence1 == '\0' && *sentence2 == '\0');
}


void necessary_processing(char** text) {
    int count = 0;
    int* is_duplicate = NULL;

    while (text[count] != NULL) {
        count++;
    }

    is_duplicate = (int*)calloc(count, sizeof(int));

    for (int i = 0; i < count; i++) {
        if (is_duplicate[i] == 1) {
            continue; 
        }
        for (int j = i + 1; j < count; j++) {
            if (is_duplicate[j] == 1) {
                continue; 
            }
            if (compare_sentences(format_sentence(text[i]), format_sentence(text[j]))) {
                is_duplicate[j] = 1; 
            }
        }
    }

    int original_index = 0;
    for (int i = 0; i < count; i++) {
        if (is_duplicate[i] == 0) {
            text[original_index++] = text[i];
        } else {
            free(text[i]);
        }
    }
    text[original_index] = NULL;

    free(is_duplicate);
}

int getFirstAndLastLength(const char* sentence) {
    int first = 0;
    int last = 0;
    const char* first_word = sentence;
    const char* last_word = sentence;

    while (*first_word && (*first_word == ' ' || *first_word == '\t')) {
        first_word++;
    }

    const char* end = first_word + strlen(first_word) - 1;
    while (end > first_word && (*end == ' ' || *end == '\t' || *end == '\n')) {
        end--;
    }
    last_word = end;                                                                   

    while (*first_word && (*first_word != ' ' && *first_word != '\t')) {
        first++;
        first_word++;
    }
    while (last_word > first_word && (*last_word != ' ' && *last_word != '\t')) {
        last++;
        last_word--;
    }

    return first + last;
}

int cmp(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    int sum_length1 = getFirstAndLastLength(str1);
    int sum_length2 = getFirstAndLastLength(str2);

    return sum_length2 - sum_length1;
}

int countWords(const char* sentence) {
    int word_count = 0;
    int inWord = 0;

    for (size_t i = 0; i < strlen(sentence); i++) {
        if (sentence[i] == ' ' || sentence[i] == '\t' || sentence[i] == '\n') {
            if (inWord) {
                inWord = 0;
            }
        } else {
            if (!inWord) {                                                      
                inWord = 1;
                word_count++;
            }
        }
    }

    return word_count;
}

void delete_sentence3(char **text) {
    int numSentences = 0;
    while (text[numSentences] != NULL) {
        if (countWords(text[numSentences]) % 3 == 0) {
            free(text[numSentences]); 
            for (int i = numSentences; text[i] != NULL; i++) {
                text[i] = text[i + 1];
            }
        } else {
            numSentences++;
        }
    }
}

void operation_0(){
    char** text = input_text();
    necessary_processing(text);
    print_text(text);
    free_memory(text);
}

void operation_1(){
    char** text = input_text();
    necessary_processing(text);
    repainting(text);
    free_memory(text);
}

void operation_2(){
    char** text = input_text();
    necessary_processing(text);
    format_text(text); 
    print_text(text);  
    free_memory(text);
}

void operation_3(){
    char** text = input_text();
    necessary_processing(text);
    delete_sentence3(text);
    print_text(text);
    free_memory(text);
}

void operation_4(){     
    char** text = input_text();
    int count_sentence = 0; 
    for(int i = 0; text[i]!=NULL; i++){
        count_sentence++;
    }
    qsort(text, count_sentence, sizeof(char*), cmp);
    print_text(text);
    free_memory(text);
}

int main(){
    printf("Course work for option 4.16, created by Maksim Chernysh.\n");
    int choise;
    scanf("%d", &choise);
    switch(choise){
        case 0:
            operation_0();
            break;
        case 1:
            operation_1();
            break;
        case 2:
            operation_2();
            break;
        case 3:
            operation_3();
            break;
        case 4:
            operation_4();
            break;
        case 5:
            reference(); 
            break;
        default:
            printf("Error: введенное значение должно быть в промежутке от 0 до 5\n");
    }
    return 0;
}
