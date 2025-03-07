#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>
#define N 100


void Spaces(char *str)
{
    int i, j = 0;
    int space = 0;

    // Пропуск начальных пробелов
    for (i = 0; *(str + i) == ' '; i++);

    // Основной цикл для копирования символов
    while (*(str + i) != '\0') 
    {
        if (*(str + i) == ' ') 
        {
            if (!space) 
            {
                *(str + j++) = ' ';
                space = 1;
            }
        }
        else 
        {
            *(str + j) = *(str + i);
            j ++;
            space = 0;
        }
        i++;
    }

    // Удаление конечных пробелов
    if (j > 0 && *(str + j - 1) == ' ') 
    {
        j--;
    }
    str[j] = '\0';
    printf("Преобразованная последовательность: '%s'\n", str);
}


// Функция для выделения памяти под строку
char *memStr(int n) 
{
    // Выделение памяти для строки длиной n символов плюс 1 для завершающего нулевого символа
    char *str = (char *)malloc((n + 1) * sizeof(char));
    if (str == NULL) 
    {
        
        printf("\033[1;31mОшибка выделения памяти\n");
        return NULL;  // Возвращаем NULL в случае ошибки
    }
    *(str + n) = '\0';  // Добавляем завершающий нулевой символ в конец строки
    return str;  // Возвращаем указатель на выделенную память
}

int strSize(int n)
{
    int p2 = 0;
    while (1) 
    {
        printf("\033[1;32mВведите размер строки: ");
        rewind(stdin);
        p2 = scanf("%d", &n);
        if (p2 != 1) 
        {
            printf("\033[1;31mОшибка, введите цифру\n");
        } 
        else if (n <= 0 || n >= N) 
        {
            printf("\033[1;31mЧисло должно быть больше 0 и до %d\n", N);
        } 
        else 
        {
            break;
        }
    }
    return n;
}

// Удаление символа новой строки
void delSYM(char *str, int n)
{
    for (int i = 0; i < n + 1; i++) 
    {
        if (*(str + i) == '\n') 
        {
            *(str + i) = '\0';
            break;
        }
    }
}
 
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
    }
    return n;
}

// Функция для очистки памяти одномерного динамического массива
void clearStr(char *array) 
{
    // Проверяем, что указатель не является NULL
    if (array != NULL) 
    {
        // Освобождаем память
        free(array);
    }
    else 
    {
        printf("Указатель уже является NULL.\n");
    }
}

void vvod(char *str, int n)
{
    while (1)
    {
        printf("\033[1;32mВведите последовательность символов (не более %d символов): ", n);
        rewind(stdin);
        fgets(str, n + 2, stdin);  // Читаем на 1 символ больше, чтобы проверить превышение длины
        delSYM(str, n + 1);  // Убираем символ новой строки, если он есть
        
        // Проверяем, если строка слишком длинная
        if (strlen(str) > n)
        {
            printf("\033[1;31mОшибка: строка слишком большая. Максимальная длина - %d символов.\n", n);
        }
        else
        {
            break;
        }
    }
}

void randVvod(char *str, int n)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    int charset_size = sizeof(charset) - 1; // Размер набора символов (без завершающего нуля)
    
    for (int i = 0; i < n; i++)
    {
        *(str + i) = *(charset + (rand() % charset_size)); // Случайный символ из набора
    }
    *(str + n) = '\0'; // Завершающий нуль
    printf("\033[1;32mСгенерированная строка: '%s'\n", str);
}

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