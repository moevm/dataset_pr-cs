#include <stdio.h>
#include "getcommand.h"
#include "readtext.h"
#include "preprocessing.h"
#include "printtext.h"
#include "freetext.h"
#include "bananapplesearch.h"
#include "convertnumsandalpha.h"
#include "siftedoutput.h"
#include "sorttextnums.h"
#include "printduplicates.h"


void printhelp(){
    puts(
        "Help about the functions that the program implements:\n"
        "0 - primary mandatory processing (deleting duplicate sentences without taking into account case)\n"
        "1 - all sentences containing the words \033[33mbanana\033[0m or \033[32mapple\033[0m\n"
        "2 - converting all letters to lowercase and replacing all numbers with the letter 'D'\n"
        "3 - deleting all sentences with a length greater than 15\n"
        "4 - sorting sentences in ascending order of the products of all numbers in them"
    );
}


int main(){
    printf("Course work for option 4.12, created by Nikita Kozmin\n");
    char **sentences;
    size_t cnt_sentences;
    int N;
    switch (getcommand()){
    case 0:
        cnt_sentences = readtext(&sentences);
        if (!sentences) return 0;
        preprocessing(&sentences, &cnt_sentences);
        printtext(&sentences, &cnt_sentences);
        freetext(&sentences, &cnt_sentences);
        return 0;
    case 1:
        cnt_sentences = readtext(&sentences);
        if (!sentences) return 0;
        preprocessing(&sentences, &cnt_sentences);
        bananapplesearch(&sentences, &cnt_sentences);
        freetext(&sentences, &cnt_sentences);
        return 0;
    case 2:
        cnt_sentences = readtext(&sentences);
        if (!sentences) return 0;
        preprocessing(&sentences, &cnt_sentences);
        convertnumsandalpha(&sentences, &cnt_sentences);
        printtext(&sentences, &cnt_sentences);
        freetext(&sentences, &cnt_sentences);
        return 0;
    case 3:
        cnt_sentences = readtext(&sentences);
        if (!sentences) return 0;
        preprocessing(&sentences, &cnt_sentences);
        siftedoutput(&sentences, &cnt_sentences);
        freetext(&sentences, &cnt_sentences);
        return 0;
    case 4:
        cnt_sentences = readtext(&sentences);
        if (!sentences) return 0;
        preprocessing(&sentences, &cnt_sentences);
        sorttextnums(&sentences, &cnt_sentences);
        printtext(&sentences, &cnt_sentences);
        freetext(&sentences, &cnt_sentences);
        return 0;
    case 5:
        printhelp();
        return 0;
    case 9:
        scanf("%d\n", &N);
        cnt_sentences = readtext(&sentences);
        if (!sentences) return 0;
        printduplicates(&sentences, &cnt_sentences, &N);
        return 0;
    default:
        printf("Error: Unexpected command\n");
        return 0;
    }
    return 0;
}
