#pragma once 


#ifndef _REQUEST_ACTION_H
#define _REQUEST_ACTION_H

#include <stdio.h>
#include <stdbool.h>
#include <wchar.h>


typedef enum {
	PREPROCESSING = 			L'0',
	REPLACING_WORDS = 			L'1',
	ASCENDING_DATES = 			L'2',
	DELETING_SENTENCES = 			L'3',
	DISPLAYING_SPECIFIC_DATES = 		L'4',
	HELPING_INFO = 				L'5',
	REPLACE_BIG_WORDS = 			L'9',
	EXIT = 					L'-',
	NOT_ACTION = 				0

} Action;

Action request_action();


#endif // _REQUEST_ACTION_H
