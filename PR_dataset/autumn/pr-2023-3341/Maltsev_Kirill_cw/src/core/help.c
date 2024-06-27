#include <wchar.h>

void help() {
    wprintf(L"The program implements the following functions:\n");
    wprintf(L"-) (removeDuplicates): text preprocessing.\n");
    wprintf(L"0) (printText): text output after preprocessing.\n");
    wprintf(L"1) (countWords): print out each word (case-sensitive) and the number of its repetitions in the text.\n");
    wprintf(L"2) (replaceNonAlphaWithCode): replace each character that is not a letter with its code.\n");
    wprintf(L"3) (sortByLatinSymbols): sort sentences by the number of Latin letters in the sentence.\n");
    wprintf(L"4) (removeUpperAndSpecialSymbolsCase): delete all sentences that contain special characters and do not contain capital letters. Special characters include: #$^%c@\n", '%');
    wprintf(L"5) (help): output help about the functions that the program implements.\n");
}