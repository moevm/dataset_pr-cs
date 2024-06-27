#include <stdio.h>
#include <stdarg.h>
#include "log.h"

void logErr(const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);

#ifdef LOG_USE_COLOR
    wprintf(L"\033[1;33mError: \033[0m");
    wprintf(L"\033[1;31m");
    vwprintf(format, args);
    wprintf(L"\033[0m\n");
#else
    wprintf(L"Error: ");
    vwprintf(format, args);
    wprintf(L"\n");
#endif
    va_end(args);
}

void logInfo(const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);

#ifdef LOG_USE_COLOR
    wprintf(L"\033[92m");
    vwprintf(format, args);
    wprintf(L"\033[0m\n");
#else
    vwprintf(format, args);
    wprintf(L"\n");
#endif
    va_end(args);
}

void logWarn(const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);

#ifdef LOG_USE_COLOR
    wprintf(L"\033[1;33mError: \033[0m");
    wprintf(L"\033[38;5;214m");
    vwprintf(format, args);
    wprintf(L"\033[0m\n");
#else
    wprintf(L"Error: ");
    vwprintf(format, args);
    wprintf(L"\n");
#endif
    va_end(args);
}

void logInfoDefault(const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);

    vwprintf(format, args);
    wprintf(L"\n");

    va_end(args);
}
void logInfoD(const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);

    vwprintf(format, args);
 

    va_end(args);
}
