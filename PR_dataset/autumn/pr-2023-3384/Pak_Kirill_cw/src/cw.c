#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_info();
void removeLeadingWhitespace(char* str);
char** read_text(int* num_sentences);
void print_sentences(char** sentences, int num_sentences);
void remove_duplicates(char** sentences, int* num_sentences);
void print_digit_sentences(char** sentences, int num_sentences);
int count_uppercase_letters(const char* sentence);
int compare_sentences(const void* a, const void* b);
void sort_by_uppercase_count(char** sentences, int num_sentences);
void remove_sentences_with_word(char*** sentences, int* num_sentences, const char* word);
void replace_digits(char** sentences, int num_sentences);


void print_info()
{
    printf("Course work for option 4.3, created by Kirill Pak.\n");
}


void removeLeadingWhitespace(char* str)
{
    int i = 0;
    while (isspace(str[i])) {
        i++;
    }

    int j = 0;
    while (str[i]) {
        str[j++] = str[i++];
    }

    str[j] = '\0';
}


char** read_text(int* num_sentences) {
    int max_sentences = 100;
    char** sentences = (char**)malloc(max_sentences * sizeof(char*));
    *num_sentences = 0;

    char buffer[1000];
    int consecutiveNewlines = 0;

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (buffer[0] == '\0') {
            consecutiveNewlines++;
            if (consecutiveNewlines >= 1) {
                break;
            }
        }
        else {
            consecutiveNewlines = 0;

            char* token = strtok(buffer, ".");
            while (token != NULL) {
                char* start = token;
                while (*start == ' ') start++;

                char* end = token + strlen(token) - 1;
                while (end > start && *end == ' ') end--;

                char* sentence = (char*)malloc((end - start + 3) * sizeof(char));
                if (sentence == NULL) {
                    printf("Error:<Memory reallocation>");
                    exit(0);
                }

                strncpy(sentence, start, end - start + 1);

                sentence[end - start + 1] = '.';
                sentence[end - start + 2] = '\0';

                if (*num_sentences >= max_sentences) {
                    max_sentences *= 2;
                    sentences = (char**)realloc(sentences, max_sentences * sizeof(char*));
                    if (sentences == NULL) {
                        printf("Error:<Memory reallocation>");
                        exit(0);
                    }
                }

                sentences[*num_sentences] = sentence;
                (*num_sentences)++;

                token = strtok(NULL, ".");
            }
        }
    }

    for (int i = 0; i < *num_sentences; ++i) {
        removeLeadingWhitespace(sentences[i]);
    }

    return sentences;
}

void print_sentences(char** sentences, int num_sentences) {
    for (int i = 0; i < num_sentences; ++i) {
        printf("%s\n", sentences[i]);
    }
}


int case_insensitive_strcmp(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return (int)tolower((unsigned char)*s1) - (int)tolower((unsigned char)*s2);
        }
        ++s1;
        ++s2;
    }
    return (int)tolower((unsigned char)*s1) - (int)tolower((unsigned char)*s2);
}

void remove_duplicates(char** sentences, int* num_sentences) {
    for (int i = 0; i < *num_sentences - 1; ++i) {
        for (int j = i + 1; j < *num_sentences;) {
            if (case_insensitive_strcmp(sentences[i], sentences[j]) == 0) {
                free(sentences[j]);
                for (int k = j; k < *num_sentences - 1; ++k) {
                    sentences[k] = sentences[k + 1];
                }
                (*num_sentences)--;
            }
            else {
                ++j;
            }
        }
    }
}

void print_digit_sentences(char** sentences, int num_sentences)
{
    for (int i = 0; i < num_sentences; ++i)
    {
        int is_digit_sentence = 1;
        for (int j = 0; sentences[i][j] != '\0'; ++j)
        {
            if (!((sentences[i][j] >= '0' && sentences[i][j] <= '9') || sentences[i][j] == ' ' || sentences[i][j] == '.'))
            {
                is_digit_sentence = 0;
                break;
            }
        }

        if (is_digit_sentence)
        {
            printf("%s\n", sentences[i]);
        }
    }
}

int count_uppercase_letters(const char* sentence)
{
    int count = 0;
    for (int i = 0; sentence[i] != '\0'; ++i)
    {
        if (isupper(sentence[i]))
        {
            count++;
        }
    }
    return count;
}

int compare_sentences(const void* a, const void* b) {
    const char* sentence_a = *(const char**)a;
    const char* sentence_b = *(const char**)b;

    int count_a = count_uppercase_letters(sentence_a);
    int count_b = count_uppercase_letters(sentence_b);

    return count_b - count_a;
}

void sort_by_uppercase_count(char** sentences, int num_sentences) {
    qsort(sentences, num_sentences, sizeof(char*), compare_sentences);
}

void remove_sentences_with_word(char*** sentences, int* num_sentences, const char* word)
{
    int removed = 0;
    char** updated_sentences = (char**)malloc(*num_sentences * sizeof(char*));

    for (int i = 0, j = 0; i < *num_sentences; ++i)
    {
        int occurrences = 0;
        const char* pos = (*sentences)[i];

        while ((pos = strstr(pos, word)) != NULL)
        {
            occurrences++;
            pos += strlen(word);
            if(occurrences==2){
                break;
            }
        }

        if (occurrences <2)
        {
            updated_sentences[j++] = (*sentences)[i];
        }
        else
        {
            free((*sentences)[i]);
            removed++;
        }
    }

    *sentences = updated_sentences;
    *num_sentences -= removed;
}

void replace_digits(char** sentences, int num_sentences)
{
    for (int i = 0; i < num_sentences; ++i)
    {
        for (int j = 0; sentences[i][j] != '\0'; ++j)
        {
            if (sentences[i][j] >= '0' && sentences[i][j] <= '9')
            {
                switch (sentences[i][j])
                {
                case '0':
                    printf("Zero");
                    break;
                case '1':
                    printf("One");
                    break;
                case '2':
                    printf("Two");
                    break;
                case '3':
                    printf("Three");
                    break;
                case '4':
                    printf("Four");
                    break;
                case '5':
                    printf("Five");
                    break;
                case '6':
                    printf("Six");
                    break;
                case '7':
                    printf("Seven");
                    break;
                case '8':
                    printf("Eight");
                    break;
                case '9':
                    printf("Nine");
                    break;
                default:
                    break;
                }
            }
            else
            {
                putchar(sentences[i][j]);
            }
        }
        putchar('\n');
    }
}


int main()
{
    print_info();
    char word[100];
    int num_sentences = 0;
    char** sentences = NULL;
    int choice;
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 0:
        sentences = read_text(&num_sentences);
        remove_duplicates(sentences, &num_sentences);
        print_sentences(sentences, num_sentences);
        break;

    case 1:
        sentences = read_text(&num_sentences);
        remove_duplicates(sentences, &num_sentences);
        print_digit_sentences(sentences, num_sentences);
        break;

    case 2:
        sentences = read_text(&num_sentences);
        remove_duplicates(sentences, &num_sentences);
        sort_by_uppercase_count(sentences, num_sentences);
        print_sentences(sentences, num_sentences);
        break;

    case 3:
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")-1] = '\0';
        sentences = read_text(&num_sentences);
        remove_duplicates(sentences, &num_sentences);
        remove_sentences_with_word(&sentences, &num_sentences, word);
        print_sentences(sentences, num_sentences);
        break;

    case 4:
        sentences = read_text(&num_sentences);
        remove_duplicates(sentences, &num_sentences);
        replace_digits(sentences, num_sentences);
        break;

    case 5: 
        printf("This program performs various operations on a set of input sentences.\n");
        printf("Options:\n");
        printf("0 Remove duplicates\n");
        printf("1 Print sentences with only digits\n");
        printf("2 Sort by uppercase count\n");
        printf("3 Remove sentences with a specific word\n");
        printf("4 Replace digits\n");
        break;
    default:
        printf("Error:<Invalid choice>\n");
    }

    for (int i = 0; i < num_sentences; ++i)
    {
        free(sentences[i]);
    }
    free(sentences);

    return 0;
}