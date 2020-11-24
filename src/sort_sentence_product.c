#include "sort_sentence_product.h"

void sortText(Text_t* text){
    qsort(text->sentences, text->size, sizeof(Sentence_t*), cmp);
}
