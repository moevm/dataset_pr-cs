#include "failure.h"

void failure(wchar_t * message){
	wprintf(L"%ls", message);
	exit(0);
}
