#include "functions.h"

// Вспомогательная рекурсивная функция для проверки палиндрома
int is_phrase_palindrome_recursive(char *phrase, int left, int right)
{
    while (left < right && !isalnum(*(phrase + left))) // Пропускаем неалфавитные символы с левой стороны
    {
        left++;
    }
    while (left < right && !isalnum(*(phrase + right))) // Пропускаем неалфавитные символы с правой стороны
    {
        right--;
    }
    if (left >= right) // Если указатели встретились или перекрещиваются, значит, строка палиндром
    {
        return 1;
    }
    if (tolower(*(phrase + left)) != egor_tolower(*(phrase + right))) // Сравниваем символы с учётом регистра
    {
        return 0;  // Если символы не равны, то не палиндром
    }
    return is_phrase_palindrome_recursive(phrase, left + 1, right - 1); // Рекурсивно проверяем остальные символы
}

// Основная функция проверки палиндрома для фразы
int is_phrase_palindrome(char *phrase)
{
    return is_phrase_palindrome_recursive(phrase, 0, egor_strlen(phrase) - 1); // Вызываем рекурсивную функцию для всей строки
}

// Проверка и вывод отдельных слов с выделением палиндромов
void print_words_in_phrase(char *phrase)
{
    char buffer[MAX_K]; // Буфер для хранения текущего слова
    // char *buffer = (char *)malloc(MAX_K * sizeof(char)); // юуфе для хранения текущего слова
    int len = strlen(phrase); // Длина строки
    int index = 0;  // Индекс для записи в буфер

    for (int i = 0; i <= len; i++) // Проходим по каждому символу строки
    {
        if (isalnum(*(phrase + i))) // Если символ является буквой или цифрой
        {
            *(buffer + index++) = *(phrase + i); // Копируем символ в буфер
        }
        else if (index > 0) // Если встретили разделительный символ и буфер не пуст
        {
            *(buffer + index) = '\0'; // Завершаем строку в буфере
            if (is_phrase_palindrome(buffer)) // Проверяем, является ли слово палиндромом
            {
                printf(BLUE "%s " RESET, buffer); // Если палиндром, выводим синим
            }
            else
            {
                printf("%s ", buffer); // Иначе выводим обычным цветом
            }
            index = 0; // Сбрасываем индекс для следующего слова
        }
        else if (!isalnum(*(phrase + i)) && *(phrase + i) != '\0') // Если символ не является буквой или цифрой
        {
            printf("%c", *(phrase + i)); // Просто выводим символ (разделитель, пробел и т.д.)
        }
    }
    if (index > 0) // Если в конце остался непроверенный буфер
    {
        *(buffer + index) = '\0'; // Завершаем строку
        if (is_phrase_palindrome(buffer)) // Проверяем слово на палиндром
        {
            printf(BLUE "%s" RESET, buffer); // Если палиндром, выводим синим
        }
        else
        {
            printf("%s", buffer); // Иначе выводим обычным цветом
        }
    }
}

// Обновлённая функция вывода матриц
void print_matrix(char ****matrices, int n1, int n, int m)
{
    for (int i = 0; i < n1; i++) // Проходим по первой размерности матрицы
    {
        printf("\nМатрица %d:\n", i + 1); // Выводим заголовок для матрицы
        for (int j = 0; j < n; j++) // Проходим по второй размерности
        {
            for (int l = 0; l < m; l++) // Проходим по третьей размерности
            {
                print_words_in_phrase(*(*(*(matrices + i) + j) + l)); // Выводим слова из строки матрицы
                printf("\n");
            }
        }
    }
}

// Подсчёт палиндромов (слов и фраз)
void count_palindromes(char ****matrices, int n1, int n, int m, int *palindrome_counts)
{
    for (int i = 0; i < n1; i++) // Проходим по первой размерности матрицы
    {
        *(palindrome_counts + i) = 0; // Инициализируем счётчик палиндромов
        for (int j = 0; j < n; j++) // Проходим по второй размерности
        {
            for (int l = 0; l < m; l++) // Проходим по третьей размерности
            {
                char buffer[MAX_K]; // Буфер для хранения слова
                // char *buffer = (char *)malloc(MAX_K * sizeof(char));
                int len = egor_strlen(*(*(*(matrices + i) + j) + l)); // Длина строки
                int index = 0; // Индекс для записи в буфер

                for (int k = 0; k <= len; k++) // Проходим по каждому символу строки
                {
                    if (isalnum(*(*(*(*(matrices + i) + j) + l) + k))) // Если символ является буквой или цифрой
                    {
                        *(buffer + index++) = *(*(*(*(matrices + i) + j) + l) + k); // Копируем в буфер
                    }
                    else if (index > 0) // Если слово завершилось (разделительный символ)
                    {
                        *(buffer + index) = '\0'; // Завершаем строку
                        if (is_phrase_palindrome(buffer)) // Проверяем на палиндром
                        {
                            ++*(palindrome_counts + i); // Увеличиваем счётчик
                        }
                        index = 0; // Сбрасываем индекс для следующего слова
                    }
                }
                if (index > 0) // Если в буфере осталась непроверенная строка
                {
                    *(buffer + index) = '\0'; // Завершаем строку
                    if (is_phrase_palindrome(buffer)) // Проверяем на палиндром
                    {
                        ++*(palindrome_counts + i); // Увеличиваем счётчик
                    }
                }
            }
        }
    }
}

// Получение положительного целого числа
int get_val(char *prompt)
{
    int num;
    while (1) // Цикл продолжается, пока пользователь не введёт корректное число
    {
        printf("\033[0;32m%s\033[0m", prompt); // Выводим подсказку
        rewind(stdin); // Очищаем ввод
        if (scanf("%d", &num) != 1 || num <= 0 || num > INT32_MAX) // Проверка введённого числа
        {
            printf("\033[0;31mОшибка: введённое число должно быть больше 0 и до %d.\033[0m\n", INT32_MAX); // Ошибка, если число не положительное или слишком большое
        }
        else
        {
            return num; // Возвращаем правильное число
        }
    }
}

// Выделение памяти для матриц
char ****mem_matrices(int n1, int n, int m)
{
    char ****matrices = malloc(n1 * sizeof(char ***)); // Выделяем память для первой размерности
    for (int i = 0; i < n1; i++) // Выделяем память для второй размерности
    {
        *(matrices + i) = malloc(n * sizeof(char **)); 
        for (int j = 0; j < n; j++) // Выделяем память для третьей размерности
        {
            *(*(matrices + i) + j) = malloc(m * sizeof(char *)); 
            for (int l = 0; l < m; l++) // Выделяем память для элементов (строк) внутри матрицы
            {
                *(*(*(matrices + i) + j) + l) = malloc(MAX_K * sizeof(char)); // Выделяем память для строки
            }
        }
    }
    return matrices; // Возвращаем указатель на выделенную память
}

// Освобождение памяти
void clear_matrices(char ****matrices, int n1, int n, int m)
{
    for (int i = 0; i < n1; i++) // Проходим по первой размерности
    {
        for (int j = 0; j < n; j++) // Проходим по второй размерности
        {
            for (int l = 0; l < m; l++) // Проходим по третьей размерности
            {
                free(*(*(*(matrices + i) + j) + l)); // Освобождаем память для каждой строки
            }
            free(*(*(matrices + i) + j)); // Освобождаем память для второй размерности
        }
        free(*(matrices + i)); // Освобождаем память для первой размерности
    }
    free(matrices); // Освобождаем память для всего массива
}

// Ввод данных
void input_matrix(char ****matrices, int n1, int n, int m)
{
    for (int i = 0; i < n1; i++) // Проходим по первой размерности матрицы
    {
        for (int j = 0; j < n; j++) // Проходим по второй размерности
        {
            for (int l = 0; l < m; l++) // Проходим по третьей размерности
            {
                while (1) // Цикл для повторного ввода данных при ошибке
                {
                    printf("\033[0;32mВведите строку для матрицы %d, строка %d, столбец %d: \033[0m", i + 1, j + 1, l + 1); // Выводим запрос
                    rewind(stdin); // Очищаем ввод
                    fgets(*(*(*(matrices + i) + j) + l), MAX_K, stdin); // Вводим строку

                    if (strlen(*(*(*(matrices + i) + j) + l)) >= MAX_K - 1) // Проверка на длину строки
                    {
                        printf("\033[0;31mОшибка! Введенная строка слишком длинная. Пожалуйста, введите строку, не превышающую 100 символов.\033[0m\n"); // Ошибка, если строка слишком длинная
                    }
                    else
                    {
                        break; // Если строка корректна, выходим из цикла
                    }
                }
                int len = egor_strlen(*(*(*(matrices + i) + j) + l)); // Длина строки
                if (len > 0 && *(*(*(*(matrices + i) + j) + l) + len - 1) == '\n') // Если строка заканчивается на символ новой строки
                {
                    *(*(*(*(matrices + i) + j) + l) + len - 1) = '\0'; // Заменяем его на нулевой символ
                }
            }
        }
    }
}

// Вывод результатов
void print_results(int *palindrome_counts, int n1)
{
    for (int i = 0; i < n1; i++) // Проходим по всем матрицам
    {
        printf("\nВ матрице %d найдено %d палиндромов\n", i + 1, *(palindrome_counts + i)); // Выводим количество палиндромов для каждой матрицы
    }
}

// Функция выбора действия
int choice_func(int n)
{
    int p3 = 0;
    while (1) // Цикл продолжается, пока пользователь не выберет корректный вариант
    {
        printf("\033[1;32mВведите 1, чтобы начать программу заново, любая другая цифра - выход: ");
        rewind(stdin); // Очищаем ввод
        p3 = scanf("%d", &n); // Считываем выбор
        if (p3 != 1) // Если введена не цифра
        {
            printf("\033[1;31mВведите цифру\n");
        }
        else
        {
            break; // Выход из цикла, если выбор правильный
        }
    }
    return n; // Возвращаем выбранный вариант
}

int egor_strlen(char *str) 
{
    char *start = str; // Указатель на начало строки
    while (*str) // Пока текущий символ не равен '\0'
    {
        str++; // Сдвигаем указатель на следующий символ
    }
    return str - start; // Разница между указателями даст длину строки
}

int egor_tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + 32;              // Разница между 'A' и 'a' в ASCII
    }
    return c;                       // Возврат без изменений
}