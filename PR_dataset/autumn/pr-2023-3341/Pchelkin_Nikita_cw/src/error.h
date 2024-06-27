#include <stdlib.h>
#include <wchar.h>

#define ERROR L"Произошла ошибка"
#define ERROR_FORMAT L"%ls № %d: %ls!\n"

void error(int error_type);