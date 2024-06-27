#include "console.h"


void on_startup() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wprintf(START_INFO);
}

void error(wchar_t* message) {
    wprintf(L"%ls\n", message);
    exit(0);
}

wchar_t* read(wchar_t* buf) {
    *buf = getwchar();
    return buf;
}

void write(wchar_t buf) {
    fputwc(buf, stdout);
}

void print_help() {
    wprintf(HELP_MSG);
}