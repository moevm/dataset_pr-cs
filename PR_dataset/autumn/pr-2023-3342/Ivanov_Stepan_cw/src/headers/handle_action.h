#pragma once 


#ifndef _HANDLE_ACTION_H
#define _HANDLE_ACTION_H

#include <stdlib.h>
#include <wchar.h>

#include "request_action.h"
#include "handle_functs/action_without_text_processing.h"
#include "handle_functs/action_with_text_processing.h"

#include "tools/textio.h"
#include "tools/error.h"


int handle_action(Action);


#endif // _HANDLE_ACTION_H
