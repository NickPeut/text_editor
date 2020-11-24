#include "update_format_date.h"

Sentence_t* foundDate(Sentence_t *sentence);
bool checkDate(Sentence_t *sentence, size_t index, wchar_t date[12]);
Sentence_t* updateSentenceDate(Sentence_t *sentence, size_t index, wchar_t* date);


void dateProcessing(Text_t* text) {
    for(size_t i = 0; i < text->size; i++) {
        text->sentences[i] = foundDate(text->sentences[i]);
    }
}


Sentence_t* foundDate(Sentence_t *sentence) {
    wchar_t date[12][12] = {L"31 января ", L"29 февраля ",
                            L"31 марта ", L"30 апреля ", L"31 мая ",
                            L"30 июня ", L"31 июля ", L"31 августа ",
                            L"30 сентября ", L"31 октября ", L"30 ноября ",
                            L"31 декабря "};

    for (size_t i = 0; i < sentence->size - 1; i++) {
        if (i != 0) {
            if (isSentenceSeparator(sentence->symbols[i])) {
                continue;
            }
        }
        if (iswdigit(sentence->symbols[i]) != 0 && (iswdigit(sentence->symbols[i + 1]) || sentence->symbols[i+1] == L' ')) {
            for (int m = 0; m < 12; m++) {
                if (checkDate(sentence, i, date[m])) {
                    wchar_t fdate[7];
                    if (iswdigit(sentence->symbols[i + 1])) {
                        fdate[0] = sentence->symbols[i];
                        fdate[1] = sentence->symbols[i + 1];
                    } else {
                        fdate[0] = L'0';
                        fdate[1] = sentence->symbols[i];
                    }
                    fdate[2] = L'/';
                    if (m + 1 < 10) {
                        fdate[3] = L'0';
                        fdate[4] = m + 1 + L'0';
                    } else {
                        fdate[3] = L'1';
                        fdate[4] = L'0' + ((m + 1) % 10);
                    }
                    fdate[5] = L'/';
                    fdate[6] = L'\0';
                    return updateSentenceDate(sentence, i, fdate);
                }
            }
        }
    }
    return sentence;
}


bool checkDate(Sentence_t *sentence, size_t index, wchar_t date[12]) {
    int day = (sentence->symbols[index] - L'0');
    if (iswdigit(sentence->symbols[index+1])) {
        day = day * 10 + (sentence->symbols[index + 1] - L'0');
    }

    int maxDay = (date[0] - L'0') * 10 + (date[1] - L'0');
    int flag = day < 10;
    if (index > sentence->size - wcslen(date) - 7 + flag)
        return false;

    if(sentence->size < wcslen(date) + 7 + flag)
        return false;

    //checkDay;
    if (maxDay < day)
        return false;

    //checkMonth;
    size_t i;
    for (i = 2; i < wcslen(date); i++) {
        if (sentence->symbols[index + i - flag] != date[i])
            return false;
    }
    size_t k = 0;

    //checkYear;
    for (k = 0; k < 4; k++) {
        if(!iswdigit(sentence->symbols[index + i + k - flag]))
            return false;
    }
    wchar_t exampleYear[] = L" г.";
    for (size_t y = 0; y < wcslen(exampleYear); y++) {
        if (sentence->symbols[index + i + k + y - flag] != exampleYear[y])
            return false;
    }

    return true;
}




Sentence_t* updateSentenceDate(Sentence_t *sentence, size_t index, wchar_t* date) {

    Sentence_t* newSentence = (Sentence_t*)malloc(sizeof(Sentence_t));
    initSentence(newSentence);

    for(size_t i = 0; i < index; i++) {
        addSymbolToSentence(newSentence, sentence->symbols[i]);
    }
    for (size_t i = 0; i < wcslen(date); i++) {
        addSymbolToSentence(newSentence, date[i]);
    }
    while(sentence->symbols[index] != L'г' || sentence->symbols[index + 1] != L'.') {
        index++;
    }
    index -= 5;
    int k = 0;
    while(k < 4) {
        k++;
        addSymbolToSentence(newSentence, sentence->symbols[index]);
        index++;
    }
    addSymbolToSentence(newSentence, L'.');
    addSymbolToSentence(newSentence, L'\0');
    freeSentence(sentence);
    updateSentenceProduct(newSentence);
    return newSentence;
}
