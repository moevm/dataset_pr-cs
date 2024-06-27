#include "handle_action.h"



int handle_action(Action action)
{
    if (action_without_text_processing(action))
        return 0;

    return action_with_text_processing(action);
    
}
