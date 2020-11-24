#ifndef WCHAR__SENTENCE_H
#define WCHAR__SENTENCE_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <wctype.h>
    #include <stdbool.h>
    #include <wchar.h>
    #include <locale.h>
    #define INIT 10

    typedef struct Sentence{
        wchar_t* symbols;
        size_t size;
        size_t capacity;
        int product;
    } Sentence_t;

    void initSentence(Sentence_t* sentence);
    bool isEndingOfSentence(char x);
    bool isSentenceSeparator(char x);
    void reserveSentenceMemory(Sentence_t* sentence, size_t newCapacity);
    void addSymbolToSentence(Sentence_t* sentence, wchar_t symbol);
    bool isTerminalSymbol(wchar_t symbol);
    void readSentence(Sentence_t* sentence, FILE *file);
    void updateSentenceProduct(Sentence_t* sentence);
    bool foundInSentence(Sentence_t* sentence);
    void freeSentence(Sentence_t* sentence);

#endif //WCHAR__SENTENCE_H
