#include <locale.h>
#include <stdlib.h>

#include "delete_repeatChar.h"
#include "cmp.h"
#include "fill_and_firstprocc_structure.h"
#include "print_colourwords.h"
#include "switch_first_word.h"
#include "print_options.h"
#include "print_structure.h"
#include "switchwords.h"

int main(void)
{
    setlocale(LC_ALL, "");
    wprintf(L"%s", "Course work for option 5.4, created by Demid Somak.\n");
    unsigned cmdnum;
    wscanf(L"%d", &cmdnum);
    wchar ch = getwchar();
    Text *text = malloc(sizeof(Text));
    wchar *word = malloc(sizeof(wchar)*25);

    switch (cmdnum)
    {
    case 0:
        fill_and_firstprocc_struct(text);
        print_structure(text);
        break;
    case 1:
        fill_and_firstprocc_struct(text);
        switch_first_word(text);
        print_structure(text);
        break;
    case 2:
        fill_and_firstprocc_struct(text);
        qsort(text->arrofsents, text->countsents, sizeof(Sentence *), cmp);
        print_structure(text);
        break;
    case 3:
        fill_and_firstprocc_struct(text);
        print_colourwords(text);
        break;
    case 4:
        fill_and_firstprocc_struct(text);
        delete_repeatChar(text);
        print_structure(text);
        break;
    case 5:
        print_options();
        break;
    case 9:
        fgetws(word,25,stdin);
        fill_and_firstprocc_struct(text);
        switchwords(text,word);
        print_structure(text);
        break;
    default:
        wprintf(L"Error: Несуществующий номер команды, введите 5 для отображения функционала программы\n");
    };
    return 0;
}
