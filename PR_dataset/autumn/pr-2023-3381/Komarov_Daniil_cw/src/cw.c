// ------------------------------------------------------------------
// Course work for option 4.12, created by Daniil Komarov.
// GitHub: https://github.com/qmaster0803
// Written during coursework in SPbSETU, 2023
// ------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define CRESET "\e[0m"

#define MEMALLOC_ERR {puts("Error: unable to allocate memory!"); exit(1);}

//this structure used for storing indexes of found words
//for detailed description see task1() comments
struct foundWord {int index; char type;};

//this structure used for storing sentences along with product of all digits in them in task4
//using really huge type for storing product because even unsigned long long can store only 9^20, so it's not really that big
struct sentenceWithProduct {char* sentence; unsigned long long product;};

//this structure used for storing words along with their sum of all digits in them in task9
struct wordWithSum {int start_index; int len; int sum;};

// ------------------------------------------------------------------
// STRING FUNCTIONS
// ------------------------------------------------------------------

//Non-case sensitive comparison of two strings. Returns 1 if strings are equal, else 0;
//This function already exists in POSIX strings.h, but strcasecmp is not in c standart;
//So, writing this to add compability with non-POSIX OS.
int strcmp_ncs(const char* str1, const char* str2)
{
        int str1_len = strlen(str1);
        int str2_len = strlen(str2);
        if(str1_len != str2_len) {return 0;}

        for(int i = 0; i < str1_len; i++) {
                if(tolower(str1[i]) != tolower(str2[i])) {return 0;}
        }
        return 1;
}

//This function returns count of word in string, also indices of found words are written to integer array 'indices'
//Word is alphanumeric sequence, with spaces or commas on both sides of it
//Search is non-case sensitive
int findWord(const char* str, const char* word, int** indices)
{
        int count = 0;
        int str_len = strlen(str);
        int word_len = strlen(word);
        char* buf = (char*)malloc(strlen(str)+1);
        if(!buf) MEMALLOC_ERR
        *indices = (int*)malloc(sizeof(int));
        if(!(*indices)) MEMALLOC_ERR
        char* buf_ptr = buf;

        for(int i = 0; i < str_len; i++) {
                buf[i] = tolower(str[i]);
        }
        buf[str_len] = '\0';

        while(buf_ptr = strstr(buf_ptr, word)) {
                char prev = (buf_ptr == buf) ? 0 : *(buf_ptr-1); //ternary here to prevent accessing memory for '-1' element of array
                char next = *(buf_ptr+word_len);
                //check if this occurrence is a word (surrounded by 'good' delimiters)
                if((buf_ptr == buf || prev == ',' || prev == ' ') && (next == ',' || next == ' ' || next == '.')) {
                        count++;
                        int index = buf_ptr-buf;
                        *indices = (int*)realloc(*indices, sizeof(int)*count);
                        if(!(*indices)) MEMALLOC_ERR
                        (*indices)[count-1] = index;
                }
                buf_ptr++;
        }
        free(buf);
        return count;
}

// ------------------------------------------------------------------
// INPUT FUNCTIONS
// ------------------------------------------------------------------

//return length of sentence if ok
//return -1 if double-'\n' occurs and nothing more to read
//return length of sentence with negative sign if double-'\n' occurs and last sentence was not finished correctly
int read_sentence(char** sentence)
{
        char* result = (char*) malloc(50);
        if(!result) MEMALLOC_ERR
        int allocated_memory_size = 50;
        int result_len = 0;
        int broken = 0; //this flag inverts sign of output. Used to determine unterminated sentences
        char c = '\0';
        do {
                c = getchar();
                result[result_len] = c;
                if(result_len >= 1 && result[result_len-1] == '\n' && c == '\n') {
                        if(result_len >= 3) { //sentence is not empty, so add full stop sign and process like normal, but return negative value
                                result[result_len-1] = '.';
                                broken = 1;
                                break;
                        }
                        free(result);
                        return -1; //sentence is empty, return -1
                }
                result_len++;
                if(result_len == allocated_memory_size-1) {
                        char* new_ptr = (char*)realloc(result, allocated_memory_size+50);
                        if(new_ptr) {
                                result = new_ptr;
                                allocated_memory_size += 50;
                        }
                        else MEMALLOC_ERR
                }
        } while(c != '.');

        //remove all newline chars from sentence and copy others
        //memcpy can be used here, but to prevent exceess load, coping, removing '\n' chars, spaces and tabs in the beginning and the ending are done in one loop
        *sentence = (char*)malloc(result_len+1); //allocate memory for "full" string
        if(!sentence) MEMALLOC_ERR
        int sentence_len = 0;
        for(int i = 0; i < result_len; i++)
        {
                if(result[i] == '\n' || result[i] == ' ' || result[i] == '\t') {
                        //newline/space/tab at the begin/end of the string - remove
                        //newline/space/tab at the middle of the string - add space to result
                        if(sentence_len != 0 && i != (result_len-1)) {
                                if(result[i] == ' ') {(*sentence)[sentence_len++] = ' ';}
                                else                 {(*sentence)[sentence_len++] = '\t';}
                        }
                }
                else { //"normal" char - add
                        (*sentence)[sentence_len++] = result[i];
                }
        }
        (*sentence)[sentence_len] = '\0';
        free(result);
        return ((broken) ? -1*result_len : result_len);
}

//return number of sentences
int read_text(char*** text_ptr)
{
        (*text_ptr) = (char**)malloc(sizeof(char*));
        if(!(*text_ptr)) MEMALLOC_ERR
        int sentence_count = 0;
        int stop_next_time = 0;
        while(!stop_next_time) {
                char* sentence;
                int l = read_sentence(&sentence);
                (*text_ptr) = (char**)realloc(*text_ptr, sizeof(char*)*(sentence_count+1));
                if(!(*text_ptr)) MEMALLOC_ERR
                if(l < 0) { //exit condition
                        if(l == -1) {break;} //exit if reached text end normally
                        else{ //exit reached, but last sentence was not terminated properly. Exit on next iteration
                                stop_next_time = 1;
                                l = -1*l;
                        }
                }

                //compare sentence to others, skip if already exists
                int skip = 0;
                for(int i = 0; i < sentence_count; i++) {
                        if(strcmp_ncs((*text_ptr)[i], sentence)) {
                                skip = 1;
                                break;
                        }
                }
                if(!skip) {(*text_ptr)[sentence_count++] = sentence;}
                else {free(sentence);}
        }
        return sentence_count;
}

// ------------------------------------------------------------------
// COMPARATORS FOR QSORT
// ------------------------------------------------------------------

int compareWordIndices(const void* a, const void* b)
{
        struct foundWord arg1 = *(const struct foundWord*)a;
        struct foundWord arg2 = *(const struct foundWord*)b;

        if(arg1.index < arg2.index) return -1;
        if(arg1.index > arg2.index) return 1;
        return 0;
}

//compare by product, if products are same, compare by alphabetic order
int compareSentenceProducts(const void* a, const void* b)
{
        struct sentenceWithProduct arg1 = *(const struct sentenceWithProduct*)a;
        struct sentenceWithProduct arg2 = *(const struct sentenceWithProduct*)b;
        if(arg1.product < arg2.product) return -1;
        if(arg1.product > arg2.product) return 1;

        if(strcmp(arg1.sentence, arg2.sentence) < 0) return -1;
        else                                         return 1;
}

//compare by sum, if sums are equal - by start_index
int compareWordSums(const void* a, const void* b)
{
        struct wordWithSum arg1 = *(const struct wordWithSum*)a;
        struct wordWithSum arg2 = *(const struct wordWithSum*)b;

        if(arg1.sum < arg2.sum) return -1;
        if(arg1.sum > arg2.sum) return 1;

        if(arg1.start_index < arg2.start_index) return -1;
        else                                    return 1;
}

// ------------------------------------------------------------------
// TASKS
// ------------------------------------------------------------------

void show_help() {
        puts("This program is a text processor.");
        puts("First, you need to select mode from range 0-5, where:");
        puts("0 - print preprocessed text;");
        puts("1 - print all sentences containing word 'banana' or 'apple',");
        puts("    'banana' should be colored in yellow, 'apple' - in green;");
        puts("2 - print text, replacing all letters with lower case ones and all digits with 'D';");
        puts("3 - print text, removing all sentences longer than 15;");
        puts("4 - print text, sorting sentences in it by product of all numbers in sentence;");
        puts("5 - show this help.");
}


void task1(char** text, int sentence_count)
{
        //algorithm:
        //1 - using function findWord(), find all occurrences of words 'banana' and 'apple' in sentence
        //2 - convert arrays of ints returned by findWord() to array of structs foundWord, where type = 0 represents 'apple' and type = 1 states for 'banana'
        //3 - sort this array using qsort and compareWordIndices() comparator, now array is sorted by indices of occurrences in ascending order
        //4 - using this array, output colored string
        for(int s = 0; s < sentence_count; s++) {
                char* sentence = text[s];
                int sentence_len = strlen(sentence);
                int* indicesBanana;
                int* indicesApple;
                int count_banana = findWord(sentence, "banana", &indicesBanana);
                int count_apple  = findWord(sentence, "apple",  &indicesApple);
                int total_count = count_apple + count_banana;

                if(total_count > 0) {
                        struct foundWord* found_words_arr = (struct foundWord*)malloc(sizeof(struct foundWord)*total_count);
                        for(int i = 0; i < count_apple; i++) {
                                struct foundWord word = {indicesApple[i], 0};
                                found_words_arr[i] = word;
                        }
                        for(int i = 0; i < count_banana; i++) {
                                struct foundWord word = {indicesBanana[i], 1};
                                found_words_arr[count_apple+i] = word;
                        }
                        qsort(found_words_arr, total_count, sizeof(struct foundWord), compareWordIndices);

                        //print beginning of sentence if exists
                        if(found_words_arr[0].index != 0) {
                                fwrite(sentence, 1, found_words_arr[0].index, stdout);
                        }
                        for(int i = 0; i < total_count; i++) {
                                //print ANSI color code
                                fputs((found_words_arr[i].type) ? YEL : GRN, stdout);
                                //print word
                                fwrite(sentence+found_words_arr[i].index, 1, (found_words_arr[i].type) ? 6 : 5, stdout);
                                //print color reset code
                                fputs(CRESET, stdout);
                                //print part of sentence between colored word or between word and the end
                                int print_count;
                                int end_of_colored_index = found_words_arr[i].index + ((found_words_arr[i].type) ? 6 : 5);
                                if(i == (total_count-1)) {print_count = sentence_len - end_of_colored_index;}
                                else                     {print_count = found_words_arr[i+1].index - end_of_colored_index;}
                                fwrite(sentence+end_of_colored_index, 1, print_count, stdout);
                        }
                        putchar('\n');
                }
                free(indicesBanana);
                free(indicesApple);
        }
}

void task2(char** text, int sentence_count)
{
        for(int s = 0; s < sentence_count; s++) {
                char* sentence = text[s];
                int sentence_len = strlen(sentence);
                for(int i = 0; i < sentence_len; i++) {
                        if(isdigit(sentence[i])) {putchar('D');}
                        else                     {putchar(tolower(sentence[i]));}
                }
                putchar('\n');
        }
}

void task3(char** text, int sentence_count)
{
        for(int s = 0; s < sentence_count; s++) {
                char* sentence = text[s];
                int sentence_len = strlen(sentence);
                if(sentence_len <= 15) {puts(sentence);}
        }
}

void task4(char** text, int sentence_count)
{
        struct sentenceWithProduct* sentences = (struct sentenceWithProduct*)malloc(sizeof(struct sentenceWithProduct)*sentence_count);
        if(!sentences) MEMALLOC_ERR
        for(int s = 0; s < sentence_count; s++) {
                char* sentence = text[s];
                int sentence_len = strlen(sentence);

                //initializing structure
                struct sentenceWithProduct sentence_struct;
                sentence_struct.sentence = (char*)malloc(sentence_len+1);
                if(!sentence_struct.sentence) MEMALLOC_ERR
                memcpy(sentence_struct.sentence, sentence, sentence_len+1);
                sentence_struct.product = 1;

                //count product of all digits in sentence
                int foundDigit = 0;
                for(int i = 0; i < sentence_len; i++) {
                        if(isdigit(sentence[i])) {
                                int digit = (int)(sentence[i] - '0');
                                foundDigit = 1;
                                //to prevent overflow...
                                unsigned long long p = sentence_struct.product * digit;
                                if(p != 0 && p/digit != sentence_struct.product) {
                                        puts("Error: variable overflow - unable to calculate product of all digits in sentence.");
                                        exit(1);
                                }
                                sentence_struct.product = p;
                        }
                }
                if(!foundDigit) {sentence_struct.product = 0;} //product is 0 when there are no digits in sentence
                sentences[s] = sentence_struct;
        }
        qsort(sentences, sentence_count, sizeof(struct sentenceWithProduct), compareSentenceProducts);
        for(int s = 0; s < sentence_count; s++) {
                puts(sentences[s].sentence);
                free(sentences[s].sentence);
        }
        free(sentences);
}

void task9(char** text, int sentence_count)
{
        struct wordWithSum* summed;
        for(int s = 0; s < sentence_count; s++) {
                char* sentence = text[s];
                int sentence_len = strlen(sentence);

                summed = (struct wordWithSum*)malloc(sizeof(struct wordWithSum));
                int summed_len = 0;
                struct wordWithSum w = {0, 0, 0};

                int output_sentence_len = 0;
                for(int i = 0; i < sentence_len; i++) {
                        if(sentence[i] != ' ' && sentence[i] != ',' && sentence[i] != '.') { //regular word char
                                w.len++;
                                if(isdigit(sentence[i])) {w.sum += (int)(sentence[i] - '0');}
                        }
                        else if(w.len > 0) { //reached word end
                                struct wordWithSum* new_summed = (struct wordWithSum*)realloc(summed, sizeof(struct wordWithSum)*(summed_len+1));
                                if(!new_summed) MEMALLOC_ERR;
                                summed = new_summed;
                                summed[summed_len] = w;
                                summed_len++;

                                output_sentence_len += w.len+1; //word len + space
                                w.start_index = i+1;
                                w.len = 0;
                                w.sum = 0;
                        }
                        else w.start_index = i+1;
                }
                
                //sort words by sum
                qsort(summed, summed_len, sizeof(struct wordWithSum), compareWordSums);
                //allocate memory for new sentence
                char* new_sentence = (char*)malloc(output_sentence_len+1);
                int new_sentence_len = 0;
                for(int i = 0; i < summed_len; i++) {
                        memcpy(new_sentence+new_sentence_len, sentence+(summed[i].start_index), summed[i].len);
                        new_sentence_len += summed[i].len;
                        new_sentence[new_sentence_len++] = ' ';
                }
                new_sentence[output_sentence_len-1] = '.';
                new_sentence[output_sentence_len] = '\0';
                puts(new_sentence);
                
                free(new_sentence);
                free(summed);
        }
}

// ------------------------------------------------------------------
// MAIN SECTION
// ------------------------------------------------------------------

int main() {
        puts("Course work for option 4.12, created by Daniil Komarov.");

        /* modes:
           0 - show preprocessed text
           1 - function 1
           2 - function 2
           3 - function 3
           4 - function 4
           5 - show help
        */
        int mode;
        int success = scanf("%d", &mode);
        if(!success || mode < 0 || (mode > 5 && mode != 9)) {
                puts("Error: wrong mode value.");
                return 1;
        }

        char** text;
        int sentence_count;
        if(mode != 5) {sentence_count = read_text(&text);}

        switch(mode) {
                case 0:
                        for(int i = 0; i < sentence_count; i++) {
                                puts(text[i]);
                        }
                        break;
                case 1:
                        task1(text, sentence_count);
                        break;
                case 2:
                        task2(text, sentence_count);
                        break;
                case 3:
                        task3(text, sentence_count);
                        break;
                case 4:
                        task4(text, sentence_count);
                        break;
                case 5:
                        show_help();
                        break;
                case 9:
                        task9(text, sentence_count);
                        break;
        }
        if(mode != 5) {
                for(int i = 0; i < sentence_count; i++) {free(text[i]);}
                free(text);
        }
        return 0;
}
