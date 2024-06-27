#include "freedom.h"//1
#include "struct.h"

void freedom(struct Text text) {
    for (size_t i = 0; i < text.cnt_sen; i++) {
        free(text.txt[i]);
    }
  free(text.txt);
}