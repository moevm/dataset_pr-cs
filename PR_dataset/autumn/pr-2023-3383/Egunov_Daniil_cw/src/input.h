#ifndef CW_INPUT_H
#define CW_INPUT_H

#include <stdbool.h>
#include "text.h"
#include "sentence.h"

Text *read_text(bool remove_duplicate_whitespaces, bool correct_spaces_with_commas);

#endif //CW_INPUT_H
