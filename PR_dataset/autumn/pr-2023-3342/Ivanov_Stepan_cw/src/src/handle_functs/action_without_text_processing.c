#include "handle_functs/action_without_text_processing.h"


void _helping_info()
{
    print_message(INFO_PREFACE);
    print_message(INFO_ABOUT_ZERO_OPTION);
    print_message(INFO_ABOUT_ONE_OPTION);
    print_message(INFO_ABOUT_TWO_OPTION);
    print_message(INFO_ABOUT_THREE_OPTION);
    print_message(INFO_ABOUT_FOUR_OPTION);
    print_message(INFO_ABOUT_FIVE_OPTION);
    print_message(INFO_ABOUT_EXIT);

}

void _exit_app()
{
    print_message(MESSAGE_FOR_EXIT);

}

void _not_action()
{
    error(1, MESSAGE_FOR_INVALID_ACTION);

}


bool
action_without_text_processing(Action action)
{
    switch (action)
    {
    case HELPING_INFO:
        _helping_info();
        return true;

    case EXIT:
        _exit_app();
        return true;

    case NOT_ACTION:
        _not_action();
        return true;
    
    default:
        return false;
 
    }

}