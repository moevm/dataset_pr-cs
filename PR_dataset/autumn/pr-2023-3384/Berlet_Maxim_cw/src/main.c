#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "printN.h"
#include "mclean.h"
#include "inputfuncs.h"

void command_print_help(){
    puts(
        "List of commands:\n"
        "  0 - Print preprocessed text.\n"
        "  1 - Print each sentence, and if it contains the phrase “define BLUE”, then print all the words after this phrase in blue.\n"
        "  2 - In the entire text, replace the sequence of consecutive letters without taking into account case with a substring of the form “<number of consecutive letters><letter in upper case>”. For example, the sequence “AaaA” should be replaced with the string “4A”.\n"
        "  3 - Delete all sentences in which the number of words is a multiple of three.\n"
        "  4 - Sort sentences by decreasing the total length of the first and last word. If there is one word in a sentence, then you need to take the length of this word.\n"
        "  5 - Print help message.\n"
        "\n"
        "The text consists of sentences separated by a period. Sentences are a set of words separated by a space or comma, words are a set of Latin letters and numbers. Double \'\\n\' is interpreted as an end of text. Any violation from these simple rules will be considered an invalid input."
    );
}

char* resstr(char* sentence, int n){
    int len = strlen(sentence);
    char* res = (char*)malloc(sizeof(char)*(len+n+2)*n);
    char* temp = strdup(sentence);
    temp[len-1] = '\0';
    for(int i = 0; i < n; i++){
        if(i != n-1){
            strcat(res, temp);
            strcat(res, " ");
        }
        else{
            strcat(res, temp);
            strcat(res, ".");
            strcat(res, "\0");
        }
    }
    return res;
}



int main(){
    printf("Course work for option 4.16, created by Maxim Berlet.\n");
    int choose_option;
    int res = scanf("%d", &choose_option);
    if(res == 0){
        printf("Error: <Invalid input. Not an integer.>");
        exit(1);
    }
    if(choose_option < 0 || choose_option > 5 && choose_option != 9){
        printf("Error: <Invalid input. Out of range.>");
        exit(1);
    }
    if(choose_option == 5){
        command_print_help();
        return 0;
    }
    
    int counter = 0;
    //freopen("test.txt", "r", stdin);
    int n0;
    scanf("%d", &n0);
    char** strs = strs_input(&counter);
    strs_preprocessing(strs, &counter);
    switch(choose_option)
    {
        case 0:{
            print0(strs, counter);
            clean_memory(strs, counter);
            break;
        }
        case 1:
            colors(strs, &counter);
            clean_memory(strs, counter);
            break;
    
        case 2:
            print2(strs, counter);
            clean_memory(strs, counter);
            break;

        case 3:
            print3(strs, counter);
            break;

        case 4:
            print4(strs, counter);
            clean_memory(strs, counter);
            break;

        case 9:
            //printf("%d\n", counter);
            for(int j = 0; j < counter; j++){
                char* r = resstr(strs[j], n0);
                printf("%s\n", r);
            }
            break;
    }
    return 0;
}
