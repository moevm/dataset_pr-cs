#include"../include/Output.h"

//метод вывода текста
void Output(Text *text) {
    for (int i = 0; i < text->size; i++) {
        wprintf(L"%ls\n", text->sentences[i].sentence);
    }
}
