#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<strings.h>
#include<string.h>
#include<ctype.h>
#define FIRST_MESSAGE "Course work for option 4.16, created by Mikhail Pyankov.\0"
#define BASE_SIZE 300
#define BLUE "define BLUE"
#define ZERO_FUNC "0: Text output after initial mandatory processing.\0"
#define FIRST_FUNC "1: Print each sentence, and if it contains the phrase “define BLUE”, then print all words after this phrase in blue.\0"
#define SECOND_FUNC "2: In the entire text, replace the sequence of consecutive letters without taking into\naccount case with a substring of the form “<number of consecutive letters><letter in upper case>”.\0"
#define THIRD_FUNC "3: Delete all sentences in which the number of words is a multiple of three.\0"
#define FOURTH_FUNC "4: Sort sentences by decreasing the total length of the first and last word.\0"
#define ERROR_MSG "ERROR: Incorrect instruction.\0"
#define ERROR_DOT_MSG "ERROR: Forgotten dot.\0"
#define SPACE ' '
#define COMMA ','
#define DOT '.'
#define TAB '\t'
#define STR_END '\0'
#define NEXT_LINE '\n'
#define BLUE_CHAR "\e[1;34m%c\e[m"

void erase(char** text, int *text_length, int index)
{
    for(int i = index; i < *text_length-1; i++)
    {
        strcpy(text[i], text[i+1]);
    }
    free(text[*text_length-1]);
    *text_length-=1;
}

int words_count(char* sentence)
{
    int result = 0;
    for(int i = 0; i < strlen(sentence); i++)
    {
        if(sentence[i] == SPACE)
        result++;
    }
    return result+1;
}

int words_length_counter(char* sentence)
{
    if(words_count(sentence)==1)
    return strlen(sentence)-1;
    int result = 0;
    for(int i = 0 ; i < strlen(sentence); i++)
    {
        if(sentence[i] != COMMA && sentence[i] != SPACE)
        result++;
        if(sentence[i] == SPACE)
        break;
    }
    for(int i = strlen(sentence)-1; i >= 0; i--)
    {
        if(sentence[i] != COMMA && sentence[i] != SPACE)
        result++;
        if(sentence[i] == SPACE)
        break;
    }
    return result;
}

int compare_func(const void* first_sentence, const void* second_sentence)
{
    return  words_length_counter(*(char**)first_sentence) - words_length_counter(*(char**)second_sentence);
}

void removing_repetitions(char** text, int* text_length)
{
    int j;
    int i = 0;
    while(i < *text_length)
    {
        j = i + 1;
        while(j < *text_length)
        {
            if(strcasecmp(text[i], text[j])==0)
            erase(text, *&text_length, j);
            j++;
        }
        i++;
    }
}

void key_input(int* key)
{
    scanf("%d", key);
}

char** text_input(int* text_length)
{
    char** text = malloc(BASE_SIZE*sizeof(char*));
    char* sentence;
    int sentence_length;
    int sentence_size_count;
    int text_size_count = 1;
    char c;
    char previos_c;
    while(1)
    {
        sentence = malloc(BASE_SIZE*sizeof(char));
        sentence_length = 0;
        sentence_size_count = 1;
        while(1)
        {
            c = getchar();
            if(sentence_length >= BASE_SIZE*sentence_size_count)
            {
                sentence_size_count+=1;
                sentence = realloc(sentence, (BASE_SIZE*sentence_size_count)*sizeof(char));
            }
            if(c != NEXT_LINE && !(sentence_length==0 && (c==SPACE||c==TAB)))
            {
                sentence[sentence_length] = c;
                sentence_length+=1;
            }
            if(c == NEXT_LINE && previos_c == NEXT_LINE)
            {
                if(sentence_length!=0)
                {
                    sentence[sentence_length] = STR_END;
                    text[*text_length] = sentence;
                    *text_length+=1;
                }
                return text;
            }
            if(c == DOT)
            {
                sentence[sentence_length] = STR_END;
                break;
            }
            previos_c = c;
        }
        if(*text_length >= text_size_count)
        {
            text_size_count+=1;
            text = realloc(text, (BASE_SIZE*text_size_count)*sizeof(char*));
        }
        text[*text_length] = sentence;
        *text_length+=1;
    }
}

void first_func(char** text, int text_length)
{
    int index;
    for(int i = 0; i < text_length; i++)
    {
        if(strstr(text[i], BLUE)!=NULL)
        {
            index = (int)(strstr(text[i], BLUE) - text[i]) + strlen(BLUE);
            for(int j = 0; j < index; j++)
            printf("%c", text[i][j]);
            for(int j = index; j < strlen(text[i]); j++)
            printf(BLUE_CHAR, text[i][j]);
            printf("\n");
        }
        else
        puts(text[i]);
    }
}

void second_func(char** text, int text_length)
{
    int new_sentence_length = 0;
    char* new_sentence;
    for(int i = 0; i < text_length; i++)
    {
        new_sentence = malloc(strlen(text[i]));
        new_sentence_length = 0;
        char symbol = text[i][0];
        int symbol_count;
        int j = 1;
        while(j < strlen(text[i])+1)
        {
            symbol_count = 0;
            while(tolower(text[i][j]) == tolower(symbol))
            {
                symbol_count +=1;
                j+=1;
            }
            if(symbol_count)
            {
                char str[100];
                snprintf(str, sizeof(str), "%d", symbol_count+1);
                strcpy(new_sentence+new_sentence_length, str);
                new_sentence_length+=strlen(str);
                new_sentence[new_sentence_length] = toupper(symbol);
                new_sentence_length+=1;
                
            }
            else
            {
                new_sentence[new_sentence_length] = symbol;
                new_sentence_length+=1;
            }
            symbol = text[i][j];
            j+=1;
        }
        new_sentence[new_sentence_length] = STR_END;
        text[i] = new_sentence;
    }
}

void third_func(char** text, int* text_length)
{
    int i = 0;
    while( i < *text_length)
    {
        if(words_count(text[i])%3 == 0)
        {
            erase(text, text_length, i);
            i--;
        }
        i++;
    }
}

void fourth_func(char** text, int text_length)
{
    qsort(text, text_length, sizeof(char*), compare_func);
}

int word_sum_digits(char* string)
{
    int sum = 0;
    for(int i = 0; i< strlen(string); i++)
    {
        if(string[i] - '0' >= 0 && string[i] - '0' < 10)
        {
            sum+=string[i] - '0';
        }
    }
    return sum;
}

int cmp_func(const void* first_string, const void* second_string)
{
    return (word_sum_digits(*(char**)first_string) - word_sum_digits(*(char**)second_string));
}

char* split(char* string)
{
    char * pch = strtok (string," ");
    int i = 0;
    char** new_cifar_string = malloc(strlen(string)*sizeof(char*));
    while(pch !=NULL)
    {
        new_cifar_string[i] = pch;
        i++;
        pch = strtok(NULL, " ,.");
        
    }
    char* new_string = malloc(strlen(string)*sizeof(char)+10);
    new_string[0]='\0';
    qsort(new_cifar_string, i, sizeof(char*), cmp_func);
    for(int k = 0; k < i; k++)
    {
        strcat(new_string, new_cifar_string[k]);
        strcat(new_string, " ");
    }
    strcat(new_string, "\0");
    return new_string;
}

void nineth_func(char** text, int text_length)
{
    for(int i = 0; i < text_length; i++)
    {
        text[i] = split(text[i]);
    }
}

void switch_func(char** text, int* text_length, int key)
{
    switch(key)
    {
        case 0:
            for(int i = 0; i < *text_length; i++)
            puts(text[i]);
            break;
        case 1:
            first_func(text, *text_length);
            break;
        case 2:
            second_func(text, *text_length);
            break;
        case 3:
            third_func(text, text_length);
            break;
        case 4:
            fourth_func(text, *text_length);
            break;
        case 9:
            nineth_func(text, *text_length);
            break;
        default:
            puts(ERROR_MSG);
    }
        
}

void zero_func_info()
{
    puts(ZERO_FUNC);
}

void first_func_info()
{
    puts(FIRST_FUNC);
}

void second_func_info()
{
    puts(SECOND_FUNC);
}

void third_func_info()
{
    puts(THIRD_FUNC);
}

void fourth_func_info()
{
    puts(FOURTH_FUNC);
}

int main()
{
    puts(FIRST_MESSAGE);
    int key;
    key_input(&key);
    if(key == 5)
    {
        zero_func_info();
        first_func_info();
        second_func_info();
        third_func_info();
        fourth_func_info();
        return 0;
    }
    int text_length = 0;
    char** text = text_input(&text_length);
    if(text[text_length-1][strlen(text[text_length-1])-1]!=DOT)
    {
        puts(ERROR_DOT_MSG);
    }
    else
    {
        removing_repetitions(text, &text_length);
        switch_func(text, &text_length, key);
        if((key>1 && key<5) || key==9)
        switch_func(text, &text_length, 0);
    }
    return 0;
}