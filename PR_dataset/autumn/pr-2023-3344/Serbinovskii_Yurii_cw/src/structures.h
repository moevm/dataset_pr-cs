#pragma once


struct Sentence {
    wchar_t* s;
};

struct Text {
    struct Sentence** t;
};