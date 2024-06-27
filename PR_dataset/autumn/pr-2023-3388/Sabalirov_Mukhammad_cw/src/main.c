#include <locale.h>
#include "choice_answer.h"

int main(){
    setlocale(LC_ALL, "");
    say_hello();
    choice_func();
    return 0;
}
