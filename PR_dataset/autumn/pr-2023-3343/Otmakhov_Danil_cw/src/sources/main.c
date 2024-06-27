#include "../include/main.h"

int main(){
    printInfoMessage();
    int command = getCommand();
    switch(command)
    {
    case 0:
        initialMandarotyProcessing();
        break;
    case 1:
        outputOnlyDigitsSentences();
        break;
    case 2:
        sortSentencesByTheNumberOfUppercaseLettersInIt();
        break;
    case 3:
        deleteSentenceWithTheInputtedWord();
        break;
    case 4:
        replaceDigitsInSentences();
        break;
    case 5:
        printHelp();
        break;
    case 9:
        repeatSentences();
        break;
    default:
        puts("Error:  incorrect command input\n");
        break;
    }
    return 0;
}
