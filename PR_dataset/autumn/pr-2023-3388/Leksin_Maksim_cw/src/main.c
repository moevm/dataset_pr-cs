#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#define BUFFER_SIZE 1024
#define SIZE_CONNECTOR 101

#define YELLOW "\033[1;93m"
#define GREEN "\033[1;92m"
#define RESET_COLOR "\033[0m"
#define HELP "0 - вывод текста после первичной обязательной обработки.\n1 - Вывести все предложения в которых есть слово “banana” или “apple”. Слово “banana” должно быть выделено желтым цветом, а слово “apple” зеленым.\n2 - Преобразовать предложения так, чтобы в слове все буквы были строчные, а все цифры были заменены буквой ‘D’.\n3 - Удалить все предложения длина которых больше 15.\n4 - Отсортировать предложения по возрастанию произведений всех цифр в них.\n5 - Вызов помощи (этого текста)."
#define INFO "Course work for option 4.12, created by Maksim Leksin."
#define ERROR "Error: данной операции не существует в программе."



void print_info();
void new_function();
char* input_text(int*);
char** split_into_sentences(char*, int);
char** remove_duplicate_sentences(char**, int*);
void text_formatting(int, char**, int);
int product_of_digits(char*);
void sort_sentences_by_digits_product(char**, int);
void yellow_green_colors(char**, int);
void little_and_d(char**, int);
void length_limit(char**, int);
void sort_order(char**, int);
int menu();

int main() {
    menu();
}

int menu() {
    print_info();
    int total_sentences = 0, chosen_task;
    scanf("%d", &chosen_task);
    if (chosen_task == 5) {
        puts(HELP);
        return 0;
    }
    else if (chosen_task == 8) {
        new_function();
        return 0;
    }
    
    else if ((chosen_task < 0 || chosen_task > 5) && chosen_task != 8) {
        puts(ERROR);
        return 0;
    }
    char* text = input_text(&total_sentences);
    char** sentences = split_into_sentences(text, total_sentences);
    char** unique_sentences = remove_duplicate_sentences(sentences, &total_sentences);
    text_formatting(chosen_task, unique_sentences, total_sentences);
    free(sentences);
    free(text);
    free(unique_sentences);
    return 0;
}

void print_info() {
    puts(INFO);
}


void new_function() {
    char* single_sentence = (char*)calloc(SIZE_CONNECTOR, sizeof(char));
    int i = 0;
    char c;

    while (1) {
        c = getchar();
        
        if (c == '\n' && i == 0) {
            continue;
        }
        single_sentence[i++] = c;
        if (i >= 2 && single_sentence[i-1] == '\n') {
            break;
        }
    }

    single_sentence[i-1] = '\0';
    
    int total_sentences = 0;
    char *text = input_text(&total_sentences);
    char **sentences = split_into_sentences(text, total_sentences);
    int unique_total = total_sentences;
    char **unique_sentences = remove_duplicate_sentences(sentences, &unique_total);
    
    int mid_text = unique_total/2;
    if (unique_total % 2 == 0) {
        for (int j = 0; j < mid_text; j++) {
            if (j >= mid_text)
                break;
            
            printf("%s %s %s.\n", unique_sentences[j], single_sentence, unique_sentences[unique_total-j-1]);
        }
            
    }
    else {
        for (int j = 0; j < unique_total; j++) {
            if (j == mid_text) {
                printf("%s %s %s.\n", unique_sentences[j], single_sentence, unique_sentences[j]);
                break;
            }
            printf("%s %s %s.\n", unique_sentences[j], single_sentence, unique_sentences[unique_total-j-1]);
        }
    }
    free(text);
    free(sentences);
    free(unique_sentences);
        
}


void text_formatting(int chosen_task, char** unique_sentences, int total_sentences) {
    switch (chosen_task) {
        case 0:
            for (int i = 0; i < total_sentences; i++) {
                printf("%s.\n", unique_sentences[i]);
            }
            break;
        case 1:
            yellow_green_colors(unique_sentences, total_sentences);
            break;
        case 2:
            little_and_d(unique_sentences, total_sentences);
            break;
        case 3:
            length_limit(unique_sentences, total_sentences);
            break;
        case 4:
            sort_order(unique_sentences, total_sentences);
            break;
    }
}

char* input_text(int* len) {
    char* text = (char*)calloc(BUFFER_SIZE, sizeof(char));
    int current_size = BUFFER_SIZE;
    int i = 0;
    char c;

    while (1) {
        c = getchar();
        if (c == '\n' && i == 0) {
            continue;
        }
        text[i++] = c;
        if (i == current_size - 1) {
            current_size += BUFFER_SIZE;
            char* temp = realloc(text, current_size*sizeof(char));
            text = temp;
        }
        if (c == '.'){
            (*len)++;
        }
        if (i >= 2 && text[i-2] == '\n' && text[i-1] == '\n') {
            break;
        }
    }

    text[i-2] = '\0';
    return text;
}

char** split_into_sentences(char* text, int count) {
    char **sentences = (char**)calloc(count, sizeof(char*));
    int capacity = BUFFER_SIZE;
    int i = 0;

    char *sentence = strtok(text, ".");
    while (sentence != NULL) {
        if (i >= capacity) {
            capacity *= 2;
            sentences = realloc(sentences, sizeof(char*) * capacity);
        }
        if (sentence[0] == ' ' || sentence[0] == '\t' || sentence[0] == '\n') {
            sentence++;
        }
        sentences[i++] = sentence;
        sentence = strtok(NULL, ".");
    }
    return sentences;
}

char** remove_duplicate_sentences(char** sentences, int* len) {
    char** del_sentences = (char**)calloc(*len, sizeof(char*));
    int index = 0;
    del_sentences[index++] = sentences[0];
    for (int i = 1; i < *len; ++i) {
        int is_duplicate = 0;
        for (int j = 0; j < index; ++j) {
            if (strcasecmp(sentences[i], del_sentences[j]) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            del_sentences[index++] = sentences[i];
        }
    }
    *len = index;
    return del_sentences;
}

int product_of_digits(char* sentence) {
    int product = 1;
    while (*sentence) {
        if (isdigit((unsigned char)*sentence)) {
            product *= *sentence - '0';
        }
        ++sentence;
    }
    return product;
}

void sort_sentences_by_digits_product(char** sentences, int len) {
    int* products = (int*)malloc(len * sizeof(int));
    for (int i = 0; i < len; ++i) {
        products[i] = product_of_digits(sentences[i]);
    }

    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - i - 1; ++j) {
            if (products[j] > products[j + 1]) {
                int temp_prod = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp_prod;

                char* temp_sent = sentences[j];
                sentences[j] = sentences[j + 1];
                sentences[j + 1] = temp_sent;
            }
        }
    }

    free(products);
}

void yellow_green_colors(char** sentences, int len) {
    for (int i = 0; i < len; ++i) {
        char* sentence = sentences[i];
        char* banana_ptr = strstr(sentence, "banana");
        char* apple_ptr = strstr(sentence, "apple");

        if (banana_ptr || apple_ptr) {
            while (*sentence) {
                if (sentence == banana_ptr) {
                    printf(YELLOW "banana" RESET_COLOR);
                    sentence += 6;
                    banana_ptr = strstr(sentence, "banana");
                } else if (sentence == apple_ptr) {
                    printf(GREEN "apple" RESET_COLOR);
                    sentence += 5;
                    apple_ptr = strstr(sentence, "apple");
                } else {
                    putchar(*sentence++);
                }
            }
            printf(".\n");
        }
    }
}

void little_and_d(char** sentences, int len) {
    for (int i = 0; i < len; ++i) {
        char* sentence = sentences[i];
        while (*sentence) {
            if (isdigit((unsigned char)*sentence)) {
                *sentence = 'D';
            } else if (isalpha((unsigned char)*sentence)) {
                *sentence = tolower((unsigned char)*sentence);
            }
            sentence++;
        }
        printf("%s.\n", sentences[i]);
    }
}

void length_limit(char** sentences, int len) {
    int num_sentence = 0;
    for (int i = 0; i < len; ++i) {
        if (strlen(sentences[i]) <= 15) {
            printf("%s.\n", sentences[i]);
            sentences[num_sentence++] = sentences[i];
        }
    }
}

void sort_order(char** sentences, int len) {
    sort_sentences_by_digits_product(sentences, len);
    for (int i = 0; i < len; ++i) {
        printf("%s.\n", sentences[i]);
    }
}
