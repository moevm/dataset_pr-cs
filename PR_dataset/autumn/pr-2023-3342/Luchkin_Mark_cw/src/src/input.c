#include "input.h"

wchar_t* getFirstWord(){
    int capacity = 1;
    int size = 0;
    wchar_t *pattern = malloc(capacity * sizeof(wchar_t));
    wchar_t currChar;
    do{
        currChar = getwchar();
        pattern[size] = currChar;
        size++;
        if (size >= capacity){
            capacity *= 2;
            pattern = realloc(pattern, sizeof(wchar_t) * capacity);
        }
    }while(currChar != L'\n');

    pattern = realloc(pattern, sizeof(wchar_t) * (capacity + 1));
    pattern[size + 1] = L'\0';
    return pattern;
}


int getCommand(){
    int commandNumber;
    wscanf(L"%d\n", &commandNumber);

    return commandNumber;
}

wchar_t *getPattern(){
    int capacity = 1;
    int size = 0;
    wchar_t *pattern = malloc(capacity * sizeof(wchar_t));
    wchar_t currChar = getwchar();
    while(currChar != L'\n') {
        if (capacity <= size){
            capacity=size+1;
            pattern = realloc(pattern, sizeof(wchar_t) * capacity);
        }
        pattern[size] = currChar;
        size++;
        currChar = getwchar();
    }
    pattern[size] = L'\0';
    return pattern;
}

Sentence inputSentence(int *newLineCounter){
    Sentence sentence;
    sentence.chars = malloc(sizeof(wchar_t));
    int sentenceCapacity = 1;
    int sentenceSize = 0;
    wchar_t currChar;
    int flag = 1;

    do{
        currChar = getwchar();
        if (currChar == L'\n'){
            (*newLineCounter)++;
            if ((*newLineCounter) == 2){
                break;
            }
            continue;
        }

        if (iswspace(currChar) && flag){
            continue;
        }

        flag = 0;
        sentence.chars[sentenceSize++] = currChar;
        if (sentenceSize >= sentenceCapacity){
            sentenceCapacity *= 2;
            sentence.chars = realloc(sentence.chars, sentenceCapacity * sizeof(wchar_t)); 
        }

         
    }while(currChar != L'.');
    sentence.chars[sentenceSize] = L'\0';
    sentence.size = sentenceSize;
    
    int wordCounter = 0;
    wchar_t* tokenBuffer;
    wchar_t* copy = wcsdup(sentence.chars); 
    wchar_t* word = wcstok(copy, L" ,", &tokenBuffer);

    while (word != NULL) {
        wordCounter++;
        word = wcstok(NULL, L" ,", &tokenBuffer);
    }

    sentence.wordCounter = wordCounter;

    return sentence;
}

Text inputText(){
    Text text;
    text.sentences = malloc(sizeof(Sentence));
    int textCapacity = 1;
    int textSize = 0;
    int newLineCounter = 0;

    for(;;){
        Sentence currSentence = inputSentence(&newLineCounter);
        int identicalSentences = 0;

        for (int i = 0; i < textSize; ++i) {
            if(wcscasecmp(currSentence.chars, text.sentences[i].chars) == 0){
                identicalSentences = 1;
                break;
            }

        }

        if (newLineCounter == 2) {
            break;
        } else {
            newLineCounter=0;
        }

        if (identicalSentences == 1){
            continue;
        }

        wchar_t *tokenBuffer;
        wchar_t *token = wcstok(wcsdup(currSentence.chars), L" .,", &tokenBuffer);
        if ((token) == NULL){
            continue;
        }

        text.sentences[textSize] = currSentence;
        text.sentences[textSize].averageWordsLength = calculateAverageWordsLength(currSentence.chars);
        text.sentences[textSize].punctuation = getPunctuation(currSentence);
        textSize++;
        text.size = textSize;

        if (textSize >= textCapacity){
            textCapacity *= 2;
            text.sentences = realloc(text.sentences, textCapacity * sizeof(Sentence));
        }
    }

    if (text.sentences[0].chars == NULL){
        wprintf(L"Error: Incorrect input.\n");
        exit(0);

    }

    return text;
}

float calculateAverageWordsLength(wchar_t *sentence){
    int wordCounter = 0;
    float totalLength = 0;
    wchar_t* tokenBuffer;
    wchar_t* token = wcstok(wcsdup(sentence), L" .,", &tokenBuffer);
    
    while (token != NULL) {
        wordCounter++;
        totalLength += wcslen(token);
        token = wcstok(NULL, L" .,", &tokenBuffer);
    }

    return wordCounter > 0 ? (float)(totalLength / wordCounter) : 0.0f;
}


wchar_t **getPunctuation(Sentence sentence){
    int punctuationCapacity = 1;
    int punctuationSize = 0;
    wchar_t **punctuation = calloc(punctuationCapacity, sizeof(wchar_t *));

    for (int i = 0; i <= sentence.size; i++){
        if (sentence.chars[i] == L' ' || sentence.chars[i] == L',' || sentence.chars[i] == L'.'){
            int capacity = 1;
            int size = 0;
            // int index = i;
            wchar_t *currChars = calloc(capacity,sizeof(wchar_t));
            while (sentence.chars[i]==L'.'||sentence.chars[i]==L' '||sentence.chars[i]==L','){
                if (size > capacity){
                    capacity *= 2;
                    currChars = realloc(currChars, capacity * sizeof(wchar_t));
                }
                currChars[size] = sentence.chars[i];
                i++;
                size++;

            }

            punctuation[punctuationSize] = currChars;
            punctuationSize++;
            if (punctuationSize >= punctuationCapacity){
                punctuationCapacity *= 2;
                punctuation = realloc(punctuation, punctuationCapacity * sizeof(wchar_t*));
            }
        }
    }
    return punctuation;
}