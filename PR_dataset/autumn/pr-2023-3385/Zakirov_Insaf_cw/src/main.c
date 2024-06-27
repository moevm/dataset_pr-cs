#include <locale.h>

#include "myinout.h"
#include "myfunc.h"
#include "mysupport.h"

int main() {
    setlocale(LC_ALL, "");
    printinfo();

	Text text;
/*
    wchar_t sen[10];
    wscanf(L"%ls", sen);
    wprintf(L"%ls", sen);

    return 0;
  */  

    switch (scancommand()) {
        case 0:
    		scantext(&text);
            break;
        case 1:
    		scantext(&text);
			f1(&text);
            break;
        case 2:
    		scantext(&text);
			f2(&text);
            break;
        case 3:
    		scantext(&text);
			f3(&text);
            break;
        case 4:
    		scantext(&text);
			f4(&text);
            break;
        case 5:
            printhelp();
			return 0;
            break;
        case 9:
            scantext(&text);
			f9(&text);
            break;    
        default:
            printerror("command not equal 0, 1, 2, 3, 4, 5, 9");
			return 0;
            break;
    }

	if (text.sentence != NULL) {
		printtext(&text);
		myfreetext(&text);
	}
	
    return 0;
}
