#include "error.h"

void error(int error_type){
    switch (error_type)
    {
    case 0:
        wprintf(ERROR_FORMAT, ERROR, error_type, L"некорректный ввод номера функции");
        break;
    case 1:
        wprintf(ERROR_FORMAT, ERROR, error_type, L"замечено пустое предложение"); //убрал потому что тест на моевм не одобрил моих инноваторских решений
        break;
    case 2:
        wprintf(ERROR_FORMAT, ERROR, error_type, L"неопознанный знак переноса строки");
        break;
    }
    exit(1);
}