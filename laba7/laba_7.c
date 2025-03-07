#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


int main()
{
    printf("эта программа рисует прямоугольники и считает их количество в матрице\n");
    int choice = 0;
    int **matrix;
    int n;
    int result;
    int add_more = 0;

    do
    {
    // Добавлен запрос на выбор ручного или случайного ввода
    printf("\033[1;32mВы хотите ввести размер матрицы вручную (1) или сгенерировать случайно (2)? ");
    int input_choice = get_valid_input("");  // Получаем выбор пользователя
        if (input_choice == 1)
        {
            n = square_matrix_size(n);  // Запросим размер вручную, если выбрано 1
        }
        else if (input_choice == 2)
        {
            n = rand() % 25 + 1;  // Сгенерируем случайное значение от 1 до 25
            printf("\033[1;32mСгенерированный размер матрицы: %d\n", n);
        }
        matrix = memAloc(n, n);     // Выделение памяти под двумерный массив
        fill0(matrix, n, n);        // Заполнение матрицы нулями
        do
        {
            printf("\033[1;32mВведите параметры прямоугольника:\n");
            inst_input(matrix, n, n);  // Ввод прямоугольников
            output_matrix(matrix, n, n);  // Вывод матрицы
            printf("\033[1;32mХотите создать еще один прямоугольник? (1 - да, любая другая цифра - нет): ");
            add_more = choice_func2(add_more);
        }
        while (add_more == 1);
        result = kol_vo_Rectangles(matrix, n);  // Подсчет прямоугольников
        printf("\033[1;32mКоличество прямоугольников: %d\n", result);  // Вывод результата
        clearMatrix(matrix, n);  // Очистка памяти
        choice = choice_func(choice);  // Выбор продолжения
    }
    while (choice == 1);
    printf("\033[1;32mКонец программы.\n");
    return 0;
}
