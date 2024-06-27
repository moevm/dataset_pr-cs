#include "main.h"

int main() {
    setlocale(LC_CTYPE, "");
    wprintf(L"Course work for option 5.14, created by Asiya Kireeva.\n");
    wchar_t c = getwchar();
    if (iswdigit(c)) {
        int n = (int) c - '0';
        switch (n) {
            case 0:
                zero_func();
                break;
            case 1:
                first_func();
                break;
            case 2:
                second_func();
                break;
            case 3:
                third_func();
                break;
            case 4:
                fourth_func();
                break;
            case 5:
                fifth_func();
                break;
            case 9:
                ninth_func();
                break;

            default:
                wprintf(L"Error: Неверный номер команды.\n");
                break;
        }
    } else {
        wprintf(L"Error: Неверный номер команды.\n");
    }
    return 0;
}