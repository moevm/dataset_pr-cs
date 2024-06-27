#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

#include "input.h"
#include "output.h"
#include "structs.h"
#include "free_memory.h"

void preprocessing() {
    Text* text = (Text*)malloc(1 * sizeof(Text));
    text->sentences = (Sentence*)malloc(sizeof(Sentence));
    input_text(text);
    if (text->sentences != NULL) {
        output_text(text);
        free_text(text);
    }
}
