#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define BLOCK_SIZE 10
#define IS_VALID_TIME(word, str_len) (str_len == 8 && isdigit(word[0]) && isdigit(word[1]) && word[2] == '-' && isdigit(word[3]) && isdigit(word[4]) && word[5] == '-' && isdigit(word[6]) && isdigit(word[7]))
#define HELP_MSG "Справка о функциях.\nПосле вывода информации о варианте курсовой работы программа ожидает ввода пользователем числа – номера команды:\n0 – вывод текста после первичной обязательной обработки.\n1 – Отсортировать все предложение по уменьшению суммарного времени указанного в строке. Время в строке указывается в виде слова “HH-MM-SS”. Например, для строки “abs 12-03-13 p 01-10-23 02-32-24” суммарное время составляет “15-46-00”. Если в предложении не указано время, то суммарное время для него составляет “00-00-00”.\n2 – Вывести все предложения в которых количество слов больше 2 и меньше 7.\n3 – Во всем тексте заменить согласные строчные буквы на заглавные.\n4 – Удалить все предложения в которых количество слов больше среднего количества слов предложениях.\n5 – вывод справки о функциях, которые реализует программа.\n"
#define ERR_ALLOC "Error: error reallocating memory"
#define ERR_COMMAND_DOES_NOT_EXIST "Error: Введенной команды не существует. (5 - вызов справки)\n"


void complete_clean(char **arr, int size_arr)
{
    for(int i = 0; i < size_arr; i++){
        if (arr[i] != NULL)
            free(arr[i]);
    }
    free(arr);
}

void lowercase_to_uppercase(char *sentence)
{
	size_t str_len = strlen(sentence);
	for(int i = 0; i < str_len; i++){
		sentence[i] = toupper(sentence[i]);
	}
}

int remove_duplicates(char** text, int size_text) {
    size_t duplicates_removed = 0;
    bool duplicates_found = true;

    while (duplicates_found) {
        duplicates_found = false;

        for (size_t i = 0; i < size_text; i++) {
            char *current_sentence = text[i];
            char *lowercase_current_sentence = malloc((strlen(current_sentence)+1) * sizeof(char));
            strncpy(lowercase_current_sentence, current_sentence, strlen(current_sentence)+1);
            lowercase_to_uppercase(lowercase_current_sentence);

            for (size_t j = i + 1; j < size_text; j++) {
                char *other_sentence = text[j];
                char *lowercase_other_sentence = malloc((strlen(other_sentence)+1) * sizeof(char));
                strncpy(lowercase_other_sentence, other_sentence, strlen(other_sentence)+1);
                lowercase_to_uppercase(lowercase_other_sentence);

                if (strcmp(lowercase_current_sentence, lowercase_other_sentence) == 0) {
                    for (size_t k = j; k < size_text - 1; k++) {
                        text[k] = text[k + 1];
		    }
		    //Возможно здесь стоит очистить память под text[size_text],  т.к. она не используется в дальнейшем
                    size_text--;
                    duplicates_removed++;
                    free(lowercase_other_sentence);
                    break;
                }
            	free(lowercase_other_sentence);
            }
	    free(lowercase_current_sentence);
        }

        if (duplicates_removed > 0) {
            duplicates_found = true;
            duplicates_removed = 0;
        }
    }
    return size_text;
}

char* get_text_str()
{
    int capacity = BLOCK_SIZE, text_len = 0;
    char* text_str = malloc(capacity * sizeof(char));
    char ch;

    while(1){

        if (text_len >= capacity-1){
            capacity += BLOCK_SIZE;
            char* text_str_ptr = realloc(text_str, capacity * sizeof(char));

            if (text_str_ptr != NULL)
                text_str = text_str_ptr;
            else{
                puts(ERR_ALLOC);
                return text_str;
            }
        }

        ch = getchar();
        if (ch == ' ' && text_len == 0){
            continue;
        }
        if (ch == '\t' && text_len == 0){
            continue;
        }
        if (ch == '\n' && text_len == 0){
            continue;
        }
        if ((ch == '\n') && (text_str[text_len-1] == '\n')){
            text_str[text_len] = ch;
            text_len++;
            break;
        }

        text_str[text_len] = ch;
        text_len++;
    }
    text_str[text_len] = '\0';
    return text_str;
}

char** get_sentences(int* sentence_count)
{
    int capacity = BLOCK_SIZE, sent_len = 0;
    char** text = malloc(capacity*sizeof(char*));
    char* str = get_text_str();

    char* start_index = str;
    char* end_index = strchr(str, '.');

    while(end_index != NULL){
        if (isalnum(*start_index)){
            if (*sentence_count >= capacity){
                capacity += BLOCK_SIZE;
                char **text_ptr = realloc(text, capacity * sizeof(char*));
                if (text_ptr != NULL)
                    text = text_ptr;
                else{
                    puts(ERR_ALLOC);
                    return text;
                }
            }
            sent_len = end_index - start_index + 1;
            if (sent_len > 1) {
                text[*sentence_count] = malloc((sent_len+1)*sizeof(char));
                strncpy(text[*sentence_count], start_index, sent_len);
                text[*sentence_count][sent_len] ='\0';
                (*sentence_count)++;
            }
        start_index = end_index + 1;
        end_index = strchr(start_index, '.');
        }
        else start_index++;
    }

    if (start_index - str < strlen(str)-1){
        if (strlen(str) - (start_index-str) != 2){
            printf("error: Incorrect end of text\n");
        }
    }
    *sentence_count = remove_duplicates(text, *sentence_count);
    return text;
}

void print_format_text(char **text, int sentence_count)
{
    for (int i = 0; i < sentence_count; ++i){
    	if (text[i] != NULL){
		printf("%s\n", text[i]);
	}
    }
}

char **split_string(char *str, char *separators, size_t *words_count)
{
    size_t capacity = BLOCK_SIZE, count_words = 0;
    char **words = malloc(capacity * sizeof(char*));
    char *str_copy = malloc((strlen(str)+1) * sizeof(char));
    strncpy(str_copy, str, strlen(str)+1);

    char *token = strtok(str_copy, separators);
    while (token != NULL){
        if (count_words >= capacity-1){
            capacity += BLOCK_SIZE;
            char **words_ptr = realloc(words, capacity * sizeof(char*));
            if (words_ptr == NULL){
                printf("%s\n", ERR_ALLOC);
                return words;
            }
            words = words_ptr;
        }

        words[count_words] = malloc((strlen(token)+1) * sizeof(char));
        strncpy(words[count_words], token, strlen(token)+1);
        words[count_words][strlen(token)] = '\0';
        count_words++;

        token = strtok(NULL, separators);
    }
    words[count_words] = NULL;
    *words_count = count_words;
    free(str_copy);
    return words;
}

void get_total_time(char *str, int *hours,  int *minutes, int *seconds)
{
    size_t word_len, words_count = 0;
    char **words = split_string(str, " .,!'\n'", &words_count);
    int temp_hours = 0, temp_minutes = 0, temp_seconds = 0;

    for (int i = 0; words[i] != NULL; i++){
        word_len = strlen(words[i]);

        if (IS_VALID_TIME(words[i], word_len) == 1){
            temp_hours = atoi(words[i]);
            temp_minutes = atoi(words[i]+3);
            temp_seconds = atoi(words[i]+6);

            *seconds += temp_seconds;
	    if (temp_seconds < 60)
            	*minutes += temp_minutes + (temp_seconds / 60) + (*seconds / 60);
	    else
		*minutes += temp_minutes + (temp_seconds / 60);
	    if (temp_minutes < 60)
            	*hours += temp_hours + (temp_minutes / 60) + (*minutes / 60);
	    else
		*hours += temp_hours + (temp_minutes / 60);

            *minutes %= 60;
            *seconds %= 60;
        }
	free(words[i]);
    }
    free(words);
}

int compare_total_time (const void *first, const void *second)
{
    char *sentence_a = *(char**)first;
    char *sentence_b = *(char**)second;
    int hours_a = 0, minutes_a = 0, seconds_a = 0;
    int hours_b = 0, minutes_b = 0, seconds_b = 0;
    get_total_time(sentence_a, &hours_a, &minutes_a, &seconds_a);
    get_total_time(sentence_b, &hours_b, &minutes_b, &seconds_b);

    int total_time_a = hours_a*3600 + minutes_a*60 + seconds_a;
    int total_time_b = hours_b*3600 + minutes_b*60 + seconds_b;

    return(total_time_b - total_time_a);
}

void sort_by_time(char **text, int sentence_count)
{
    int hours = 0, minutes = 0, seconds = 0;

    for(int i = 0; i < sentence_count; i++){
    	get_total_time(text[i], &hours, &minutes, &seconds);
        hours = 0; minutes = 0; seconds = 0;
    }

    qsort(text, sentence_count, sizeof(text[0]), compare_total_time);
    for(int i = 0; i < sentence_count; i++){
        printf("%s\n", text[i]);
    }
}

void lowercase_consonants_letters(char **text, int sentence_count)
{
    char key_consonants[] = "bcdfghjklmnpqrstvwxyz";
    char *consonants_seeker;
    for (int i = 0; i < sentence_count; i++){
    	consonants_seeker = strpbrk (text[i], key_consonants);
	while (consonants_seeker != NULL){
		text[i][consonants_seeker-text[i]] = toupper(text[i][consonants_seeker-text[i]]);
        	consonants_seeker = strpbrk(consonants_seeker+1, key_consonants);
	}
	printf("%s\n", text[i]);
    }
}

void word_count_check(char **text, int sentence_count)
{
	size_t words_count = 0;
	for(int i = 0; i < sentence_count; i++){
		split_string(text[i], " .,!", &words_count);
		if (words_count > 2 && words_count < 7)
			printf("%s\n", text[i]);
	}
}

void check_average_words_count(char **text, int sentence_count)
{
	size_t words_count = 0;
	double avarage_words_count = 0;
	for(int i = 0; i < sentence_count; i++){
		split_string(text[i], " .,!", &words_count);
		avarage_words_count += words_count;
	}
	avarage_words_count /= sentence_count;
	for(int i = 0; i < sentence_count; i++){
		split_string(text[i], " .,!", &words_count);
		if (words_count > avarage_words_count){
			free(text[i]);
			text[i] = NULL;
		}
		else printf("%s\n", text[i]);
	}

}

char* get_first_str()
{
    int capacity = BLOCK_SIZE, str_len = 0;
    char* first_str = malloc(BLOCK_SIZE * sizeof(char));
    char ch;
    //getchar();
    while (1)
    {
        if (str_len >= capacity-1){
            capacity += BLOCK_SIZE;
            char* first_str_ptr = realloc(first_str, capacity * sizeof(char));
            if (first_str_ptr != NULL)
                first_str = first_str_ptr;
            else return first_str;
        }
        ch = getchar();
        if ((ch == '\n') && (str_len == 0))
            continue;
        if (ch == '\n')
            break;
        first_str[str_len] = ch;
        str_len++;
    }
    first_str[str_len] = '\0';
    return first_str;
}

int check_num_of_capital(char *sentence)
{
    size_t len = strlen(sentence);
    int capital_count = 0;
    for(int i = 0; i < len; i++){
        if (isupper(sentence[i])){
            capital_count++;
        }
    }
    return capital_count;

}

void removing_many_capitals(char **text, int sentence_count, char* first_str)
{
    int first_capital = check_num_of_capital(first_str);
    printf("capital letters in {%s} == %d", first_str, first_capital);
    printf("\nTEXT:\n");
    for (int i = 0; i < sentence_count; i++){
        if (check_num_of_capital(text[i]) > first_capital){
            free(text[i]);
            text[i] = NULL;
        }
        else printf("%s\n", text[i]);
    }
}

int check_sum_of_digits(char *sentence)
{
    size_t len = strlen(sentence);
    int sum_of_digits = 0;
    for(int i = 0; i < len; i++){
        if (isdigit(sentence[i])){
            sum_of_digits += sentence[i] - '0';
        }
    }
    return sum_of_digits;
}

void sum_of_digits(char **text, int sentence_count, char* first_str)
{
    int first_sum = check_sum_of_digits(first_str);
    int sum_of_digits = 0;
    for (int i = 0; i < sentence_count; i++){
        sum_of_digits = check_sum_of_digits(text[i]);
        if (sum_of_digits > first_sum)
             printf("(%d) %s\n", (sum_of_digits - first_sum), text[i]);
    }
}

void menu(int item)
{
    int sentence_count = 0;
    char** text = NULL;
    char *first_str = NULL;

    switch (item)
    {
    	case 0:
        	text = get_sentences(&sentence_count);
        	print_format_text(text, sentence_count);
        	break;

    	case 1:
		text = get_sentences(&sentence_count);
        	sort_by_time(text, sentence_count);
        	break;

	case 2:
	    	text = get_sentences(&sentence_count);
        	word_count_check(text, sentence_count);
		break;

	case 3:
	    	text = get_sentences(&sentence_count);
		lowercase_consonants_letters(text, sentence_count);
        	break;

	case 4:
	    	text = get_sentences(&sentence_count);
	    	check_average_words_count(text, sentence_count);
		break;

    	case 5:
        	printf(HELP_MSG);
        	break;

    case 8:
        first_str = get_first_str();
        text = get_sentences(&sentence_count);
        sum_of_digits(text, sentence_count, first_str);
        break;

    	default:
        	printf(ERR_COMMAND_DOES_NOT_EXIST);
        	break;
    }
    complete_clean(text, sentence_count);
}

int main(){
	int item = 0;
	printf("Course work for option 4.21, created by Malakhov Artem.\n");
	scanf("%d", &item);
	menu(item);
	return 0;
}
