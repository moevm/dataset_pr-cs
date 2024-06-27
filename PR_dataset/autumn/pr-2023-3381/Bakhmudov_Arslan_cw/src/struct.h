#pragma once

#include <wchar.h>

#include "struct.h"



struct Text
{
	struct Sentence * start;	// Pointer to the first Sentence of the text
	size_t size;				// Number of Sentences in the Text
};



struct Sentence
{
	struct Word * start;		// Pointer to the first Word of the Sentence
	size_t size;				// Number of Words in the Sentence
	struct Sentence * next;		// Pointer to the next Sentence
};



struct Word
{
	wchar_t * str;				// Pointer to the memory allocated for the tring of the Word
	size_t size;				// Amount of memory (in Chars) allocated
	struct Word * next;			// Pointer to the next Word
};



// Gets a Sentence and a Sentence Chain, returns index of Sentence in Chain or -1
int stch_index(struct Sentence * st_p, struct Sentence * ch_start_p);

// Gets a Text, parses stdin, fills the Text, returns a redundant zero
int readtext(struct Text * text_p, wchar_t * endingchars);
// Gets a Text, prints it reasonably
void printtext(struct Text * text_p);
// Sentence destructor. Gets a Sentence, frees all memory it uses
void freest(struct Sentence * st_p);
// Text destrucctor. Gets a Text, frees all Sentences in it
void freetext(struct Text * text_p);
