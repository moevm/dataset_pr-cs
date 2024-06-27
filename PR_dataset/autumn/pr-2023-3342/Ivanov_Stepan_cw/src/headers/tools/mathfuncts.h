#pragma once

#ifndef _MATHFUNCTS_H
#define _MATHFUNCTS_H

#include <stdio.h>

static inline size_t
_ceil(double val)
{
    if (val < 0)
        return 0;

    return (size_t)(val) + 1;
}


#endif // _MATHFUNCTS_H
