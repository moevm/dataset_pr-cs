#include <wchar.h>

void throwTestTypeError() {
    wprintf(L"Error: wrong test type.\n");
}

void throwTextEndError() {
    wprintf(L"Error: invalid text end.\n");
}