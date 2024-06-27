#include "my_lib.h"

int main()
{
    setlocale(LC_ALL,"");
    wprintf(L"Course work for option 5.16, created by Nikita Skobelev.\n");
    int command;
    wscanf(L"%d",&command);
    struct Text text;
    ch first[1000];
    switch(command){
    case 0:
        text = input_text();
        for(int i=0;i<text.cnt_sen;++i){
        wprintf(L"%S\n",text.txt[i].snt);
        }
        memory_cleaning(&text);
        break;
    case 1:
        text = input_text();
        replace_0_9(&text);
        memory_cleaning(&text);
        break;
    case 2:
        text = input_text();
        find_(&text);
        memory_cleaning(&text);
        break;
    case 3:
        text = input_text();
        sort_low_cnt_wrd(&text);
        memory_cleaning(&text);
        break;
    case 4:
        text = input_text();
        del(&text);
        memory_cleaning(&text);
        break;
    case 5:
        wprintf(L"command 0: accepts text, deletes repeated sentences and prints the processed text\ncommand 1: accepts text, changes all words in the text ending in a digit character (0-9) so that they end with the name of the Cyrillic digit, prints the processed text\ncommand 2: accepts the text, prints the sentences in the open there is the last word of the previous sentence, highlighting them in red\n Command 3: accepts the text, sorts the sentences to reduce the number of words, prints the processed text.\nCommand 4: accepts text, deletes sentences with less than 3 words, prints the processed text\nCommand 5: outputs help.");
        break;
    case 9:
        getwchar();
        fgetws(first,1000,stdin);
        text = input_text();
        find_no_reg(&text,first);
        memory_cleaning(&text);
        break;
    default:
        error(1);
        //wprintf(L"GG");
    }
    return 0;
}
