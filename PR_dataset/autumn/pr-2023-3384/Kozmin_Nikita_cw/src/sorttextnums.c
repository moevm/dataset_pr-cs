#ifndef stdlib
#include <stdlib.h>
#endif
#ifndef ctype
#include <ctype.h>
#endif

#include "sorttextnums.h"


int cmpsntncs(const void *first, const void *second){
	const char *f = *((const char **)first);
	const char *s = *((const char **)second);
	size_t product_num_f = 1;
	size_t product_num_s = 1;

	// Нахождение произведения цифр первого предложения
	for (size_t i = 0; f[i]; i++){
		if (isdigit(f[i])){
			product_num_f *= (size_t)f[i];
		}
	}

	// Нахождение произведения цифр второго предложения
	for (size_t i = 0; s[i]; i++){
		if (isdigit(s[i])){
			product_num_s *= (size_t)s[i];
		}
	}
	
	return product_num_f - product_num_s;
}

void sorttextnums(char ***sentences, size_t *cnt_sentences){
	qsort(*sentences, *cnt_sentences, sizeof(char *), cmpsntncs);
}
