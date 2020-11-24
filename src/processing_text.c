#include "processing_text.h"

bool foundInSentence(Sentence_t* sentence);
bool isSentenceIncludeDigit(Sentence_t* sentence);
bool isSentenceIncludeSearchWchar(Sentence_t* sentence);


void processingText(Text_t* text) {
    for (size_t i = 0;  i < text->size; i++) {
        if (!foundInSentence(text->sentences[i])) {
            deleteSentences(text, i);
            i--;
        }
    }
}


bool foundInSentence(Sentence_t* sentence) {
    if (isSentenceIncludeSearchWchar(sentence)) {
        if (isSentenceIncludeDigit(sentence)) {
            return true;
        }
        return false;
    }
    return true;
}


bool isSentenceIncludeDigit(Sentence_t* sentence){
    for (size_t i = 0; i < sentence->size; i ++) {
        if(iswdigit(sentence->symbols[i]))
            return true;
    }
    return false;
}

bool isSentenceIncludeSearchWchar(Sentence_t* sentence){
    for (size_t i = 0; i < sentence->size; i ++) {
        if(sentence->symbols[i] == L'#' || sentence->symbols[i] == L'№')
            return true;
    }
    return false;
}
