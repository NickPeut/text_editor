#include "text.h"

void initText(Text_t* text) {
    text->capacity = 10;
    text->sentences = (Sentence_t**)malloc(text->capacity * sizeof(Sentence_t*));
    text->size = 0;
}


void reserveTextMemory(Text_t* text, size_t newCapacity) {
    text->sentences = (Sentence_t**)(realloc(text->sentences, newCapacity * sizeof(Sentence_t*)));
    text->capacity = newCapacity;
}


void addSentenceToText(Text_t* text, Sentence_t* sentence) {
    if (text->size == text->capacity) {
        reserveTextMemory(text, text->capacity * 2);
    }
    text->sentences[text->size] = sentence;
    text->size++;
}

void readText(Text_t* text, FILE *file) {
    while (true) {
        Sentence_t *sentence = (Sentence_t *) malloc(sizeof(Sentence_t));
        initSentence(sentence);
        readSentence(sentence, file);
        updateSentenceProduct(sentence);
        if (sentence->size == 0 || isTerminalSymbol(sentence->symbols[sentence->size - 1])) {
            freeSentence(sentence);
            break;
        }
        addSentenceToText(text, sentence);
    }
}
int cmp(const void* a, const void* b){
    if ((*((Sentence_t**)a))->product == (*((Sentence_t**)b))->product)
      return 0;
    else {
        if ((*((Sentence_t**)a))->product < (*((Sentence_t**)b))->product) {
            return -1;
        }
        else return 1;
    }
}


void printText(Text_t *text, FILE *file) {
    for (size_t i = 0; i < text->size; i++) {
        fwprintf(file,L"%ls ", text->sentences[i]->symbols);
    }
    fwprintf(file,L"\n\n");
}

void deleteSentences(Text_t* text, size_t ind) {
    freeSentence(text->sentences[ind]);
    for (size_t i = ind; i < text->size - 1; i++) {
        text->sentences[i] = text->sentences[i+1];
    }
    text->size--;
}

bool isWordInSentence(Sentence_t* sentence, Sentence_t* word){
    int count = 0;
    if (word->size > sentence->size)
        return false;

    for(size_t i = 0; i < sentence->size - word->size; i++){
        size_t j = 0;
        for(j = 0; j < word->size; j++){
            if(sentence->symbols[i+j] != word->symbols[j]) {
                break;
            }
        }
        if(j == word->size){
            count++;
        }
    }
    return count > 1;
}


void skipSeparators(size_t* j, Text_t* text, const size_t* i) {
    do {
        (*j)++;
    } while(*j < text->sentences[*i]->size && (isEndingOfSentence(text->sentences[*i]->symbols[*j]) || isSentenceSeparator(text->sentences[*i]->symbols[*j])));
}






void deleteSameSentence(Text_t *text) {
    for (size_t i = 0; i < text->size - 1; i++) {
        for (size_t j = i+1; j < text->size; j++) {
            if (wcscasecmp(text->sentences[i]->symbols, text->sentences[j]->symbols) == 0) {
                deleteSentences(text, j);
                j--;
            }
        }
    }
}

void freeText(Text_t* text) {
    for (size_t i = 0; i < text->size; i++) {
        freeSentence(text->sentences[i]);
    }
    free(text->sentences);
    free(text);
}
