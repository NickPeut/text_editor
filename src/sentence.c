#include "sentence.h"

void initSentence(Sentence_t* sentence){
    sentence->capacity = INIT;
    sentence->symbols = (wchar_t *)calloc(sentence->capacity, sizeof(wchar_t));
    sentence->size = 0;
    sentence->product = 1;
}

bool isEndingOfSentence(char x) {
    return x == '.';
}


bool isSentenceSeparator(char x) {
    return x == ' ' || x == ',';
}

void reserveSentenceMemory(Sentence_t* sentence, size_t newCapacity) {
    sentence->symbols = (wchar_t*)realloc(sentence->symbols, newCapacity * sizeof(wchar_t));
    sentence->capacity = newCapacity;
}

void addSymbolToSentence(Sentence_t* sentence, wchar_t symbol) {
    if (sentence->size == sentence->capacity - 1) {
        reserveSentenceMemory(sentence, sentence->capacity * 2);
    }
    sentence->symbols[sentence->size++] = symbol;
    sentence->symbols[sentence->size] = L'\0';
}

bool isTerminalSymbol(wchar_t symbol) {
    return symbol == L'\n';
}


void readSentence(Sentence_t* sentence, FILE *file) {
    wchar_t symbol = L'\0';
    do {
        symbol = fgetwc(file);
        if (isSentenceSeparator(symbol) && sentence->size == 0)
            continue;
        if (isTerminalSymbol(symbol) && sentence->size == 0)
            break;
        addSymbolToSentence(sentence, symbol);
        if (isTerminalSymbol(symbol))
            break;
        if (isEndingOfSentence(symbol))
            break;
    } while(symbol != WEOF || symbol != L'\n');
}


void updateSentenceProduct(Sentence_t* sentence){
    int k = 0;
    if(sentence->size == 0){
        sentence->product = 0;
        return;
    }
    for(size_t i = 0; i < sentence->size; i++) {
        if(isSentenceSeparator(sentence->symbols[i]) && k != 0) {
            sentence->product *= k;
            k = 0;
        }
        else{
            if(!isEndingOfSentence(sentence->symbols[i]))
                k++;
        }
    }
    if(k != 0)
        sentence->product *= k;
}


void freeSentence(Sentence_t* sentence) {
    free(sentence->symbols);
    free(sentence);
}
