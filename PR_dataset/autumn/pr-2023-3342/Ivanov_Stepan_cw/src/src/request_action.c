#include "../headers/request_action.h"


bool
_is_action(wchar_t ch)
{
	switch (ch)
	{
	case PREPROCESSING:
	case REPLACING_WORDS:
	case ASCENDING_DATES:
	case DELETING_SENTENCES:
	case DISPLAYING_SPECIFIC_DATES:
	case HELPING_INFO:
	case REPLACE_BIG_WORDS:
	case EXIT:
		return true;
	
	default:
		return false;
	}

}


Action
request_action()
{
	wchar_t action = getwchar();

	if (getwchar() != L'\n')
        return NOT_ACTION;// clean buffer

	if (!_is_action(action))
		return NOT_ACTION; // TODO: ERROR MESSAGES

	return (Action)action;
	
}
