#include "menu.h"
int main() {

    setlocale( LC_ALL, "ru_RU.UTF-8");
    Text_t* text = (Text_t*)malloc(sizeof(Text_t));
    initText(text);
    FILE *input = fopen("input.txt", "r");
    readText(text, input);                                    //считываем текст
    fclose(input);
    deleteSameSentence(text);                                   //удаляем одинаковые предложения
    menu(text);                                               //открываем меню
    return 0;
}
