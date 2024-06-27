#include "ioroutine.h"

#define START_INFO L"Course work for option 5.12, created by Mukhammad Sabalirov.\n"

void say_hello() {
    wprintf(START_INFO);
}

void panic(wchar_t* message) {
    wprintf(L"%ls\n", message);
    exit(0);
}