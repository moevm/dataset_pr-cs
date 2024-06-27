#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** text_input(int* size_link);
void correct_text(char** text, int* size_link);
void print_info();
void free_text(char** text, int size);
void text_output(char** text, int size);
void flower_to_planted(char** text, int size);
void count_student(char** text, int size);
void delete_friend(char** text, int size);
void sort_by_max_num(char** text, int size);
int compare(const void* x, const void* y);
int get_num(char* sentence);
int* found_word(char* str, char* word);
int max(int a, int b);
int get_sum();
void print_diff(char** text, int size, int min_s);

int main() {
	printf("Course work for option 4.15, created by Danila Savranskii.\n");

	int option;

	if (scanf("%d", &option) != 1 || (option < 0 || option == 6 || option == 7 || option > 9)) {
		printf("Error: Неверная команда!");
		return 1;
	}

    if (option == 5) {
        print_info();
        return 0;
    }

	int size;
    char** text;
    int s = 0;

    switch(option) {
        case 0:
            text = text_input(&size);
            correct_text(text, &size);
            text_output(text, size);
            break;
        case 1:
            text = text_input(&size);
            correct_text(text, &size);
            flower_to_planted(text, size);
            text_output(text, size);
            break;
        case 2: 
            text = text_input(&size);
            correct_text(text, &size);
            count_student(text, size);
            break;
        case 3:
            text = text_input(&size);
            correct_text(text, &size);
            delete_friend(text, size);
            text_output(text, size);
            break;
        case 4:
            text = text_input(&size);
            correct_text(text, &size);
            sort_by_max_num(text, size);
            text_output(text, size);
            break;
        case 5:
            print_info();
            break;
        case 8:
            s = get_sum();
            text = text_input(&size);
            correct_text(text, &size);
            print_diff(text, size, s);
            break;
        case 9:
            return 0;
    }
    free_text(text, size);

}

void free_text(char** text, int size) {
    for (int i = 0; i < size; i++) {
        free(text[i]);
    }
    free(text);
}

void print_info() {
    printf("1: В каждом предложении заменить все слова “flower” на “planted”.\n");
    printf("2: Для каждого предложения посчитать количество слов “student” и вывести количество посчитанных слов и само предложение выделив слова “student” красным цветом.\n");
    printf("3: Удалить все предложения в которых слово “friend” встречается больше одного раза.\n");
    printf("4: Отсортировать предложения по уменьшению максимального числа в строке. Число - слово состоящее только из цифр. Если в предложении нет числа, то для такого числа значение максимального числа равно 0.");
}

void text_output(char** text, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", text[i]);
    }
}

char** text_input(int* size_link) {
    char** text = malloc(sizeof(char*));
    char** tmp_text;
    char* tmp_sent; 
    int size = 0;
    text[0] = malloc(sizeof(char) * 100);
	char c;

    short int new_line = 0;
    int cursor = 0;

	do {
		c = getchar();

        if (c == '\n' && new_line == 1) {
            break;
        }
        else if (c == '\n') {
            new_line = 1;
            continue;
        }
        else {
            new_line = 0;
        }
        if (isspace(c) && cursor == 0) continue;

        text[size][cursor++] = c;
        if (cursor >= 99) {
            tmp_sent = realloc(text[size], sizeof(char) * (cursor + 1));
            if (tmp_sent == NULL) {
                printf("Error: Ошибка выделения памяти!");
                free_text(text, size);
                exit(1);
            }
            text[size] = tmp_sent;
        }

        if (c == '.') {
            text[size][cursor] = '\0';
            size++;
            tmp_text = realloc(text, sizeof(char*) * (size + 1 ));
            if (tmp_text == NULL) {
                printf("Error: Ошибка выделения памяти!");
                free_text(text, size);
                exit(1);
            }
            text = tmp_text;

            text[size] = malloc(sizeof(char) * 100);
            cursor = 0;
        };

	} while (1);

    text[size][cursor] = '\0';


    if (cursor != 0) size++;


    *size_link = size;
    return text;
}

int str_matches(char* str1, char* str2) {
    if (strlen(str1) != strlen(str2)) return 0;
    int l = strlen(str1);
    for (int i = 0; i < l; i++) {
        if (tolower(str1[i]) != tolower(str2[i])) return 0;
    }
    return 1;
}

void correct_text(char** text, int* size_link) {
    int size = *size_link;
    for (int i = 0; i < size - 1; i++) {
        
        for (int j = i + 1; j < size; j++) {
            if (str_matches(text[i], text[j])) {
                free(text[j]);
                memmove(text + j, text + j + 1, (size - 2) * sizeof(char*));
                j--;
                size--;
            }
        }
    }
    *size_link = size;
}

int* found_word(char* str, char* word) {
    int *matches = malloc(sizeof(int));
    int count = 0;
    matches[0] = -1;

    int len = strlen(str);
    int w_len = strlen(word);

    int j = 0;
    for (int cursor = 0; cursor < len; cursor++) {
        if (j == 0) {
            if (cursor == 0 || (isspace(str[cursor - 1]) || str[cursor - 1] == ',')) {
                if (word[0] == str[cursor]) j += 1;
            }
        }
        else if (j < w_len) {
            if (str[cursor] == word[j]) j += 1;
            else j = 0;
        }
        else {
            if (str[cursor] == '.' || isspace(str[cursor]) || str[cursor] == ',') {
                matches = realloc(matches, sizeof(int) * (count + 1));
                if (matches == NULL) {
                    printf("Error: Ошибка выделения памяти!");
                    exit(1);
                }
                matches[count] = cursor - w_len;
                matches[count + 1] = -1;
                count++;
            }
            j = 0;
        }
    }

    return matches;
}


void flower_to_planted(char** text, int size) {

    for (int i = 0; i < size; i++) {
        int *matches = found_word(text[i], "flower");
        int len = strlen(text[i]);

        int offset = 0;
        for (int k = 0; matches[k] != -1; k++) {
            int cursor = matches[k] + offset;
            char *str = malloc((len + 2) * sizeof(char));
            str[len + 1] = '\0';
            if (cursor != 0)
                memcpy(str, text[i], cursor * sizeof(char));
            memcpy(str + cursor, "planted", 7 * sizeof(char));
            if (cursor != len - 1)
                memcpy(str + cursor + 7, text[i] + cursor + 6, (len - cursor - 6) * sizeof(char));

            free(text[i]);
            text[i] = str;
            len++;
            offset++;
        }
        free(matches);
    }
}

void count_student(char** text, int size) {
    for (int i = 0;i < size; i++) {
        int* matches = found_word(text[i], "student");
        int count = 0;
        for (;matches[count] != -1; count++);
        int k = 0;
        printf("%d ", count);
        for (int j = 0; j < strlen(text[i]); j++) {
            if (k < count && j == matches[k]) {
                printf("\033[41m\033[30m");
            }
            printf("%c", text[i][j]);
            if (k < count && j == matches[k] + 6) {
                printf("\033[0m");
                k++;
            }
        }
        printf("\n");
        free(matches);
    }
}

void delete_friend(char** text, int size) {
    for (int i = 0; i < size; i++) {
        int* matches = found_word(text[i], "friend");
        int count = 0;
        for (;matches[count] != -1; count++);

        if (count > 1) {
            free(text[i]);
            memmove(text + i, text + i + 1, (size - 1) * sizeof(char*));
            size--;
            i--;
        }
        free(matches);
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int get_num(char* sentence) {
    int max_num = 0;
    int num = -1;
    for (int i = 0; i < strlen(sentence); i++) {
        if (num == -1) {
            if (isdigit(sentence[i]) && (i == 0 || isspace(sentence[i - 1]))) {
                num = (int)sentence[i] - 48;
            }
        }
        else {
            if (isdigit(sentence[i])) {
                num = num * 10 + (int)sentence[i] - 48;
            }
            else if (isspace(sentence[i]) || sentence[i] == ',' || sentence[i] == '.') {
                max_num = max(max_num, num);
                num = -1;
            }
            else {
                num = -1;
            }
        }
    }
    return max_num;
}

int compare(const void* x, const void* y) {
    char* snt1 = *(char**)x;
    char* snt2 = *(char**)y;
    return get_num(snt2) - get_num(snt1);
}

void sort_by_max_num(char** text, int size) {
    qsort(text, size, sizeof(char*), compare);
}

int get_sum() {
    char c;
    int s = 0;
    getchar();
    for (int i = 0; i < 200; i++) {
        c = getchar();
        if (c == '\n') break;
        if (isdigit(c)) s += (int)c - 48;
    }
    return s;
}

void print_diff(char** text, int size, int min_s) {
    int s;
    for (int i = 0; i < size; i++) {
        s = 0;
        for (int j = 0; text[i][j] != '.'; j++) {
            if (isdigit(text[i][j])) s += (int)text[i][j] - 48;
        }

        if (s > min_s) {
            printf("(%d) %s\n", s - min_s, text[i]);
        }

    }
}
 