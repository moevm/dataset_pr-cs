#include "output.h"

void output_course_work_option()
{
    wprintf(L"%ls\n", L"Course work for option 5.12, created by Alisa Yakovleva.");
}

void output_text(struct Text text)
{
    for(int i = 0; i < text.number_sentences; i++)
        wprintf(L"%ls\n", text.sents[i]->str);
}
