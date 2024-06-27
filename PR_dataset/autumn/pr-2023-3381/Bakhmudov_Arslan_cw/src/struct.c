#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "safety.h"
#include "macros.h"
#include "struct.h"



int stch_index(struct Sentence * st_p, struct Sentence * chain_p)
{
	int count = 0;
	struct Word * wp1;
	struct Word * wp2;
	char same;

	while (chain_p != NULL)
	{
		wp1 = st_p->start;
		wp2 = chain_p->start;
		same = 1;
		while (wp1 != NULL || wp2 != NULL)
		{
			// Sentences differ if:
			// 1) their lengths are different
			if (wp1 == NULL || wp2 == NULL)
			{
				same = 0;
				break;
			}
			// 2) their corresponding words are different
			if (wcscasecmp(wp1->str, wp2->str) != 0)
			{
				same = 0;
				break;
			}
			wp1 = wp1->next;
			wp2 = wp2->next;
		}
		if (same)
		{
			return count;
		}

		chain_p = chain_p->next;
		count++;
	}
	return -1;
}



int readtext(struct Text * text_p, wchar_t * endingchars)
{
	// Text-level variables
	size_t t_len = 0;
	struct Sentence * pin_st_p = NULL;

	// Sentence-level variables
	struct Sentence * prev_st_p = NULL;
	size_t s_len = 0;
	struct Word * pin_w_p = NULL;
	struct Sentence * sentence;

	// Word-level variables
	struct Word * prev_w_p = NULL;
	size_t cur_mem = WD_SIZE_STEP;
	wchar_t * cur_w = s_malloc(cur_mem * sizeof(wchar_t));
	size_t wi = 0;
	struct Word * word;

	// Flag variables
	char br = 0;
	char st_end = 0;

	// Current symbol
	wchar_t c;
	do
	{
		c = getwchar();

		// LineBreak Handling
		if (c == L'\n')
		{
			c = L' ';
			br += 1;
		}
		else
		{
			br = 0;
		}

		// Space Handling
		if (iswspace(c))
		{
			// Word Handling
			if (wi > 0)
			{
				// Adjusting Word size
				cur_w[wi] = '\0';
				cur_mem = wi + 1;
				cur_w = s_realloc(cur_w, cur_mem*sizeof(wchar_t));

				// Forging the Word
				word = s_malloc(sizeof(struct Word));
				word->str = cur_w;
				word->size = cur_mem;
				word->next = NULL;

				// Pinning the first Word
				if (pin_w_p == NULL) { pin_w_p = word; }

				// Jointing
				if (prev_w_p != NULL)
				{
					prev_w_p->next = word;
				}
				prev_w_p = word;
				s_len++;

				// Recycling
				cur_mem = WD_SIZE_STEP;
				cur_w = s_malloc(cur_mem*sizeof(wchar_t));
				wi = 0;
			}
		
			// Sentence Handler
			if (st_end || (br > 1 && s_len > 0))
			{
				// Forging the Sentence
				sentence = s_malloc(sizeof(struct Sentence));
				sentence->start = pin_w_p;
				sentence->size = s_len;
				sentence->next = NULL;

				// Checking the Sentence
				if (stch_index(sentence, pin_st_p) == -1)
				{
					// Pinning the first Sentence
					if (pin_st_p == NULL) { pin_st_p = sentence; }

					// Jointing
					if (prev_st_p != NULL)
					{
						prev_st_p->next = sentence;
					}
					prev_st_p = sentence;
					t_len++;
				}
				else
				{
					freest(sentence);
				}

				// Recycling
				pin_w_p = NULL;
				prev_w_p = NULL;
				s_len = 0;

				st_end = 0;
			}
		}
		// Char Handling
		else if (!iswspace(c))
		{
			// Memory reallocation
			if (wi >= cur_mem - 1)
			{
				cur_mem += WD_SIZE_STEP;
				cur_w = s_realloc(cur_w, cur_mem*sizeof(wchar_t));
			}
			
			// Word continuation
			cur_w[wi] = c;
			wi++;

			// Sentence end determining
			st_end = (wcschr(endingchars, c) != NULL);
		}
	}
	while (br < 2);

	// Text Forging
	text_p->start = pin_st_p;
	text_p->size = t_len;

	free(cur_w);
	return 0;
}



void printtext(struct Text * text_p)
{
	struct Sentence * st_p;
	struct Word * w_p;
	
	//wprintf(L"%ls\n", SPAN); /\/\/\ .
	st_p = text_p->start;
	while (st_p != NULL)
	{
		w_p = st_p->start;
		while (w_p != NULL)
		{
			wprintf(L"%ls", w_p->str);
			w_p = w_p->next;
			if (w_p != NULL)
			{
				wprintf(L" ");
			}
		}
		st_p = st_p->next;
		wprintf(L"\n");
	}
}



void freest(struct Sentence * st_p)
{
	struct Word * w_p;
	struct Word * wpt;

	w_p = st_p->start;
	while (w_p != NULL)
	{
		free(w_p->str);
		wpt = w_p->next;
		free(w_p);
		w_p = wpt;
	}
	free(st_p);
}



void freetext(struct Text * text_p)
{
	struct Sentence * st_p;
	struct Sentence * spt;
	
	st_p = text_p->start;
	while (st_p != NULL)
	{
		spt = st_p->next;
		freest(st_p);
		st_p = spt;
	}
}
