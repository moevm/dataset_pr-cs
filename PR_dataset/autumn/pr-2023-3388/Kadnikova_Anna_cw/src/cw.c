#include "menu.h"


int main() {
    on_startup();
    wchar_t input; read(&input);
    menu(input);
    return 0;
}
