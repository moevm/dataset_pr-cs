#ifndef __PARSE_FUNCS__
#define __PARSE_FUNCS__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <regex.h>

#include "bmp.h"
#include "exceptions.h"

int32_t parse_unsigned_char(const char*, uint8_t*);

// parse coords in format x.y
int32_t parse_coords(const char*, int64_t**);

int32_t parse_posit_number(const char*, uint32_t*);

// parse color components in format r.g.b
int32_t parse_comps(const char*, RGB* color);
    
#endif
