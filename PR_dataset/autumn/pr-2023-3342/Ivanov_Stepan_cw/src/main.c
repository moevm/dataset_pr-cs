#include "handle_action.h"
#include "option_message.h"
#include "request_action.h"
#include "information.h"

#include <locale.h>


int main_logic();

int main(int argc, char **argv)
{
    setlocale(LC_ALL, LOCALE);
    return main_logic();

}


int 
main_logic()
{
    print_option_message(VERSION, AUTHOR);

    Action action = request_action();

    return handle_action(action);

}
