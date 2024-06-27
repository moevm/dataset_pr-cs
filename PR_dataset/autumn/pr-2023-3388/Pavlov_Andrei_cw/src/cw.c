#include "menu.h"


int main() {
    say_hello();
    wchar_t input; read(&input);
    menu(input - L'0');
    return 0;
}
