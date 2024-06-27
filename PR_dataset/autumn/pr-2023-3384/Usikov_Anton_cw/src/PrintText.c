#include "PrintText.h"

void PrintText(struct Text* T){
	for (int i = 0; i < T->l; i++)
    	wprintf(L"%ls\n", T->txt[i]->str);
}
