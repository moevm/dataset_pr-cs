#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

#include "structs.h"

void output_text(Text* text) {
    for (int i = 0; i < text->size_text; i++)
        wprintf(L"%ls\n", text->sentences[i].str);
}
