#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

#include "structs.h"

void free_text(Text* text) {
    for (int i = 0; i < text->size_text; i++){
        free(text->sentences[i].str);
    }
    free(text->sentences);
}
