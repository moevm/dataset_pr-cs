#include <locale.h>
#include "function_select.h"
#include "description.h"

int main () {
    setlocale(LC_CTYPE, "");
    description();
    function_select();
    return 0;
}