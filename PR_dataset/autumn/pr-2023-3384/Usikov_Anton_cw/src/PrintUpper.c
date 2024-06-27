#include "PrintUpper.h"
void
PrintUpper (struct Text *T)
{
	for (int i = 0; i < T->l; i++)
	{
		struct Sentence *sentence = T->txt[i];
		wchar_t *sentence_copy = wcsdup (sentence->str);
		wchar_t *pt;
		wchar_t *word = wcstok (sentence_copy, L" ,.", &pt);
		while (word != NULL)
		{
			int length = wcslen (word);
			if (iswupper (word[0]) && iswupper (word[length - 1]))
			{
				int found = 0;
				for (int j = 0; j < i; j++)
				{
					 struct Sentence *previous_sentence = T->txt[j];

					  if (wcsstr (previous_sentence->str, word) != NULL)
					  {
						   found = 1;
						   break;
					  }
				}
				if (!found)
				{
					wprintf (L"%ls: %d", word, i + 1);
					for (int j = i + 1; j < T->l; j++)
					{
						 struct Sentence *next_sentence = T->txt[j];
						 if (wcsstr (next_sentence->str, word) != NULL)
						 {
							 wprintf (L" %d", j + 1);
						 }
					}
					wprintf (L"\n");
				}
			}
			word = wcstok (NULL, L" ,.", &pt);
		}
		free (sentence_copy);
	}
}
