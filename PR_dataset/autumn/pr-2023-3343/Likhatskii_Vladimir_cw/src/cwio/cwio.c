#include "cwio.h"

void print_program_info() {
    wprintf(L"Course work for option %ls, created by %ls.\n", CW_OPTION, CW_AUTHOR);
}

void print_program_help() {
    wprintf(L"[1]: Заменить в тексте все подстроки \"high noon\" на \"полдень\" и \"полночь\" на \"midnight\". \n");
    wprintf(L"[2]: Найти и вывести все даты в тексте заданные в виде \"DD/MM/YYYY\" или \"YYYY-MM-DD\" в \n");
    wprintf(L"     порядке возрастания этих дат. \n");
    wprintf(L"[3]: Удалить все предложения, которые начинаются и заканчиваются на одно и то же слово. \n");
    wprintf(L"[4]: Для всех вхождений дат в тексте вида \"<day> <month> <year>, вывести эти даты в виде \n");
    wprintf(L"     \"DD.MM.YYYY\" и строку \"Happened\" если эта дата была до текущей и \"Not Happened\" в \n");
    wprintf(L"     противном случае. Например, для даты \"03 Jan 1666\" вывести \"03.01.1666	Happened\". \n");
    wprintf(L"[5]: Показать справку \n");
}

int get_cmd() {
    wint_t cmd = L'6';
    while(!wcschr(ALLOWED_COMMANDS, cmd)) {
         cmd = getwchar();

         if(!wcschr(ALLOWED_COMMANDS, cmd)) {
            return -1;
         }
    }

    return (int)(cmd - L'0');
}

wchar_t * read_stdin() {
    int length = 0;
    long size = CHUNK_SIZE;
    wchar_t *text = malloc(size);
    wint_t c;

    while(!endswith(TEXT_END, text)) {
        c = getwchar();

        if((length + 1) * sizeof(wchar_t) > size) {
            size += CHUNK_SIZE;
            text = realloc(text, size);
        }

        text[length++] = c;
    }

    text = realloc(text, (length + 1) * sizeof(wchar_t));
    text[length - wcslen(TEXT_END)] = L'\0';

    return text;
}

void print_text(Text *text) {
    for(int i = 0; i < text->length; i++) {
        wprintf(L"%ls\n", text->sentences[i].text);
    }
}

void print_one_line(Text *text) {
    for(int i = 0; i < text->length; i++) {
        wprintf(L"%ls ", text->sentences[i].text);
    }
}