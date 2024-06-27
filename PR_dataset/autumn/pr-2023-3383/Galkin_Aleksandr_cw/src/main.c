#include "structures_define.h"
#include "get_text.h"
#include "text_treatment.h"
#include "time_funcs.h"
#include "funcs_explanation.h"

int main()
{
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.15, created by Aleksandr Galkin.\n");
    int method;
    if (wscanf(L"%d", &method) != 1)
    {
        wprintf(L"Error: не введено число, указывающее на то, что программа должна сделать. Программа будет приостановлена.\n");
        return 0;
    }
    if ((method > 5 || method < 0) && method!=9)
    {
        wprintf(L"Error: введено неверное значение. Программа будет приостановлена.\n");
        return 0;
    }
    if (method != 5)
    {
        struct Text received_text = get_text();
        if(received_text.length!=0){
            switch (method)
            {
            case 0:
                withdraw_text(received_text);
                break;
            case 1:
                for (int i = 0; i < received_text.length; i++)
                {
                    translate_func(received_text.text[i]);
                }
                withdraw_text(received_text);
                break;
            case 2:
                check_time(received_text);
                break;
            case 3:
                delete_sentences(received_text);
                break;
            case 4:
                get_and_check_dates(received_text);
                break;
            case 9:
                func9(received_text);
                break;
            }
        }
        else withdraw_text(received_text);
        release_text(received_text);
    }
    else
        explain_functions();
}