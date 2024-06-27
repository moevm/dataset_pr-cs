#include "counting.h"
#include "log.h"
int cyrillicCounter(const Sentence *sentence)
{
	int counter = 0;
	const wchar_t *str = sentence->sentence;
	 while (*str) {
        if ((*str >= L'А' && *str <= L'я') || (*str >= L'Ё' && *str <= L'ё')) 
            counter++;
        str++;
    }
    return counter;	
}