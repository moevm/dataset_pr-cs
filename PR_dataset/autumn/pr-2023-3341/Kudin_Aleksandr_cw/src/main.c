#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#define AUTHOR_INFO "Course work for option 4.4, created by Aleksandr Kudin.\n"


char* read_text(int* text_size, int* sentence_count) {
    int capacity = 1;
    *text_size = 0;
    *sentence_count = 0;
    char* text = (char*) malloc(sizeof(char));
    int newline_count = 0;
    char ch = getchar();

    while (true) {
        if ((*text_size) + 1 >= capacity) {
            capacity *= 2;
            text = (char*) realloc(text, capacity * sizeof(char));
        }

        if (ch == '\n') {
            newline_count++;
            if (newline_count == 2) {
                break;
            }
        } else {
            newline_count = 0;
            if (ch == '.') {
                (*sentence_count)++;
            }
        }

        text[*text_size] = ch;
        (*text_size)++;
        ch = getchar();
    }

    text[*text_size - 2] = '\0';

    return text;
}

char** split_text(char* text, char** sentences) {
    const char sep[] = ".";
    char* substr;

    substr = strtok(text, sep);
    int i = 0;
    while (substr != NULL) {
        while(isspace(*substr)){
            substr++;
        }
        sentences[i] = substr;
        i++;
        substr = strtok(NULL, sep);
    }
    return sentences;
}

void print_sentences(char** sentences, int sentence_count) {
    for (int i = 0; i < sentence_count; i++) {
        if (sentences[i][0] != '\0') {
            printf("%s.\n", sentences[i]);
        }
    }
}
char* to_upper(const char* str) {
    char* cpy = (char*) calloc(strlen(str) + 1, sizeof(char));
    strcpy(cpy, str);
    for (int i = 0; i < strlen(cpy); i++) {
        cpy[i] = toupper(cpy[i]);
    }
    return cpy;
}

char** remove_duplicates(char** sentences, int* sentencesNumber) {
    int uniqueCount = 0;

    for (int i = 0; i < *sentencesNumber; i++) {
        int isDuplicate = 0;
        char* upperSentence = to_upper(sentences[i]);

        for (int j = 0; j < i; j++) {
            char* otherUpperSentence = to_upper(sentences[j]);
            if (strcmp(upperSentence, otherUpperSentence) == 0) {
                isDuplicate = 1;
                free(otherUpperSentence);
                break;
            }
            free(otherUpperSentence);
        }

        free(upperSentence);

        if (!isDuplicate) {
            sentences[uniqueCount++] = sentences[i];
        }
    }

    *sentencesNumber = uniqueCount;
    return sentences;
}

typedef struct {
    int year;
    int month;
    int day;
} Date;


int compareDates(const void *a, const void *b) {
    const Date *date_first = (const Date *)a;
    const Date *date_second = (const Date *)b;
    if (date_first->year != date_second->year) return date_first->year - date_second->year;
    if (date_first->month != date_second->month) return date_first->month - date_second->month;
    return date_first->day - date_second->day;
}

void findAndPrintDates(char **sentences, int sentenceCount) {
    int initialCapacity = 10;
    int dateCount = 0;
    Date *dates = malloc(initialCapacity * sizeof(Date));

    for (int s = 0; s < sentenceCount; s++) {
        char *p = sentences[s];
        int day, month, year;

        while (*p) {
            if (sscanf(p, "d%2dm%2dy%4d", &day, &month, &year) == 3) {
                if (day > 0 && day <= 31 && month > 0 && month <= 12 && year >= 0) {
                    if (dateCount == initialCapacity) {
                        initialCapacity *= 2;
                        dates = realloc(dates, initialCapacity * sizeof(Date));
                    }
                    dates[dateCount++] = (Date){year, month, day};
                }
                p = strstr(p, "y");
                if (p) p += 1;
            } else {
                p++;
            }
        }
    }

    qsort(dates, dateCount, sizeof(Date), compareDates);

    for (int i = 0; i < dateCount; i++) {
        printf("%02d:%02d:%04d\n", dates[i].day, dates[i].month, dates[i].year);
    }

    free(dates);
}

int countWords(const char *sentence) {
    int count = 0;
    const char *wordStart = NULL;
    while (*sentence) {
        if (!wordStart && isalnum((unsigned char)*sentence)) {
            wordStart = sentence;
        } else if (wordStart && !isalnum((unsigned char)*sentence)) {
            count++;
            wordStart = NULL;
        }
        sentence++;
    }
    if (wordStart) {
        count++;
    }
    return count;
}

void removeSentencesWithOddWordCount(char **sentences, int *sentenceCount) {
    int writeIndex = 0;
    for (int i = 0; i < *sentenceCount; i++) {
        if (countWords(sentences[i]) % 2 == 0) {
            sentences[writeIndex++] = sentences[i];
        }
    }
    *sentenceCount = writeIndex;
}
int contains_digits(const char *word) {
    while (*word) {
        if (isdigit((unsigned char)*word)) {
            return 1;
        }
        word++;
    }
    return 0;
}
void capitalizeWordsWithoutDigits(char *sentence) {
    char *start = sentence;
    char *current = sentence;

    while (*current) {
        if (*current == ' ' || *current == '\0') {
            if (!contains_digits(start)) { 
                while (start < current - 1) { 
                    *start = toupper((unsigned char)*start);
                    start++;
                }
            }
            start = current + 1;
        }
        current++;
    }
    if (!contains_digits(start)) {
        while (start < current - 1) {
            *start = toupper((unsigned char)*start);
            start++;
        }
    }
}
int containsNoUppercase(const char *sentence) {
    while (*sentence) {
        if (isupper((unsigned char)*sentence)) {
            return 0;
        }
        sentence++;
    }
    return 1;
}


void printSentencesWithoutUppercase(char **sentences, int num_sentences) {
    for (int i = 0; i < num_sentences; i++) {
        if (containsNoUppercase(sentences[i])) {
            if (sentences[i][0] != '\0') {
                printf("%s.\n", sentences[i] + 1);
        }
        }
    }
}

void itbn(int n){
    int b[100];
    int size = 0;
    while(n > 0){
        b[size] = n % 2;
        n /= 2;
        size++;
    }
    printf("0b");
    for(int i = size-1;i>=0;i--){
        printf("%d",b[i]);
    }
}


void rntb(char* sentence){
    char* num = (char*)calloc(1000, sizeof(char));
    int j = 0;
    for(int i = 0; i < strlen(sentence); i++){
        if(isdigit(sentence[i])){
            num[j] = sentence[i];
            j++;
        }
        else{
            if(num[0] != '\0'){
                itbn(atoi(num));
                j = 0;
                num = (char*)calloc(1000,sizeof(char));
            }
            printf("%c",sentence[i]);
        }
    }
    if(num[0] != '\0'){
        itbn(atoi(num));
    }
}



void output(int command){
    if(command == 5){
        printf("function info:\n\
        1 - Finds dates in the entire text in the form “d<day>m<month>y<year>”, sorts, displays in ascending order in the format DD:MM:YYYY.\n\
        2 - Removes all sentences with an odd number of words.\n\
        3 - For each word in sentences, converts letters to capitals except the last one if the word does not contain numbers.\n\
        4 - Displays sentences without capital letters.\n");
        return;
    }
    int sentence_count_before = 0;
    int text_size = 0;
    char* text = read_text(&text_size, &sentence_count_before);

    char** sentences = malloc((sentence_count_before+1) * sizeof(char*));
    sentences = split_text(text, sentences);

    sentences = remove_duplicates(sentences,&sentence_count_before);

    switch (command) {
        case 0:
            print_sentences(sentences,sentence_count_before);
            break;
        case 1:
            findAndPrintDates(sentences, sentence_count_before);
            break;
        case 2:
            removeSentencesWithOddWordCount(sentences, &sentence_count_before);
            print_sentences(sentences,sentence_count_before);
            break;
        case 3:
            for (int i = 0; i < sentence_count_before; i++) {
                capitalizeWordsWithoutDigits(sentences[i]);
            }
            print_sentences(sentences,sentence_count_before);
            break;
        case 4:
            printSentencesWithoutUppercase(sentences, sentence_count_before);
            break;
        case 9:
            for(int i =0; i<sentence_count_before; i++){
                rntb(sentences[i]);
                printf(".\n");
    }       break;
        default:
            printf("Error: Invalid command\n");
            break;
    }
    free(text);
    free(sentences);
}
int main() {
    printf(AUTHOR_INFO); 
    int command;
    scanf("%d", &command); 
    output(command);
    
    return 0;
}
