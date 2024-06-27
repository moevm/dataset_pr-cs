#pragma once 


#ifndef _ERROR_H
#define _ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

static inline void
error(size_t exitcode, const wchar_t *msg)
{
    wprintf(L"Error: %ls\n", msg);
    exit(exitcode);
}


#endif // _ERROR_H
