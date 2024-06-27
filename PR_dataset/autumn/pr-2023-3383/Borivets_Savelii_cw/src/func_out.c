#include "func_out.h"
#include "freedom.h"
#include "struct.h"

void func_out(struct Text text, int freedom_mode) {
    for (size_t i = 0; i < text.cnt_sen; i++) {
        wprintf(L"%ls\n", text.txt[i]);
    }
    if (freedom_mode) freedom(text);
}