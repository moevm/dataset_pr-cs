#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_WORD_COUNT 10
#define WORD_LENGTH_INCREMENT 10
#define WORD_INCREMENT 10


void print_info() {
    printf("Course work for option 4.15, created by Potapov Rodion.\n");
}

char* get_text() {
    int size = 10;
    char* sentence = (char*)calloc(size, sizeof(char));
    char* sent = sentence;
    int count = 0, stage = 1;
    int consecutive_newlines = 0;
    int is_start_osenttence = 1;
    int check;

    while ((check = getchar()) != EOF) {
        if (check == '\n') {
            consecutive_newlines++;
            if (consecutive_newlines >= 2) {
                break;
            }
            is_start_osenttence = 1; // Начало нового предложения
        } else {
            consecutive_newlines = 0;
            if (is_start_osenttence && check == ' ') {
                continue; // Пропускаем пробелы в начале предложения
            }
            is_start_osenttence = 0;
        }
        *sent = check;
        if (count == (10 * stage) - 1) {
            stage++;
            size = stage * 10;
            sentence = realloc(sentence, size * sizeof(char));
        }

        sent++;
        count++;
    }

    if (check == EOF) {
        printf("Error: Некорректные входные данные\n");
        free(sentence); // Освобождаем память перед выходом из функции
        return NULL;
    }

    // Удаление переноса строки в конце
    if (count > 0 && sentence[count - 1] == '\n') {
        sentence[count - 1] = '\0'; // Заменяем перенос строки на завершающий символ
    }

    return sentence;
}
char** text_to_sentences(char* text, int* num_sen) {
    int size = 5;
    char** sentences = (char**)malloc(size * sizeof(char*));
    int count = 0;
    int sentence_start = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!') {
            sentences[count] = (char*)malloc((i - sentence_start + 2) * sizeof(char));
            strncpy(sentences[count], &text[sentence_start], i - sentence_start + 1);
            sentences[count][i - sentence_start + 1] = '\0';
            sentence_start = i + 2;
            count++;

            if (count >= size) {
                size += 5;
                sentences = realloc(sentences, size * sizeof(char*));
            }
        }
    }
    sentences[count] = NULL; // Устанавливаем NULL для обозначения конца массива строк
    *num_sen=count;
    return sentences;
}
char** into_words(char* sentence) {
    char** words = (char**)malloc(INITIAL_WORD_COUNT * sizeof(char*));
    int word_count = 0;
    int word_capa = INITIAL_WORD_COUNT;

    char* start_word = sentence;
    char* end_word;

    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '?' || sentence[i] == '!') {
            words[word_count] = (char*)calloc(WORD_LENGTH_INCREMENT, sizeof(char));
            int word_length = 0;
            int word_length_capa = WORD_LENGTH_INCREMENT;

            end_word = sentence + i;

            while (start_word < end_word) {
                words[word_count][word_length] = *start_word;
                start_word++;
                word_length++;

                if (word_length == word_length_capa) {
                    word_length_capa += WORD_LENGTH_INCREMENT;
                    words[word_count] = realloc(words[word_count], word_length_capa * sizeof(char));
                }
            }

            words[word_count][word_length] = '\0'; // Добавляем завершающий символ

            word_count++;
            start_word = sentence + i + 1; // Обновляем указатель на начало следующего слова

            if (word_count == word_capa) {
                word_capa += WORD_INCREMENT;
                words = realloc(words, word_capa * sizeof(char*));
            }
        }
    }

    words[word_count] = NULL; // Устанавливаем NULL для обозначения конца массива сло

    return words;
}
int count_words(char* sen, char* word){
    int count = 0, i = 0;
    char word_with_dot[BUFSIZ]; // Выделение памяти для строк word_with_dot и word_with_comma
    sprintf(word_with_dot, "%s.", word);
    char word_with_comma[BUFSIZ];
    sprintf(word_with_comma, "%s,", word);

    char** words = into_words(sen);
    while (words[i] != NULL){
        if (strcmp(words[i], word) == 0 || strcmp(words[i], word_with_dot) == 0 || strcmp(words[i], word_with_comma) == 0){
            count++;
        }
        i++;
    }
    return count;
}
void word_change(char** sentences) {
    int i = 0;
    while (sentences[i] != NULL) {
        char* sen = sentences[i];
        int count = 0;
        char* index = sen;
        while ((index = strstr(index, "flower")) != NULL) {
            if (*(index + strlen("flower")) != 's') {
                char buffer[BUFSIZ];
                strncpy(buffer, sen, index - sen);
                buffer[index - sen] = '\0';

                strcat(buffer, "planted");

                strcat(buffer, index + strlen("flower"));

                free(sentences[i]); // Освобождаем предыдущую память
                sentences[i] = (char*)malloc(strlen(buffer) + 1); // Выделяем новую память
                strcpy(sentences[i], buffer); // Копируем данные

                index = sentences[i] + (index - sen) + strlen("planted"); // Обновляем индекс
                count++;
            } else {
                index += strlen("flower") + 1;
            }
        }
        i++;
    }
}
void dups_delete(char** sentences, int* num_sen) {
    int i = 0;
    while (sentences[i] != NULL) {
        int j = i + 1;
        while (sentences[j] != NULL) {
            if (strcmp(sentences[i], sentences[j]) == 0) {
                free(sentences[j]);
                (*num_sen)--;

                // Сдвигаем последующие предложения влево
                int k = j;
                while (sentences[k] != NULL) {
                    sentences[k] = sentences[k + 1];
                    k++;
                }
            } else {
                j++;
            }
        }
        i++;
    }
}


void print_sentences(char** sentences){
    int i=0;
    while (sentences[i]!=NULL){
        printf("%s\n",sentences[i]);
        free(sentences[i]);
        i++;
    }
    free(sentences);
}
void replace_flower_to_planted(char** sentences, int num_sen) {
    char** sen_copy = malloc(sizeof(char*) * (num_sen + 1));
    if (sen_copy == NULL) {
        printf("Error: Ошибка выделения памяти\n");
        return;
    }

    int i = 0;
    while (sentences[i] != NULL) {
        sen_copy[i] = malloc(strlen(sentences[i]) + 1);
        if (sen_copy[i] == NULL) {
            printf("Error: Ошибка выделения памяти\n");
            // Освобождаем уже выделенную память
            while (i > 0) {
                free(sen_copy[--i]);
            }
            free(sen_copy);
            return;
        }
        strcpy(sen_copy[i], sentences[i]);
        i++;
    }
    sen_copy[i] = NULL;

    word_change(sen_copy);

    i=0;
    while (sen_copy[i]!=NULL){
        printf("%s\n",sen_copy[i]);
        i++;
    }

    // Освобождение памяти sen_copy
    i = 0;
    while (sen_copy[i] != NULL) {
        free(sen_copy[i]);
        i++;
    }
    free(sen_copy); // Освобождение массива указателей
}
void count_students(char **sentences, int num_sentences) {
    for (int i = 0; i < num_sentences; i++) {
        int count = count_words(sentences[i], "student");
        printf("%d ", count);

        char **words = into_words(sentences[i]);
        int j = 0;
        while (words[j] != NULL) {
            if (strcmp(words[j], "student") == 0) {
                printf("\033[0;31mstudent\033[0m");
            } else if (strcmp(words[j], "student,") == 0 ) {
                printf("\033[0;31mstudent\033[0m,");
            } else if (strcmp(words[j], "student.") == 0 ) {
                printf("\033[0;31mstudent\033[0m");
            }else{
                printf("%s",words[j]);
            }
            if (words[j + 1] != NULL) {
                printf(" ");
            }
            j++;
        }
        printf(".");
        for (int k = 0; k < j; k++) {
            free(words[k]);
        }
        free(words);

        printf("\n");
    }
}
void sort_by_friend(char** sentences) {
    int i = 0;
    while (sentences[i] != NULL) {
        int count = count_words(sentences[i], "friend");
        if (count > 1) {
            free(sentences[i]); // Освобождаем память текущего предложения
            int j = i + 1;
            while (sentences[j] != NULL) {
                sentences[j - 1] = sentences[j]; // Сдвигаем последующие предложения влево
                j++;
            }
            sentences[j - 1] = NULL; // Устанавливаем конец списка предложений
        } else {
            i++;
        }
    }

    i = 0;
    while (sentences[i] != NULL) {
        printf("%s\n", sentences[i]);
        i++;
    }
}
int get_max_number(const char *sentence) {
    int max_number = 0;
    int current_number = 0;
    int is_number = 0; // Флаг, указывающий на то, что мы находимся внутри числа

    for (int i = 0; sentence[i] != '\0'; ++i) {
        if (isdigit(sentence[i])) {
            current_number = current_number * 10 + (sentence[i] - '0');
            is_number = 1;
        } else {
            if (is_number) {
                if (current_number > max_number) {
                    max_number = current_number;
                }
                current_number = 0;
                is_number = 0;
            }
        }
    }

    if (is_number && current_number > max_number) {
        max_number = current_number;
    }

    return max_number;
}
int compare_sentences(const void *a, const void *b) {
    const char **sentence_a = (const char **)a;
    const char **sentence_b = (const char **)b;

    int max_number_a = get_max_number(*sentence_a);
    int max_number_b = get_max_number(*sentence_b);

    return max_number_b - max_number_a; // Сортировка по убыванию
}
void sort_sentences(char** sentences, int num_sentences){
    // Сортировка предложений
    qsort(sentences, num_sentences, sizeof(char *), compare_sentences);

    // Вывод отсортированных предложений
    int i=0;
    while (sentences[i]!=NULL){
        printf("%s\n", sentences[i]);
        i++;
    }
}

void sort_by_number(char** sentences , int first_sum){
    int i = 0;
    while(sentences[i]!=NULL){
	    int summa=0;
	    int j =0;
	    while(sentences[i][j]!='\0'){
	        if(isdigit(sentences[i][j])!=0){
	            summa+=(sentences[i][j] - 48);
	        }
	        j++;
	    }
	    if(summa - first_sum >0){
	        printf("(%d)%s\n" , summa - first_sum , sentences[i]);
	        
	    }
	    
	    i++;
    }
}



void process_input(){
    int option;
    scanf("%d\n" , &option);
    int num_sentences=0;
    
    int summ_first_sen = 0;
    
    
    char* text = get_text();
    if(text == NULL){
        printf("Error: Invalid option.\n");
            return;
    }
    char** sentences = text_to_sentences(text , &num_sentences);
     if (sentences == NULL) {
            printf("Error: Invalid option.\n");
            free(text);
            return;
    }
    dups_delete(sentences,&num_sentences);

    switch (option){
        case 0:
            print_sentences(sentences);
            break;
        case 1:
            replace_flower_to_planted(sentences,num_sentences);
            break;
        case 2:
            count_students(sentences,num_sentences);
            break;
        case 3:
            sort_by_friend(sentences);
            break;
        case 4:
            sort_sentences(sentences,num_sentences);
            break;
        case 5:
            printf("Опция 0: Удалить повторяющиеся предложения.\n");
            printf("Опция 1: Заменить слово 'flower' на 'planted'.\n");
            printf("Опция 2: Подсчитать вхождения 'student'.\n");
            printf("Опция 3: Удалить предложения с более чем одним 'friend'.\n");
            printf("Опция 4: Отсортировать предложения по числу в строке.\n");
            printf("Опция 5: Вывод справки о функциях.\n");
            break;
	case 8:
	    for(int  i = 0 ; sentences[0][i] != '\0' ; i++){
	        if(isdigit(sentences[0][i])!=0){
	            summ_first_sen+=(sentences[0][i] - 48);
	        }
	    }
	    sort_by_number(sentences , summ_first_sen);
            break;
        default:
            printf("Error: Invalid option.\n");
            break;
        
    }

}

int main(){
    print_info();
    process_input();

    return 0;
}
