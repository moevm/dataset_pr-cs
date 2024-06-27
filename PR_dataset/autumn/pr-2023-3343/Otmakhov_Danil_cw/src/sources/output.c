#include "../include/output.h"

void printInfoMessage(){
    puts("Course work for option 4.3, created by Danil Otmakhov.");
}

void printText(Text text){
    for(size_t i = 0; i < text.size; i++){
        printf("%s\n", text.sentences[i].chars);
    }
}

void printHelp(){
    puts("0 - Text output after initial mandatory processing\n"
        "1 - Print all sentences in which all words consist only of numbers.\n"
        "2 - Sort sentences by reducing the number of uppercase letters in them.\n"
        "3 - Delete all sentences in which a certain word (which the user enters into your program after selecting this action) occurs 2 or more times.\n"
        "4 - Transform all sentences so that each occurrence of a digit is replaced by the corresponding substring (0 - “Zero”, 1 - “One”, 2 - “Two”, etc.).\n"
        "5 - View information about the functions that the program implements.");
}
