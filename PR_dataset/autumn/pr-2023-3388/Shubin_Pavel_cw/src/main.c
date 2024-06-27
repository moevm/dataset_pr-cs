#include "structs_libraries.h"
#include "user_functions.h"
#include "text_reading.h"
#include "support_functions.h"
#include "output_function.h"


int main(){
    setlocale(LC_CTYPE, "");
    wprintf(COURSE_WORK_INFO);
    struct Text text;
    int chosen_function;
    if (wscanf(L"%d", &chosen_function) != 1){
        wprintf(L"Ошибка. Неверный ввод значения выбора действия.\n");
        exit(1);
    }
    process_chosen_function(chosen_function, text);   
    return 0;
}


