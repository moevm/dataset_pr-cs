#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>

#include "safety.h"
#include "macros.h"
#include "struct.h"
#include "functions.h"



char iswlatin(wchar_t c)
{
	return (														\
				(													\
					c > 64 && c < 91								\
				)													\
				||													\
				(													\
					c > 96 && c < 123								\
				)													\
	);
}



char iswcyrillic(wchar_t c)
{
	return (														\
				(c > 1039 && c < 1104)								\
				||													\
				(c == 1025)											\
				||													\
				(c == 1105)											\
	);
}



int st_sort_cmp(const void * a, const void * b)
{
	int scorea = 0;
	int scoreb = 0;
	struct Word * wa_p = (*((struct Sentence **)a))->start;
	struct Word * wb_p = (*((struct Sentence **)b))->start;
	size_t wi;

	// Counting latin characters in a
	while (wa_p != NULL)
	{
		wi = 0;
		while ((wa_p->str)[wi] != '\0')
		{
			scorea += iswlatin((wa_p->str)[wi]);
			wi++;
		}
		wa_p = wa_p->next;
	}

	// Counting latin characters in b
	while (wb_p != NULL)
	{
		wi = 0;
		while ((wb_p->str)[wi] != '\0')
		{
			scoreb += iswlatin((wb_p->str)[wi]);
			wi++;
		}
		wb_p = wb_p->next;
	}

	return (scoreb - scorea);
}



void f1_palindromes(struct Text * text_p)
{
	struct Sentence * st_p;
	struct Word * w_p;
	struct Word * wpt;
	struct Word wbase;
	size_t cur_s;
	wchar_t * cur_v;

	wchar_t * std;
	int si;
	wchar_t * rev;
	int ri;
	wchar_t * c;
	int pc = 0;

	st_p = text_p->start;
	while (st_p != NULL)
	{
		pc = 0;
		w_p = st_p->start;
		while (w_p != NULL)
		{
			// Constructing an all-alphabetic version of the Word
			std = s_malloc((w_p->size)*sizeof(wchar_t));
			si = 0;
			c = w_p->str;
			while (*c != '\0')
			{
				if (iswalpha(*c))
				{
					std[si] = *c;
					si++;
				}
				c++;
			}
			std[si] = '\0';

			// Constructing a REVERSED all-alphabetic version of the Word
			rev = s_malloc((si+1)*sizeof(wchar_t));
			ri = si-1;
			si = 0;
			while (ri >= 0)
			{
				rev[ri] = std[si];
				si++;
				ri--; 
			}
			rev[si] = '\0';

			// Recognizing a palindrome
			pc += (wcscasecmp(std, rev) == 0);

			free(std);
			free(rev);
			wpt = w_p->next;
			if (wpt == NULL)
			{
				break;
			}
			else
			{
				w_p = wpt;
			}
		}
		if (pc == 0)
		{
			// No palindromes
			cur_s = 33;
			cur_v = s_malloc(cur_s*sizeof(wchar_t));
			cur_v = wcsncpy(cur_v, L"[Кто-то потерял все палиндромы.]", cur_s);
		}
		else if (pc == st_p->size)
		{
			// Everything is a palindrome
			cur_s = 23;
			cur_v = s_malloc(cur_s*sizeof(wchar_t));
			cur_v = wcsncpy(cur_v, L"[Палиндромы на месте!]", cur_s);
		}
		else
		{
			// There are both palindromes and non-palindromes
			cur_s = 22;
			cur_v = s_malloc(cur_s*sizeof(wchar_t));
			cur_v = wcsncpy(cur_v, L"[Чего-то не хватает.]", cur_s);
		}
		// Attaching the result
		wbase.str = cur_v;
		wbase.size = cur_s;
		wbase.next = NULL;
		wpt = s_malloc(sizeof(wbase));
		*wpt = wbase;
		w_p->next = wpt;
		st_p = st_p->next;
	}
}



void f2_spec_char(struct Text * text_p)
{
	struct Sentence * s_p;
	struct Word * w_p;
	size_t wi;
	wchar_t * n_w;
	size_t nwi;
	size_t mem = WD_SIZE_STEP;

	// Replacement substring
	const size_t SL = 16;
	wchar_t src[] = L">special symbol<";
	size_t srci = 0;
	
	s_p = text_p->start;
	while (s_p != NULL)
	{
		w_p = s_p->start;
		while (w_p != NULL)
		{
			// New word creation
			n_w = s_malloc(mem*sizeof(wchar_t));
			nwi = 0;
			wi = 0;
			while((w_p->str)[wi] != '\0')
			{
				if (nwi + SL + 2 > mem)
				{
					mem += WD_SIZE_STEP;
					n_w = s_realloc(n_w, mem*sizeof(wchar_t));
				}

				if (iswpunct((w_p->str)[wi]) || iswcntrl((w_p->str)[wi]))
				{
					// Substring addition
					n_w[nwi] = '\0';
					
					while (srci < SL)
					{
						n_w[nwi + srci] = src[srci];
						srci++;
					}
					n_w[nwi + srci] = '\0';
					srci = 0;
					nwi += SL;
				}
				else
				{
					// Char addition
					n_w[nwi] = (w_p->str)[wi];
					nwi++;
				}
				wi++;
			}
			// Replacing the word with its processed version
			n_w[nwi] = '\0';
			mem = nwi+1;
			n_w = s_realloc(n_w, mem*sizeof(wchar_t));
			free(w_p->str);
			w_p->size = mem;
			w_p->str = n_w;

			w_p = w_p->next;
		}
		s_p = s_p->next;
	}
}



void f3_sort(struct Text * text_p)
{
	struct Sentence * st_p = text_p->start;
	struct Sentence ** addr_order = s_malloc((text_p->size) * sizeof(st_p));
	long oi = 0;
	// Sentence address list creation
	while(st_p != NULL)
	{
		addr_order[oi] = st_p;
		st_p = st_p->next;
		oi++;
	}

	// Arranging the address order
	qsort(addr_order, text_p->size, sizeof(st_p), st_sort_cmp);

	// Sentence chain reconstruction
	oi = 0;
	while (oi < ((long)(text_p->size) - 1))
	{
		addr_order[oi]->next = addr_order[oi+1];
		oi++;
	}

	text_p->start = *addr_order;
	if ((text_p->size) > 0)
	{
		addr_order[oi]->next = NULL;
	}

	free(addr_order);
}



void f4_filter(struct Text * text_p)
{
	struct Sentence * pst_p = NULL;
	struct Sentence * st_p = text_p->start;
	struct Sentence * nst_p = NULL;
	struct Word * w_p;
	char lat;
	char cyr;
	size_t wi;

	while (st_p != NULL)
	{
		nst_p = st_p->next;
		w_p = st_p->start;
		while (w_p != NULL)
		{
			lat = 0;
			cyr = 0;
			wi = 0;
			while ((w_p->str)[wi] != '\0')
			{
				if (iswlatin((w_p->str)[wi])) { lat = 1; }
				if (iswcyrillic((w_p->str)[wi])) { cyr = 1; }
				wi++;
			}
			if (cyr && lat) { break; }
			w_p = w_p->next;
		}
		if (cyr && lat)
		// Destroy this Sentence, its previous Sentence now links to its next Sentence
		{
			if (pst_p != NULL)
			{
				pst_p->next = nst_p;
			}
			freest(st_p);
		}
		else
		// Move to the next Sentence
		{
			if (pst_p == NULL)
			{
				pst_p = st_p;
				text_p->start = pst_p;
			}
			else
			{
				pst_p = st_p;
			}
		}
		st_p = nst_p;
	}
}



void f5_info()
{
	wprintf(
		L"%ls\n"
		L"Программа форматирует введённый текст, удаляя все повторно встречающиеся предложения, причём предложения сравниваются без учёта регистра.\n"
		L"Символы, являющиеся концом предложения, можно настраивать, изменяя файл \"%ls\".\n"
		L"При распечатке текста программой слова печатаются через пробел, предложения разделены переносом строки.\n\n"
		L"Подробное описание команд программы:\n"
		L"0) Распечатать текст без изменений\n"
		L"1) Распечатать для каждого предложения [Палиндромы на месте!], если все слова являются палиндромами, [Кто-то потерял все палиндромы.], если палиндромов нет, и [Чего-то не хватает.] в иных случаях\n"
		L"2) Распечатать текст, заменив все специальные символы на \">special symbol<\"\n"
		L"3) Распечатать текст, отсортировав предложения по убыванию количества латинских букв\n"
		L"4) Распечатать текст, удалив все предложения, в которых есть слово, состоящее и из кириллических, и из латинских букв\n"
		L"5) Распечатать эту справку (без ввода текста)\n"
		L"\nP.S. Существует секретные команды :D\n", SPAN, CFG_FILENAME_INFO
	);
}



void f9_whitelist(struct Text * text_p, wchar_t ** whitelist)
{
	struct Sentence * pst_p = NULL;
	struct Sentence * st_p = text_p->start;
	struct Sentence * nst_p = NULL;
	struct Word * w_p;
	size_t wl_i;
	wchar_t word[2024];
	size_t origwi;
	size_t readywi;
	char found;

	while (st_p != NULL)
	{
		nst_p = st_p->next;
		w_p = st_p->start;
		while (w_p != NULL)
		{
			origwi = 0;
			readywi = 0;
			while (w_p->str[origwi] != '\0')
			{
				if (!iswpunct(w_p->str[origwi]))
				{
					word[readywi] = w_p->str[origwi];
					readywi++;
				}
				origwi++;
			}
			word[readywi] = '\0';

			found = 0;
			wl_i = 0;
			while (whitelist[wl_i] != NULL)
			{
				if (!wcscasecmp(whitelist[wl_i], word))
				{
					found = 1;
					break;
				}
				wl_i++;
			}
			if (!found) { break; }

			w_p = w_p->next;
		}
		if (!found)
		// Destroy this Sentence, its previous Sentence now links to its next Sentence
		{
			if (pst_p != NULL)
			{
				pst_p->next = nst_p;
			}
			freest(st_p);
		}
		else
		// Move to the next Sentence
		{
			if (pst_p == NULL)
			{
				pst_p = st_p;
				text_p->start = pst_p;
			}
			else
			{
				pst_p = st_p;
			}
		}
		st_p = nst_p;
	}
}
