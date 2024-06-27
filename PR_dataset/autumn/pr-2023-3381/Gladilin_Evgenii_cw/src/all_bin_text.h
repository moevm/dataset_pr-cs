#pragma once
#include <stdlib.h>
#include <wchar.h>
#include <ctype.h>
#include <wctype.h>
#include "structs.h"
#include "other_stuff.h"

struct Sentence *make_bin(struct Sentence *sentence);
struct Text bin(struct Text text);
void all_bin_sym(struct Text text);

