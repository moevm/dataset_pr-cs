#include "option.h"
#include <locale.h>
#include <wchar.h>
#include "error.h"

int main(){
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.6, created by Pchelkin Nikita.\n");
    int flag;
    if(!wscanf(L"%d\n", &flag)) error(0);
    
    option(flag);

    return 0;
}
