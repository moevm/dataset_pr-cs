#ifndef GET_TEXT
#define GET_TEXT
#include "structures_define.h"

struct Sentence *get_str();
struct Sentence *delete_trash(struct Sentence *str);
struct Text get_text();
void withdraw_text(struct Text txt);

#endif