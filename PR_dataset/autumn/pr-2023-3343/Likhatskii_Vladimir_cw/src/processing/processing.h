#include <wchar.h>

#pragma once
#include "../structures/structures.h"
#pragma once
#include "../helpers/helpers.h"
#pragma once 
#include "../dates/dates.h"


Text *initial_processing(Text*);
Text *process_1(Text * text);
Text *process_2(Text * text);
Text *process_3(Text * text);
Text *process_4(Text * text);
Text *process_9(Text * text);
Text *split_by_space(wchar_t *str);