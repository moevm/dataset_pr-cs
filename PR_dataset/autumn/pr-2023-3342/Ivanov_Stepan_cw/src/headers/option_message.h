#pragma once 


#ifndef _OPTION_MESSAGE_H
#define _OPTION_MESSAGE_H

#include <stdio.h>
#include <wchar.h>

#include "information.h"

static inline void 
print_option_message(const wchar_t *version, const wchar_t *author)
{
    wprintf(
        PATTERN_OPTION_MESSAGE, 
        version, 
        author
    );

}


#endif // _OPTION_MESSAGE_H
