#include "Common.h"
#include "FreeMemory1.h"

void memory_clean(CountWord* result, int* res) {
 int total_world = *res;
 for (int i = 0; i < total_world; i++) {
  free(result[i].word);
 }
 free(result);
}
