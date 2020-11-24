#include "menu.h"
void menu(Text_t* text){

    FILE *output = fopen("output.txt", "w");
    wprintf(L"_____________________________________________________\n"
                    L"Введите номер действия:\n"
                    L"    1 - Распечатать каждое слово которое встречается не более одного раза в тексте.\n"
                    L"    2 - Заменить формат даты на: ДД/ММ/ГГГГ”.\n"
                    L"    3 - Отсортировать предложения по произведению длин слов в предложении.\n"
                    L"    4 - Удалить все предложения, которые содержат символ ‘#’ или ‘№’, но не содержат ни одной цифры.\n"
                    L"    5 - Вывести текст\n"
                    L"    6 - Выход\n"
                    L"_____________________________________________________\n");
    fflush(stdout);
    int c;
    while(true) {
        scanf("%d", &c);
        switch (c) {
            case 1:
                printUniqueWords(text, output);
                break;
            case 2:
                dateProcessing(text);
                break;
            case 3:
                sortText(text);
                break;
            case 4:
                processingText(text);
                break;
            case 5:
                printText(text, output);
                break;
            case 6:
                fclose(output);
                freeText(text);
                return;
            default:
                wprintf(L"Error: не существующее действие.");
                fflush(stdout);
        }
    }

}
