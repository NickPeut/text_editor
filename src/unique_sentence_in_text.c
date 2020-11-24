#include "unique_sentence_in_text.h"

Sentence_t* getWord(Text_t* text, size_t* n, size_t* m);
void checkWordUnique(Text_t *text, Sentence_t *word, Text_t *ansText, size_t i);
bool check(Text_t *text, Sentence_t *word, int index);


void printUniqueWords(Text_t* text, FILE* file) {
    size_t i = 0;
    size_t j = 0;
    Text_t* ansText = (Text_t*)malloc(sizeof(Text_t));
    initText(ansText);
    while(i < text->size) {
        Sentence_t* word = getWord(text, &i, &j);
        checkWordUnique(text, word, ansText, i);
    }
    printText(ansText, file);
    freeText(ansText);
}



Sentence_t* getWord(Text_t* text, size_t* n, size_t* m) {
    Sentence_t *word = (Sentence_t *) malloc(sizeof(Sentence_t));
    initSentence(word);
    while(*n < text->size) {
        if(*m != 0)
            skipSeparators(m, text, n);
        if(*m >= text->sentences[*n]->size){
            (*n)++;
            (*m = 0);
        }
        while(*n < text->size && *m < text->sentences[*n]->size && !isEndingOfSentence(text->sentences[*n]->symbols[*m]) && !isSentenceSeparator(text->sentences[*n]->symbols[*m])){
            addSymbolToSentence(word, text->sentences[*n]->symbols[*m]);
            (*m)++;
            if(*m >= text->sentences[*n]->size || isEndingOfSentence(text->sentences[*n]->symbols[*m]) || isSentenceSeparator(text->sentences[*n]->symbols[*m])){
                return word;
            }
        }
        (*n)++;
        (*m) = 0;
    }
    return word;
}



void checkWordUnique(Text_t *text, Sentence_t *word, Text_t *ansText, size_t i) {
    bool flag = true;
    for(size_t k = 0; k < text->size; k++) {
        if(k != i) {
            if(check(text, word, k)){
                flag = (flag * false);
            }
        } else {
            flag = (flag * !isWordInSentence(text->sentences[k], word));
        }
    }
    if(flag) {
        addSentenceToText(ansText, word);
    } else {
        freeSentence(word);
    }
}


bool check(Text_t *text, Sentence_t *word, int index) {
    wchar_t* checkWStr = malloc(sizeof(wchar_t) * (text->sentences[index]->size + 2));
    wcpcpy(checkWStr, text->sentences[index]->symbols);
    wchar_t *buff;

    wchar_t * pch = wcstok(checkWStr,L" ,.", &buff);

    while (pch != NULL) {
        if (wcscmp(pch, word->symbols) == 0) {
            free(checkWStr);
            return true;
        }
        pch = wcstok (NULL, L" ,.", &buff);
    }
    free(checkWStr);
    return false;
}
