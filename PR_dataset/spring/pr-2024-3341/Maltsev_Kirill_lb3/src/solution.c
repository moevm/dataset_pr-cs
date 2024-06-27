#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

#define NULL_CH              '\0'
#define ENDL                 "\n"
#define NULL_CH_BUFFER_SIZE  1
#define MATCH_GROUPS_SIZE    1

const char* kOutputFileName = "result.txt";
const char* kPatternAdd = "^[a-zA-Z0-9/]*add$";
const char* kPatternMul = "^[a-zA-Z0-9/]*mul$";


void throwIndexError();

typedef struct VectorNum
{
    /** Vector implementation
     * A standard container which offers access to
     * individual elements in any order.
    */
    long long* array;
    int capacity;
    int size;
} VectorNum;

/* Vector methods */
VectorNum* vectorNumInit();
void vectorNumDelete(VectorNum* vector_num);
long long vectorNumAt(VectorNum* vector_num, int index);
void vectorNumPushBack(VectorNum* vector_num, long long new_element);
void printVector(VectorNum* vector_num);

typedef struct String
{
    /** String implementation
     * Managing sequences of characters.
    */
    char* array;
    int capacity;
    int size;
} String;

/* String methods */
String* stringInit();
void stringDelete(String* string);
char stringAt(String* string, int index);
void stringPushBack(String* string, char new_element);
void stringPrint(String* string);

long long getResult();
void outputDataToFile(const char* file_path, long long result);
long long fileTreeTraversal(char* dir_path, int type, char operation,
                            regex_t* regex_compiled_add_ptr, regex_t* regex_compiled_mul_ptr);
int dirPathValidation(char* dir_path, regex_t* regex_compiled);
int isConsidered(char* dir_name);
char* getSubPath(char* dir_path, char* sub_file_name);
String* getDataFromFile(char* file_path);
VectorNum* processData(String* string);
long long vectorNumSum(VectorNum* vector_num);
long long vectorNumProduct(VectorNum* vector_num);


int main()
{
    long long result = getResult();
    outputDataToFile(kOutputFileName, result);
    return 0;
}

void throwIndexError()
{
    printf("Index out of range%s", ENDL);
}

long long getResult()
{

    regex_t regex_compiled_add;
	regcomp(&regex_compiled_add, kPatternAdd, REG_EXTENDED);

    regex_t regex_compiled_mul;
	regcomp(&regex_compiled_mul, kPatternMul, REG_EXTENDED);
    
    DIR* dir;
    if ( dir = opendir("tmp/add") ) {
        return fileTreeTraversal("tmp/add", DT_DIR, '+', &regex_compiled_add, &regex_compiled_mul);
    }

    if ( dir = opendir("tmp/mul") ) {
        return fileTreeTraversal("tmp/mul", DT_DIR, '-', &regex_compiled_add, &regex_compiled_mul);
    }

    return 0;
}

void outputDataToFile(const char* file_path, long long result)
{
    FILE* fout = fopen(file_path, "w");
    fprintf(fout, "%lld", result);
    fclose(fout);
}

long long fileTreeTraversal(char* dir_path, int type, char operation,
                            regex_t* regex_compiled_add_ptr, regex_t* regex_compiled_mul_ptr)
{
    if (type == DT_DIR) {
        DIR* dir = opendir(dir_path);

        if (dirPathValidation(dir_path, regex_compiled_add_ptr)) {
            long long sum = 0;
            struct dirent* de = readdir(dir);
            while (de) {
                char* sub_path = getSubPath(dir_path, de->d_name);
                if (isConsidered(de->d_name)) {
                    sum += fileTreeTraversal(sub_path, de->d_type, '+', regex_compiled_add_ptr, regex_compiled_mul_ptr);
                }
                de = readdir(dir);
            }
            closedir(dir);
            return sum;
        }

        if (dirPathValidation(dir_path, regex_compiled_mul_ptr)) {
            long long product = 1;
            struct dirent* de = readdir(dir);
            while (de) {
                char* sub_path = getSubPath(dir_path, de->d_name);
                if (isConsidered(de->d_name)) {
                    product *= fileTreeTraversal(sub_path, de->d_type, '*', regex_compiled_add_ptr, regex_compiled_mul_ptr);
                }
                de = readdir(dir);
            }
            closedir(dir);
            return product;
        }

    }
    if (type == DT_REG) {
        VectorNum* numbers = processData(getDataFromFile(dir_path));
        if (operation == '+') {
            return vectorNumSum(numbers);
        }
        if (operation == '*') {
            return vectorNumProduct(numbers);
        }
    }
    return 0;
}

int dirPathValidation(char* dir_path, regex_t* regex_compiled_ptr)
{
	regmatch_t match_groups[MATCH_GROUPS_SIZE];
	return (regexec(regex_compiled_ptr, dir_path, MATCH_GROUPS_SIZE, match_groups, 0) == 0);
}

int isConsidered(char* dir_name)
{
    return (strcmp(dir_name, ".") != 0 && strcmp(dir_name, "..") != 0);
}

char* getSubPath(char* dir_path, char* sub_file_name)
{
    char* sub_path = (char*) calloc(strlen(dir_path) + strlen(sub_file_name) + 2 * NULL_CH_BUFFER_SIZE, sizeof(char));
    strcpy(sub_path, dir_path);
    sub_path[strlen(dir_path)] = '/';
    strcat(sub_path, sub_file_name);
    return sub_path;
}

String* getDataFromFile(char* file_path)
{
    FILE* fin = fopen(file_path, "r");
    String* line = stringInit();

    signed char ch = 0;
    while ((ch = fgetc(fin)) != EOF) {
        stringPushBack(line, ch);
    }
    
    if (strchr(line->array, '\n')) {
        *strchr(line->array, '\n') = NULL_CH;
    }
    
    fclose(fin);

    return line;
}

VectorNum* processData(String* string)
{
    VectorNum* processed_data = vectorNumInit();
    char* sep = " ";
    char* token;

    token = strtok(string->array, sep);
    while (token) {
        vectorNumPushBack(processed_data, atoll(token));
        token = strtok(NULL, sep);
    }

    stringDelete(string);
    return processed_data;
}

long long vectorNumSum(VectorNum* vector_num)
{
    long long sum = 0;
    for (int i = 0; i < vector_num->size; i++) {
        sum += vectorNumAt(vector_num, i);
    }
    vectorNumDelete(vector_num);
    return sum;
}

long long vectorNumProduct(VectorNum* vector_num)
{
    if (vector_num->size == 0) {
        return 0;
    }
    long long product = 1;
    for (int i = 0; i < vector_num->size; i++) {
        product *= vectorNumAt(vector_num, i);
    }
    vectorNumDelete(vector_num);
    return product;
}




VectorNum* vectorNumInit()
{
    return (VectorNum*) calloc(1, sizeof(VectorNum));
}

void vectorNumDelete(VectorNum* vector_num)
{
    free(vector_num->array);
    free(vector_num);
}

long long vectorNumAt(VectorNum* vector_num, int index)
{
    if (index >= 0 && index < vector_num->size) {
        return vector_num->array[index];
    }
    throwIndexError();
    return 0;
}

void vectorNumPushBack(VectorNum* vector_num, long long new_element)
{
    if (vector_num->size + 1 > vector_num->capacity) {
        if (vector_num->size == 0) {
            vector_num->capacity = 2;
        } else {
            vector_num->capacity = vector_num->capacity * vector_num->capacity;
        }
        vector_num->array = realloc(vector_num->array, vector_num->capacity * sizeof(long long));
    }
    vector_num->array[vector_num->size++] = new_element;
}

void printVector(VectorNum* vector_num)
{
    for (int i = 0; i < vector_num->size; i++) {
        printf("%lld ", vectorNumAt(vector_num, i));
    }
    printf(ENDL);
}




String* stringInit()
{
    return (String*) calloc(1, sizeof(String));
}

void stringDelete(String* string)
{
    free(string->array);
    free(string);
}

char stringAt(String* string, int index)
{
    if (index >= 0 && index < string->size) {
        return string->array[index];
    }
    throwIndexError();
    return -1;
}

void stringPushBack(String* string, char new_element)
{
    if (string->size + 1 + NULL_CH_BUFFER_SIZE > string->capacity) {
        if (string->size == 0) {
            string->capacity = 2;
        } else {
            string->capacity = string->capacity * string->capacity;
        }
        string->array = realloc(string->array, string->capacity * sizeof(char));
    }
    string->array[string->size++] = new_element;
    string->array[string->size] = NULL_CH;
}

void stringPrint(String* string)
{
    printf("%s", string->array);
}
