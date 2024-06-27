#include <wchar.h>
#include <stdio.h>


#include "macros.h"
#include "config.h"


int config(wchar_t * endingchars)
{
	FILE * fileptr = fopen(CFG_FILENAME, "r");
	if (fileptr == NULL)
	{
		// File not found
		endingchars = wcscpy(endingchars, L".?!");
		fileptr = fopen(CFG_FILENAME, "w");
		if (fileptr == NULL)
		{
			// Unable to create the file
			return 2;
		}
		// Create the file
		fwprintf(fileptr, L"%ls\n", endingchars);
		fclose(fileptr);
		return 1;
	}
	// Read delimiters from the file
	fgetws(endingchars, ENDINGCHARS_MAX_LEN, fileptr);
	fclose(fileptr);
	while (*endingchars != L'\n' && *endingchars != L'\0')
	{
		endingchars++;
	}
	*endingchars = L'\0';
	return 0;
}