#pragma once


// Tries to get a string of Sentence delimiters from config and write it to the endingchars.
// It config doesn't exist, creates one, prefilled with default .?! delimiters.
// If cannot create config, just uses default delimiters.
int config(wchar_t * endingchars);
