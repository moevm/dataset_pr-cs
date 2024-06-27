#pragma ones;
struct Sentence;
struct Text;

int latin_counter(struct Sentence *sen);

int cmp_latin_counter(const void *sen1, const void *sen2);

void latin_sort(struct Text *text);
