#include "input_output.h"
#include <wctype.h>

Word readWord(){
    int size = MEMORY_STEP;
    int len = 0;
    wchar_t * chars = malloc(size*sizeof(wchar_t));
    wchar_t sep, symbol = L' ';

    while(symbol == L' ')
        symbol = getwchar();

    while(!wcschr(WORD_SEP, symbol) && !wcschr(SENTENCE_SEP, symbol)){
        chars[len++] = symbol;
        if(len == size){
            size += MEMORY_STEP;
            chars = realloc(chars, size*sizeof(wchar_t));
        }
        symbol = getwchar();
    }

    chars[len] = L'\0';
    sep = symbol;

    return (Word){chars, sep, len};
}

Sentence readSentence(){
    int size = MEMORY_STEP;
    int len = 0;
    Word* words = malloc(size*sizeof(Word));
    Word word;

    do{
        word = readWord();
        words[len++] = word;
        if(len == size){
            size += MEMORY_STEP;
            words = realloc(words, size*sizeof(Word));
        }
    }while(!wcschr(SENTENCE_SEP, word.sep));

    return (Sentence){words, len};
}

int isEndOfText(Text text){
    if(text.len < 2)
        return 0;
    Sentence lastSent = text.sents[text.len-1];
    Sentence sent = text.sents[text.len-2];
    return lastSent.len == 1 && lastSent.words[0].len == 0 && lastSent.words[0].sep == L'\n' && sent.words[sent.len-1].sep == L'\n';
}

Text readText(){
    int size = MEMORY_STEP;
    int len = 0;
    Sentence* sents = malloc(size*sizeof(Sentence));
    Sentence sent;

    do{
        sent = readSentence();
        sents[len++] = sent;
        if(len == size){
            size += MEMORY_STEP;
            sents = realloc(sents, size*sizeof(Sentence));
        }
    }while(!isEndOfText((Text){sents, len}));

    free(sents[len-1].words[0].chars);
    free(sents[len-1].words);
    len--;

    if(sents[len-1].words[sents[len-1].len-1].sep == L'\n')
        sents[len-1].words[sents[len-1].len-1].sep = L'.';

    return (Text){sents, len};
}

void printText(Text text){
    for(Sentence* sent = text.sents; sent < text.sents + text.len; sent++) {
        for (Word *word = sent->words; word < sent->words + sent->len; word++) {
            if (word->len) {
                wprintf(L"%ls%lc", word->chars, word->sep);
                if (word->sep == L',')
                    wprintf(L" ");
            }
        }
        wprintf(L"\n");
    }
}

int* getCharacters(Sentence* sent, wchar_t begin, wchar_t end){
    int* characters = malloc((end-begin+1)*sizeof(int));
    for(int i = 0; i < end-begin+1; i++)
        characters[i] = 0;
    for(Word* word = sent->words; word < sent->words + sent->len; word++){
        for(wchar_t* c = word->chars; c < word->chars + word->len; c++){
            if(towupper(*c) >= begin && towupper(*c) <= end)
                characters[towupper(*c) - begin]++;
        }
    }
    return characters;
}

int isAnagrams(Sentence* first, Sentence* second){
    wchar_t begin[3] = {L'0', L'A', L'А'};
    wchar_t end[3] = {L'9', L'Z', L'Я'};

    for(int i = 0; i < 3; i ++) {
        int *firstCharacters = getCharacters(first, begin[i], end[i]);
        int *secondCharacters = getCharacters(second, begin[i], end[i]);

        for (int j = 0; j < end[i]-begin[i]+1; j++) {
            if (firstCharacters[j] != secondCharacters[j]){
                free(firstCharacters);
                free(secondCharacters);
                return 0;
            }
        }

        free(firstCharacters);
        free(secondCharacters);
    }

    return 1;
}

void printAnagrams(Text text){
    for(Sentence* firstSent = text.sents; firstSent < text.sents + text.len - 1; firstSent++){
        int size = MEMORY_STEP;
        Sentence* sents = malloc(size* sizeof(Sentence));
        sents[0] = *firstSent;
        int len = 1;
        for(Sentence* secondSent = firstSent + 1; secondSent < text.sents + text.len; secondSent++){
            if(isAnagrams(firstSent, secondSent)){
                sents[len++] = *secondSent;
                if(len == size){
                    size += MEMORY_STEP;
                    sents = realloc(sents, size*sizeof(Sentence));
                }
            }
        }
        if(len != 1){
            printText((Text){sents, len});
            wprintf(L"\n");
        }
        free(sents);
    }
}

