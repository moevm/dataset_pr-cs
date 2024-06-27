#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

#pragma once
#include "../config/config.h"
#pragma once
#include "../helpers/helpers.h"
#pragma once
#include "../structures/structures.h"

void print_program_info(); 
void print_program_help();

wchar_t get_cmd();
wchar_t * read_stdin();

void print_text(Text*);
void print_one_line(Text*);