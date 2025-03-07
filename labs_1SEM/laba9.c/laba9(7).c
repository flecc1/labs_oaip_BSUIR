#include "functions.h"



int main()
{
    void (*vivod)(char ****matrices, int n1, int n, int m);
    vivod = print_matrix;

    // Массив указателей на функции (для ввода и вывода)
    void (*operations[2])(char ****, int, int, int) = {input_matrix, vivod};
    int choice = 0;
    do
    {
        int n1 = get_val("Введите количество матриц (n1): "); // Количество матриц
        int n = get_val("Введите количество строк (n): ");   // Количество строк
        int m = get_val("Введите количество столбцов (m): "); // Количество столбцов
        int *palindrome_counts = malloc(n1 * sizeof(int));
        
        char ****matrices = mem_matrices(n1, n, m); // Выделяем память для матриц
        // Цикл для вызова функций ввода и вывода
        for (int i = 0; i < 2; i++)
        {
            operations[i](matrices, n1, n, m); // Вызываем функции по порядку
        }
        count_palindromes(matrices, n1, n, m, palindrome_counts); // Подсчёт палиндромов
        print_results(palindrome_counts, n1);     // Вывод результатов
        clear_matrices(matrices, n1, n, m);       // Освобождение памяти

        choice = choice_func(choice);
    } while (choice == 1);

    printf("\033[1;32mКонец программы\n\033[0m");
    return 0;
}