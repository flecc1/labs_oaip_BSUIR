#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"s

int main() 
{
    printf("\033[1;32mЭта программа удаляет начальный и конечные пробелы в строке.\nИ заменяет группы пробелов внутри строки на один пробел\n\n");

    int input_choice = 0, fill_choice = 0, choice = 0, n;
    char *str;

    do
    {
        printf("\033[1;32mВы хотите задать размер строки вручную (1) или сгенерировать случайно (2)?\nВыбор: ");
        input_choice = get_valid_input("");

        if (input_choice == 1)
        {
            n = strSize(n); // Пользователь вводит размер строки
        }
        else if (input_choice == 2)
        {
            n = rand() % (100 - 30 + 1) + 30; // Генерация размера строки от 30 до 100
            printf("\033[1;32mСгенерированный размер строки: %d\n", n);
        }

        str = memStr(n); // Выделение памяти под строку

        printf("\033[1;32mВы хотите ввести строку вручную (1) или заполнить случайными символами (2)?\nВыбор: ");
        fill_choice = get_valid_input("");

        if (fill_choice == 1)
        {
            vvod(str, n); // Ручной ввод строки
        }
        else if (fill_choice == 2)
        {
            randVvod(str, n); // Случайное заполнение строки
        }

        delSYM(str, n);  // Удаление нуль-символа
        Spaces(str);     // Удаление лишних пробелов
        clearStr(str);   // Освобождение памяти

        choice = choice_func(choice);
    } while (choice == 1);

    printf("\033[1;32mКонец программы.\n");
    return 0;
}
