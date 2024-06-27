#include <stdio.h>
#include "menu.h"

int main() {
    say_hello();
    char input; get(&input);
    menu(input);
    return 0;
}

