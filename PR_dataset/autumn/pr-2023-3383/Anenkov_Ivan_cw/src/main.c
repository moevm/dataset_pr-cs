#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}


int cmp(char* s1, char* s2){
    char s1_lower[strlen(s1) + 1]; 
    strcpy(s1_lower, s1);
    char s2_lower[strlen(s2) + 1];
    strcpy(s2_lower, s2); 
    for(int i = 0; s1_lower[i] != '\0'; i++) s1_lower[i] = (char)tolower(s1_lower[i]); // Переводим буквы в нижний регистр
    for(int i = 0; s2_lower[i] != '\0'; i++) s2_lower[i] = (char)tolower(s2_lower[i]);// чтобы сравнение было без учета регистра
    return (strcmp(s1_lower, s2_lower)); 
}

void delete_duplicates(char** text, int *len){
    for(int i = 0; i < (*len); i++){ 
        for(int j = i + 1; j < (*len); j++){
            if(!cmp(text[i], text[j])){ 
                memmove(&text[j], &text[j + 1], sizeof(char*) * ((*len) - j - 1)); 
                (*len)--; 
                j--;  
            }
        }
    }
}

void split_sentences(char ***text, char *buffer, int *len, int *capacity) {
    char *token = strtok(buffer, ".");
    while (token != NULL && strlen(token) != 1) {
	char * new_token = (char *)malloc((strlen(token) + 1) * sizeof(char));
	int index = 0;
	int new_index = 0;
	while(token[index] == ' ') {
		index++;
	}
	while(index < strlen(token)) {
		new_token[new_index++] = token[index++];
	}
	new_token[new_index] = '\0';
	
        (*text)[(*len)] = strdup(new_token);
        if ((*text)[(*len)] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        if ((*len) >= *capacity - 1) {
            (*capacity) = (*capacity) * 2;
            *text = (char**)realloc(*text, (*capacity) * sizeof(char*));
            if (!(*text)) {
                printf("Error: Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
        }
        (*len)++;
        token = strtok(NULL, ".");
    }
}

char** text_input(int *string_len) {
    char buffer[1024];
    int capacity = 10; 
    char** text = (char**)malloc(capacity * sizeof(char*));
    int len = 0; 

    if (!text) {
        printf("Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (strcmp(buffer, "\n") == 0) {
            break;
        }
        split_sentences(&text, buffer, &len, &capacity);
    }

    *string_len = len;

    if(len > 1)
        delete_duplicates(text, string_len);

    return text;
}


int count_words(char *sent) {
    int word_count = 0;
    int in_word = 0;  // Флаг указывает, находится ли указатель внутри слова
    while (*sent) {
        if (!(isdigit(*sent) || isalpha(*sent))) {
            in_word = 0;
        } else {
            if (!in_word) {
                in_word = 1;
                word_count++;
            }
        }
        sent++;
    }
    return word_count;
}

int counter_len_of_word(int i, int step, char * sent) {
    int count = 0;
    while(i >= 0 && i < strlen(sent) && !(isdigit(sent[i]) || isalpha(sent[i])))
        i+=step;
    while(i >= 0 && i < strlen(sent) && (isdigit(sent[i]) || isalpha(sent[i]))) {
        i+=step;
        count++;
    }
    return count;
}

int count_len_first_and_last(char * sent) {
    int count = 0;
    if(count_words(sent) == 1)
        count = counter_len_of_word(0, 1, sent) ;
    else 
        count = counter_len_of_word(0, 1, sent) 
                + counter_len_of_word(strlen(sent) - 1, -1, sent);
    //printf("%d)%s.\n",count, sent);
    return count;
}

int compare_sentences(const void* a, const void* b){
    char** first = (char**)a; 
    char** second = (char**)b;
    int first_count = count_len_first_and_last(*first); 
    int second_count = count_len_first_and_last(*second); 
    if(first_count > second_count) return -1; 
    else if(second_count > first_count) return 1;
    return 0;
}

void print_text(char ** text, int len) {
    for(int i = 0; i < len; i++)
        printf("%s.\n", text[i]);
}

void delete_sent(char **text, int *len) {
    int i, new_len;
    for (i = 0, new_len = 0; i < *len; i++) {
        if (count_words(text[i]) % 3 != 0) {
            text[new_len++] = text[i];
        } else {
            free(text[i]);
        }
    }
    *len = new_len;
}

void transform_string(char *input) {
    int length = strlen(input);
    if (length == 0) {
        return;
    }
    char result[length * 2];  
    int result_index = 0;
    int count = 1;
    char current_char = input[0];
    for (int i = 1; i <= length; i++) {
        if (tolower(input[i]) == tolower(current_char)) {
            count++;
        } else {
            if (count > 1) {
                result[result_index++] = count + '0';
                result[result_index++] = toupper(current_char);
            } else {
                result[result_index++] = current_char;
            }
            count = 1;
            current_char = input[i];
        }
    }
    result[result_index] = '\0';    
    strcpy(input, result);
}

void transform_text(char ** text, int len) {
    for(int i = 0; i < len; i++) {
        transform_string(text[i]);
    }
} 


void print_blue_text(char **text, int len) {
    const char *define_blue = "define BLUE";
    for (int i = 0; i < len; i++) {
        const char *position = strstr(text[i], define_blue);
        if (position == NULL) {
            printf("%s.\n", text[i]);
        } else {
            char *first_part = (char *)malloc((position - text[i] + 1) * sizeof(char));
            char *second_part = (char *)malloc((strlen(position + strlen(define_blue)) + 1) * sizeof(char));

            if (first_part == NULL || second_part == NULL) {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }

            strncpy(first_part, text[i], position - text[i]);
            first_part[position - text[i]] = '\0';

            strcpy(second_part, position + strlen(define_blue));

            printf("%s", first_part);
            printf("\033[34m");
            printf("%s.\n", second_part);
            printf("\033[0m");
            free(first_part);
            free(second_part);
        }
    }
}

void duplicate_sent(char ** text, int len, int N) {
    for(int i = 0; i < len; i++){
        for(int j = 0; j < N -1; j++)
            printf("%s ", text[i]);
        printf("%s.\n", text[i]);
    }
}

int main()
{
    printf("Course work for option 4.16, created by Ivan Anenkov.\n");
    char** text;
    int command;
    scanf("%d",&command);
    getchar();
    int count_sent = 0;
    if(command >= 0 && command <= 4) {
       // printf("Введите текст\n");
        text = text_input(&count_sent);
       // printf("Текст считан\n");
    } else if(command == 5) {
            printf("0 – вывод текста после первичной обязательной обработки (если предусмотрена заданием данного уровня сложности)\n");
            printf("1 – Вывести каждое предложение, и если в нем есть словосочетание “define BLUE”, то все слова после этого словосочетания вывести голубым цветом.\n");
            printf("2 – Во всем тексте заменить последовательность подряд идущих букв без учета регистра подстрокой вида “<кол-во подряд идущих букв><буква в верхнем регистре>”. Например, последовательность “AaaA” должна быть заменена строкой “4A”.\n");
            printf("3 – Удалить все предложения в которых количество слов кратно трем.\n");
            printf("4 – Отсортировать предложения по уменьшению суммарной длины первого и последнего слова. Если в предложении одно слово, то необходимо брать длину этого слова.\n");
            printf("5 – вывод справки о функциях, которые реализует программа.\n");
        return 0;
    } else if (command == 9){
        int N;
        scanf("%d", &N);
        getchar();
        text = text_input(&count_sent);
        duplicate_sent(text, count_sent, N);
        printf("\n");
    } else {
        printf("Введите команду от 0 до 5 (включительно)");
    }
    switch(command){
        case 0:
           // printf("-----------Считанный текст : ------------------\n");
            print_text(text, count_sent);
            break;
        case 1:
          /*  printf("-----------------------------------------------\n");
            printf("| Выбрана функция 1. Вывести каждое предложение|\n");
            printf("|Если в нем есть словосочетание \"define BLUE\"|\n");
            printf("| то все слова после вывести синим цветом      |\n");
            printf("-----------------------------------------------\n");*/
            print_blue_text(text, count_sent);
            printf("\n");
            break;
            
        case 2:
            /*printf("-----------------------------------------------\n");
            printf("| Выбрана функция 2. Во всем тексте заменить    |\n");
            printf("|последовательность подряд идущих букв без учета|\n");
            printf("|регистра строкой вида <количество> <буква в ВР>|\n");
            printf("| Ex.          \"AaaA\" ---> \"4A\"             |\n");
            printf("-----------------------------------------------\n");*/
            transform_text(text, count_sent);
            print_text(text, count_sent);
            printf("\n");
            break;
            
        case 3:
           /* printf("-----------------------------------------------\n");
            printf("|Удалить пред-ия, кол-во слов в которых кратно 3|\n");
            printf("-----------------------------------------------\n");*/
            delete_sent(text, &count_sent);
            print_text(text, count_sent);
            printf("\n");
            break;
            
        case 4:
           /* printf("-----------------------------------------------\n");
            printf("|Отсортировать предложения по уменьшению суммы |\n");
            printf("|длин первого и последнего слова в предложении |\n");
            printf("-----------------------------------------------\n");*/
            qsort(text, count_sent, sizeof(char*), compare_sentences);
            for(int i = 0; i < count_sent; i++){
                printf("%s.\n",text[i]);
            }
            printf("\n");
            break;
        default:
        {
           /* printf("-----------------------------------------------\n");
            printf("|Выбрано некорректное значение-----------------|\n");
            printf("-----------------------------------------------\n");*/
            
        }
    }
    
    return 0;
}
