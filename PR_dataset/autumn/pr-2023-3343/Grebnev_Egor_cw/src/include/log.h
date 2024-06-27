#ifndef LOGGING_H
#define LOGGING_H

#include <wchar.h>

void logErr(const wchar_t *format, ...);
void logWarn(const wchar_t *format, ...);
void logInfo(const wchar_t *format, ...);
void logInfoDefault(const wchar_t *format, ...);
void logInfoD(const wchar_t *format, ...);
#endif