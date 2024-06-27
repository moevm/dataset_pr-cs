#include <locale.h>
#include "start_and_choose_function.h"

int main(){
    setlocale(LC_ALL, "");
    start();
    choose_function();
    return 0;
}