#include "textHandle.h"

int is_separator(wchar_t symbol)
{
    return (iswspace(symbol) || iswpunct(symbol));
}
