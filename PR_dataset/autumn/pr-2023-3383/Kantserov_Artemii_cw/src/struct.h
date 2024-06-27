#ifndef CW_STRUCT_H
#define CW_STRUCT_H

struct sentence {
    char *str;
    int **dates;
    int count_dates;
    int print;
};
struct text {
    struct sentence* sentence;
    int count_sentence;
};
#endif //CW_STRUCT_H
