#include <locale.h>
#include "processing.h"

int main(){
	setlocale(LC_CTYPE, "");
	wprintf(L"Course work for option 5.11, created by Shapovalenko Egor\n");

	initial_processing();

	return 0;
}
