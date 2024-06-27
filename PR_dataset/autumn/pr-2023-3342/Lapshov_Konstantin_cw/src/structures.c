#include "structures.h"


struct Word create_word(){
    struct Word new_word;

    new_word.quantity_of_letters = 0;
    new_word.quantity_of_punctuation = 0;
    new_word.letters = NULL;
    new_word.punctuation = NULL;

    return new_word;
}
void add_letters(struct Word* word, wchar_t symbol){
    word->letters = realloc(word->letters, sizeof(wchar_t) * (word->quantity_of_letters + 2));
    if(word->letters == NULL){
        wprintf(L"Error: Ошибка выделения памяти");
        exit(0);
    }

    word->letters[word->quantity_of_letters] = symbol;
    word->quantity_of_letters++;
    word->letters[word->quantity_of_letters] = L'\0';
}
void add_punctuation(struct Word* word, wchar_t symbol){
    word->punctuation = realloc(word->punctuation, sizeof(wchar_t) * (word->quantity_of_punctuation + 2));
    if(word->punctuation == NULL){
        wprintf(L"Error: Ошибка выделения памяти");
        exit(0);
    }

    word->punctuation[word->quantity_of_punctuation] = symbol;
    word->quantity_of_punctuation++;
    word->punctuation[word->quantity_of_punctuation] = L'\0';
}

struct Sentence create_sentence(){
    struct Sentence new_sen;

    new_sen.quantity_of_words = 0;
    new_sen.words = NULL;

    return new_sen;
}
void add_word(struct Sentence* sen, struct Word word){
    sen->words = realloc(sen->words, sizeof(struct Word) * (sen->quantity_of_words + 1));
    if(sen->words == NULL){
        wprintf(L"Error: Ошибка выделения памяти");
        exit(1);
    }

    sen->words[sen->quantity_of_words] = word;
    sen->quantity_of_words++;
}

struct Text create_text(){
    struct Text new_text;
    new_text.quantity_of_sentences = 0;
    new_text.sentences = NULL;

    return new_text;
}
void add_sentence(struct Text *text, struct Sentence sen){
    text->sentences = realloc(text->sentences, sizeof(struct Sentence) * (text->quantity_of_sentences + 1));
    if(text->sentences == NULL){
        wprintf(L"Error: Ошибка выделения памяти");
        exit(1);
    }

    text->sentences[text->quantity_of_sentences] = sen;
    text->quantity_of_sentences++;
}

struct Unique_Word create_unique_word(wchar_t* word){
    struct Unique_Word new_unique_word;

    new_unique_word.letters = word;
    new_unique_word.word_count = 0;

    return new_unique_word;
}

size_t quantity_of_latin(struct Sentence sen){
    size_t latins = 0;

    for (int i = 0; i < sen.quantity_of_words; i++) {
        struct Word *curr_word = &sen.words[i];
        for (int j = 0; j < curr_word->quantity_of_letters; j++) {
            if (towlower(curr_word->letters[j]) >= L'a' && towlower(curr_word->letters[j]) <= L'z') latins++;
        }
    }
    return latins;
}