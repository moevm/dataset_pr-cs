#include "ioroutine.h"


void say_hello() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wprintf(START_INFO);
}

void panic(wchar_t* message) {
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
    wprintf(HELP_MSG_H);
    wprintf(HELP_MSG_0);
    wprintf(HELP_MSG_1);
    wprintf(HELP_MSG_2);
    wprintf(HELP_MSG_3);
    wprintf(HELP_MSG_4);
    wprintf(HELP_MSG_5);
    wprintf(HELP_MSG_9);
}