#include "Common.h"
#include "OutText.h"

void outText(char** text) {
 for (int i = 0; text[i] != NULL; i++) {
  printf("%s\n", text[i]);
 }
}
