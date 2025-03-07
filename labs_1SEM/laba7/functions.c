#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <limits.h>
#include <time.h>

// Функция для подсчета прямоугольников в матрице
int kol_vo_Rectangles(int **matrix, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (*(*(matrix + i) + j) == 1)
            {
                count++;
                for (int x = i; x < n && *(*(matrix + x) + j) == 1; x++)
                {
                    for (int y = j; y < n && *(*(matrix + x) + y) == 1; y++)
                    {
                        *(*(matrix + x) + y) = 0;
                    }
                }
            }
        }
    }
    return count;
}

// Функция для выделения памяти под двумерный массив
int **memAloc(int rows, int cols)
{
    int **mas = (int **)malloc(rows * sizeof(int *));
    if (mas == NULL)
    {
        printf("\033[1;31mОшибка выделения памяти\n");
    }

    for (int i = 0; i < rows; i++)
    {
        *(mas + i) = (int *)malloc(cols * sizeof(int));
        if (*(mas + i) == NULL)
        {
            printf("\033[1;31mОшибка выделения памяти\n");
        }
    }

    return mas;
}

// Функция для заполнения матрицы нулями
void fill0(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(matrix + i) + j) = 0;
        }
    }
    printf("Нулевая матрица:\n");

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%5d ", *(*(matrix + i) + j));
        }
        printf("\n\n");
    }
    printf("\n");
}

// Функция для вывода матрицы
void output_matrix(int **matrix, int rows, int cols)
{
    printf("Введенная матрица: \n\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (*(*(matrix + i) + j) == 1)
                printf("\033[1;34m%5d ", *(*(matrix + i) + j));
            else
                printf("\033[1;32m%5d ", *(*(matrix + i) + j));
        }
        printf("\n\n");
    }
    printf("\n");
}

// Функция для очистки памяти
void clearMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(*(matrix + i));
    }
    free(matrix);
}

// Функция для ввода размера матрицы
int square_matrix_size(int n)
{
    int p2 = 0;
    while (1)
    {
        printf("\033[1;32mВведите размер поля: ");
        rewind(stdin);
        p2 = scanf("%d", &n);
        if (proverka2(n, p2))
        {
            break;
        }
    }
    return n;
}

// Функция для выбора продолжения программы
int choice_func(int n)
{
    printf("\n");
    int p3 = 0;
    while (1)
    {
        printf("\033[1;32mВведите 1, если хотите начать программу заново, любая другая цифра - конец программы: ");
        rewind(stdin);
        p3 = scanf("%d", &n);
        if (p3 != 1)
        {
            printf("\033[1;31mВведите цифру\n");
        }
        else if (n != 1)
        {
            break;
        }
        else
        {
            break;
        }
    }
    return n;
}

// Функция для проверки введенных данных
int proverka2(int a, int y)
{
    if (y != 1 || a <= 0 || a > 25)
    {
        printf("\n\033[31mОшибка. Некорректный ввод. Попробуйте снова, введенное число должно быть от 1 до %d\033[0m\n", 25);
        rewind(stdin);
        return 0;
    }
    else
    {
        return 1;
    }
}

// Функция для ввода данных с проверкой
int get_valid_input(char *prompt)
{
    int value;
    while (1)
    {
        printf("%s", prompt);
        rewind(stdin);
        if (scanf("%d", &value) == 1)
        {
            return value;
        }
        else
        {
            printf("\033[1;31mНекорректный ввод. Пожалуйста, введите число.\n");
        }
    }
}

// Функция для ввода параметров прямоугольника
void inst_input(int **matrix, int rows, int cols)
{
    int row_start, col_start, rect_height, rect_width;
    int choice;

    printf("\033[1;32mВы хотите ввести параметры прямоугольника вручную (1) или случайным образом (2)? ");
    while (1)
    {
        choice = get_valid_input("");
        if (choice == 1 || choice == 2)
        {
            break;
        }
        else
        {
            printf("\033[1;31mНеверный выбор. Пожалуйста, введите 1 для ручного ввода или 2 для случайного.\n");
        }
    }

    if (choice == 1)
    {
        while (1)
        {
            row_start = get_valid_input("\033[1;32mВведите номер строки, с которого начинается прямоугольник: ");
            if (row_start > rows)
            {
                printf("\033[1;31mВы вышли за пределы матрицы. Попробуйте снова\n");
            }
            else if (row_start == 0)
            {
                printf("\033[1;31m0-вой строки нет, введенная строка должна быть хотя бы с номером 1\n");
            }
            else
            {
                row_start--;
                break;
            }
        }
        while (1)
        {
            col_start = get_valid_input("\033[1;32mВведите номер столбца, с которого начинается прямоугольник: ");
            if (col_start > cols)
            {
                printf("\033[1;31mВы вышли за пределы матрицы. Попробуйте снова\n");
            }
            else if (col_start == 0)
            {
                printf("\033[1;31m0-вого столбца нет, введенный столбец должен быть хотя бы с номером 1\n");
            }
            else
            {
                col_start--;
                break;
            }
        }
        while (1)
        {
            rect_height = get_valid_input("\033[1;32mВведите высоту прямоугольника: ");
            if (rect_height == 0)
            {
                printf("\033[1;31mЭлемент должен состоять хотя бы из одной единицы\n");
            }
            else if (rect_height > rows - row_start)
            {
                printf("\033[1;31mВы вышли за пределы матрицы. Попробуйте снова\n");
            }
            else break;
        }

        while (1)
        {
            rect_width = get_valid_input("\033[1;32mВведите ширину прямоугольника: ");
            if (rect_width == 0)
            {
                printf("\033[1;31mЭлемент должен состоять хотя бы из одной единицы\n");
            }
            else if (rect_width > cols - col_start)
            {
                printf("\033[1;31mВы вышли за пределы матрицы. Попробуйте снова\n");
            }
            else break;
        }
    }
    else
    {
        row_start = rand() % rows;
        col_start = rand() % cols;
        rect_height = rand() % (rows - row_start) + 1;
        rect_width = rand() % (cols - col_start) + 1;
        printf("\033[1;32mСгенерированные параметры прямоугольника:\n");
        printf("Номер строки: %d\n", row_start + 1);
        printf("Номер столбца: %d\n", col_start + 1);
        printf("Высота: %d\n", rect_height);
        printf("Ширина: %d\n", rect_width);
    }

    if (row_start + rect_height > rows || col_start + rect_width > cols)
    {
        printf("\033[1;31mПрямоугольник выходит за пределы матрицы. Попробуйте снова.\n");
        return;
    }

    if (checkOverlap(matrix, rows, row_start, col_start, rect_height, rect_width))
    {
        printf("\033[1;31mПрямоугольник пересекается или соприкасается с существующим. Попробуйте снова.\n");
        return;
    }

    for (int i = row_start; i < row_start + rect_height; i++)
    {
        for (int j = col_start; j < col_start + rect_width; j++)
        {
            *(*(matrix + i) + j) = 1;
        }
    }
}

// Функция для проверки пересечения прямоугольников
int checkOverlap(int **matrix, int size, int row, int col, int rectHeight, int rectWidth)
{
    for (int i = row - 1; i <= row + rectHeight; i++)
    {
        for (int j = col - 1; j <= col + rectWidth; j++)
        {
            if (i >= 0 && i < size && j >= 0 && j < size && *(*(matrix + i) + j) == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

int choice_func2(int n)
{
    int p3 = 0;
    while (1)
    {
        printf("\033[1;32mВведите 1, если хотите создать еще один прямоугольник, любая другая цифра - конец подсчета прямоугольников: ");
        rewind(stdin);
        p3 = scanf("%d", &n);
        if (p3 != 1)
        {
            printf("\033[1;31mВведите цифру\n");
        }
        else if (n != 1)
        {
            break;
        }
        else if(n == 1)
        {
            break;
        }
    }
    return n;
}
