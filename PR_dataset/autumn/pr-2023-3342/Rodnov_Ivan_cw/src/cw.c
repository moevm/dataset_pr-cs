#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MEM_STEP 10
#define END_OF_STRING '\n'


void print_student_info()
{
    printf("Course work for option 4.1, created by Ivan Rodnov\n");
}
//Посимвольный ввод текста
char* get_sentence(int* nl_count)
{
    int size = MEM_STEP;
    char* sentence = malloc(size*sizeof(char));
    if (sentence == NULL) {
        printf("Error: Memory allocation error for sentence\n");
    }
    int sentence_len = 0;
    char temp_char;
    do
    {
        temp_char = getchar();
        if(temp_char == END_OF_STRING)
        {
            (*nl_count)++;
            if (*nl_count == 2)
            {
                break;
            }
        }
        else
        {
            *nl_count = 0;
        }

        if(sentence_len == 0 && (temp_char == ' ' || temp_char == '.' || temp_char == '\n'))
        {
            continue;
        }
        else
        {   
            sentence[sentence_len] = temp_char;
            sentence_len++;
            if(sentence_len == size - 1)
            {
                size += MEM_STEP;
                sentence = realloc(sentence, sizeof(char) * size);
                if (sentence == NULL) {
                    printf("Error: Memory allocation error for sentence\n");
                }
            }
        }
    } while (temp_char != '.');
    sentence[sentence_len] = '\0';
    
    return sentence;
}

char** make_text(int* text_len){
    int size = MEM_STEP;
    char** text = malloc((size + 1) * sizeof(char*));
    if (text == NULL) {
        printf("Error: Memory allocation error for text\n");
    }
    int local_text_len = 0;
    int nl_count = 0;
    char* temp_sentence;
    while(1)
    {   
        temp_sentence = get_sentence(&nl_count);
        int len_sentence = strlen(temp_sentence);
        if (nl_count == 2)
        {
            break;
        }
        else
        {
            nl_count = 0;
            if (len_sentence == 0){
                continue;
            }
            text[local_text_len] = temp_sentence;
            local_text_len++;
            if(local_text_len == size - 1)
            {
                size += MEM_STEP;
                text = realloc(text, sizeof(char*) * size);
                if (text == NULL) {
                    printf("Error: Memory allocation error for text\n");
                }
            }
        }  
    }
    *text_len = local_text_len;
    return text;
}

//Удаление одинаковых предложений
int comp_letters(char f, char s) {
    if ((isdigit(f) && isdigit(s) && f != s) ||
        (isalpha(f) && isalpha(s) && toupper(f) != toupper(s)) ||
        (!isalnum(f) && !isalnum(s) && f != s))
    {
        return 0;
    }
    return 1;
}

int comp_str(char* f, char* s)
{
    int f_len = strlen(f);
    int s_len = strlen(s);
    if(f_len != s_len)
    {
        return 0;
    }
    else
    {
        for(int i = 0; i < f_len; i++)
        {
            if(comp_letters(f[i],s[i]) == 0)
            {
                return 0;
            }
        }
    }
    return 1;   
}

char** delete_duplicate(char** text, int* text_len)
{
    int *check_arr = calloc(*(text_len), sizeof(int));
    if (check_arr == NULL) {
        printf("Error: Memory allocation error for check_arr\n");
    }
    char** uniqe_text = malloc(*(text_len) * sizeof(char*));
    if (uniqe_text == NULL) {
        printf("Error: Memory allocation error for uniqe_text\n");
    }
    for(int i = 0; i < *text_len; i++)
    {
        for(int j = i+1; j < *text_len; j++)
        {
            if(comp_str((text)[i], (text)[j]) == 1)
            {
                check_arr[j] = 1;
            }
        }
    }
    int b = 0;
    for(int i = 0; i < *text_len; i++)
    {
        if(check_arr[i] == 0)
        {
            uniqe_text[b] = text[i];
            b++;
        }
    }
    *text_len = b;
    free(check_arr);
    return uniqe_text;
}
//Делим предложения на слова

char** split_sentence(char* sentence, int* word_count)
{
    int vol_words = MEM_STEP;
    int count = 0;
    char** words = malloc(vol_words * sizeof(char*));
    if (words == NULL) {
        printf("Error: Memory allocation error for words\n");
    }
    char* copy_sentence = malloc((strlen(sentence)+1)*sizeof(char));
    if (copy_sentence == NULL) {
        printf("Error: Memory allocation error for copy_sentence\n");
    }
    strcpy(copy_sentence, sentence);
    char* token = strtok(copy_sentence, " .,");
    while (token!=NULL)
    {
        if (count  >= vol_words)
        {
            vol_words *= 2;
            words = realloc(words, vol_words*sizeof(char*));
            if (words == NULL) {
                printf("Error: Memory allocation error for words\n");
            }
        }
        words[count] = malloc((strlen(token)+1)*sizeof(char));
        if (words[count] == NULL) {
                printf("Error: Memory allocation error for words[count]\n");
        }
        strcpy(words[count], token);
        words[count][strlen(token)] = '\0';
        count++;
        token = strtok(NULL, " .,");
    }
    *word_count = count;
    return words;
}

void word_counter(char* sentence, int* word_count)
{
    int vol_words = MEM_STEP;
    int count = 0;
    char** words = malloc(vol_words * sizeof(char*));
    if (words == NULL) {
        printf("Error: Memory allocation error for words\n");
    }
    char* copy_sentence = malloc((strlen(sentence)+1)*sizeof(char));
    if (copy_sentence == NULL) {
        printf("Error: Memory allocation error for copy_sentence\n");
    }
    strcpy(copy_sentence, sentence);
    char* token = strtok(copy_sentence, " .,");
    while (token!=NULL)
    {
        if (count  >= vol_words)
        {
            vol_words *= 2;
            words = realloc(words, vol_words*sizeof(char*));
            if (words == NULL) {
                printf("Error: Memory allocation error for words\n");
            }
        }
        words[count] = malloc((strlen(token)+1)*sizeof(char));
        if (words[count] == NULL) {
            printf("Error: Memory allocation error for words[count]\n");
        }
        strcpy(words[count], token);
        words[count][strlen(token)] = '\0';
        count++;
        token = strtok(NULL, " .,");
    }
    *word_count = count;

}


//Исполнение 1 задачи
void f_upper(char** new_text, int* text_len)
{
    for(int i = 0; i < *text_len; i++)
    {
        int str_len = strlen(new_text[i]);
        for(int j = 0; j < str_len; j++)
        {
            if(j == 0)
            {
                new_text[i][j] = toupper(new_text[i][j]);
            }
            else
            {
                new_text[i][j] = tolower(new_text[i][j]);
            }
        }
    }
    for(int i = 0; i < *text_len; i++)
    {
        printf("%s\n", new_text[i]);
    }
}
//Исполнение 2 функции
void remove_even_word_sentences(char** new_text, int* text_len)
{
    char** formated_text = malloc(*text_len * sizeof(char*));
    if (formated_text == NULL) {
        printf("Error: Memory allocation error for formated_text\n");
    }
    int c = 0;
    for(int i = 0; i < *text_len; i++)
    {
        int word_count = 0;
        word_counter(new_text[i], &word_count);
        if(word_count % 2 != 0)
        {
            formated_text[c] = malloc(strlen(new_text[i]) * sizeof(char));
            if (formated_text[c] == NULL) {
                printf("Error: Memory allocation error for formated_text[c]\n");
            }
            strcpy(formated_text[c], new_text[i]);
            c++;
        }
    }
    *text_len = c;
    for(int i = 0; i < *text_len; i++)
    {
        printf("%s\n", formated_text[i]);
    }
}
//Исполнение 3 функции
int isVowel(char c) {
    c = tolower(c);
    return (strchr("aeiou", c) != NULL);
}

int summ_of_vowels(char* sentence, int sentence_len)
{
    int c = 0;
    int word_count = 0;
    char** splited_sentence = split_sentence(sentence, &word_count);

    for(int i = 0; i < word_count; i++)
    {
        if(i % 2 == 0)
        {
            for(int j = 0; j < strlen(splited_sentence[i]); j++)
            {
                if(isVowel(splited_sentence[i][j]))
                {
                    c++;      
                }
            }
        }
    }
    return c;
}

int cmp(const void* a, const void* b)
{
    char* first = *(char**)a;
    char* second = *(char**)b;
    int summ_f = summ_of_vowels(first, strlen(first));
    int summ_s = summ_of_vowels(second, strlen(second));
    return summ_s - summ_f;
}

void sort_by_vowels(char** new_text, int* text_len)
{
    qsort(new_text, *text_len, sizeof(char*), cmp);
    for(int i = 0; i < *text_len; i++)
    {
        printf("%s\n", new_text[i]);
    }
}

//Исполнение 4 функции
int all_upper(char* word, int word_len)
{
    int c = 0;
    for(int i = 0; i < word_len; i++)
    {
        if(isupper(word[i]))
        {
            c++;
            if(c == word_len)
            {
                return 1;
            }
        }
    }
    return 0;
}

void print_blue(char** new_text, int* text_len)
{
    for(int i = 0; i < *text_len; i++)
    {
        int c = 0;
        int to_print = 0;
        int word_count = 0;
        char** splited_sentence = split_sentence(new_text[i], &word_count);
        for(int k = 1; k < word_count - 1; k++)
        {
            if(all_upper(splited_sentence[k], strlen(splited_sentence[k])))
            {
                to_print = 1;
            }
        }
        if(word_count > 2 && to_print != 0)
        {
            for(int j = 0; j < strlen(new_text[i]); j++)
            {
                if((new_text[i][j] == ' ' || new_text[i][j] == ',') && (new_text[i][j-1] != ' ' && new_text[i][j-1] != ','))
                {
                    c++;
                }
                if((c > 0 && c < word_count - 1) && isalnum(new_text[i][j]) && all_upper(splited_sentence[c], strlen(splited_sentence[c])))
                {
                    printf("\x1b[34m%c\x1b[0m", new_text[i][j]);
                }
                else if(new_text[i][j] == '.')
                {
                    printf(".\n");
                }
                else
                {
                    printf("%c", new_text[i][j]);
                }
            }
        }
    }
}

//Задача на защиту
void delete_upper(char** new_text, int* text_len, char* first_sentence){
    int first_count = 0;
    for(int k = 0; k < strlen(first_sentence); k++){
        if(isupper(first_sentence[k]) != 0){
            first_count++;
        }
    }
    int c = 0;
    for(int i = 0; i < *text_len; i++){
        for(int j = 0; j < strlen(new_text[i]); j++){
            if(isupper(new_text[i][j]) != 0){
                c++;
            }
        }
        if(c <= first_count){
            printf("%s\n", new_text[i]);
        }
        c = 0;
    }
}

//Вывод справки
void print_CW_info()
{
    printf("This program can change text like this:\n");
    printf("0) Print text in which all duplicate sentences have been removed.\n");
    printf("1) Transform sentences so that each first word begins with a capital letter and all others are lowercase.\n");
    printf("2) Remove all sentences containing an even number of words.\n");
    printf("3) Sort the sentences by the sum of the number of vowels in every second word.\n");
    printf("4) Print all sentences in the middle of which there are words consisting of capital letters. These words are highlighted in blue.\n");
}

//Вывод
void print_text(char** text, int text_len)
{
    for (int i = 0; i < text_len; i++)
    {
        printf("%s\n", text[i]);
    }
}

int main(void)
{
    print_student_info();
    int text_len = 0;
    int func_num;
    scanf("%d", &func_num);
    if (func_num == 5){
        print_CW_info();
        return 0;
    }
    //
    int size = MEM_STEP;
    char* first_sentence = malloc(size*sizeof(char));
    int sentence_len = 0;
    char temp_char;
    if (func_num == 8){
        getchar();
        do
        {
            temp_char = getchar();
            if(sentence_len == 0 && (temp_char == ' ' || temp_char == '.'))
            {
                continue;
            }
            else
            {   
                first_sentence[sentence_len] = temp_char;
                sentence_len++;
                if(sentence_len == size - 1)
                {
                    size += MEM_STEP;
                    first_sentence = realloc(first_sentence, sizeof(char) * size);
                }
            }
        } while (temp_char != '\n');
        first_sentence[sentence_len] = '\0';
    }
    char** text;
    char** new_text;
    switch (func_num)
    {
    case 0:
        text = make_text(&text_len);
        new_text = delete_duplicate(text, &text_len);
        print_text(new_text, text_len);
        break;
    case 1:
        text = make_text(&text_len);
        new_text = delete_duplicate(text, &text_len);
        f_upper(new_text, &text_len);
        break;
    case 2:
        text = make_text(&text_len);
        new_text = delete_duplicate(text, &text_len);
        remove_even_word_sentences(new_text, &text_len);
        break;
    case 3:
        text = make_text(&text_len);
        new_text = delete_duplicate(text, &text_len);
        sort_by_vowels(new_text, &text_len);
        break;
    case 4:
        text = make_text(&text_len);
        new_text = delete_duplicate(text, &text_len);
        print_blue(new_text, &text_len);
        break;
    case 8:
        text = make_text(&text_len);
        new_text = delete_duplicate(text, &text_len);
        delete_upper(new_text, &text_len, first_sentence);
        break;
    default:
        printf("Error: Wrong function number!");
        break;
    }
    return 0;
}
