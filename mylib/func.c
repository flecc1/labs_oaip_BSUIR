#include "header_Lib.h"

// функция для получения int от min до max
int getValidInt(int min, int max)
{
    int num;
    while (1)
    {
        if (scanf("%d", &num) == 1 && num >= min && num <= max)
        {
            while(getchar() != '\n'); // очистка буфера ввода
            return num;
        }
        else
        {
            printf("Ошибка! Введите число от %d до %d: ", min, max);
            while(getchar() != '\n');
        }
    }
}

// функция для получения float от min до max
float getValidFloat(int min, int max)
{
    float num;
    
    while (1)
    {
        if (scanf("%f", &num) == 1 && num >= min && num <= max)
        {
            rewind(stdin); // Очистка ввода с использованием rewind(stdin)
            return num;
        }
        else
        {
            printf("Ошибка! Введите число от %d до %d: ", min, max);
            rewind(stdin); // Очистка ввода перед повторной попыткой
        }
    }
}

// функция для считывая динамической с перераспределением памяти строки
void getValidString(char **str)
{
    char c;
    int size = 1;
    
    *str = (char *)malloc(size * sizeof(char));
    if (*str == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }

    char *ptr = *str;

    while ((c = getchar()) == '\n'); // Пропускаем пустую строку

    while (c != '\n' && c != EOF)
    {
        *ptr = c;
        ptr++;
        size++;

        // Используем временный указатель для безопасного realloc
        char *temp = (char *)realloc(*str, size * sizeof(char));
        if (temp == NULL)
        {
            printf("Ошибка выделения памяти при перераспределении!\n");
            free(*str);
            exit(1);
        }

        // Обновляем указатель str и корректируем ptr
        ptr = temp + (ptr - *str);
        *str = temp;

        c = getchar();
    }
    *ptr = '\0'; // Завершаем строку нулевым символом

    rewind(stdin);
}

//функция для считывания сторки в буфер длиной length
void readString(char *buffer, int max_length)
{
    if (fgets(buffer, max_length, stdin) != NULL)
    {
        int i = 0;
        while (*(buffer + i) != '\0')
        {
            if (*(buffer + i) == '\n')
            {
                *(buffer + i) = '\0';
                break;
            }
            i++;
        }
        rewind(stdin);
    }
}


//функция для подсчета длины строки 
int my_strlen(const char *s)
{
    int len = 0;
    while (*(s + len) != '\0')
        len++;
    return len;
}


//функция для перераспределения памяти для динамической строки
char* optimizeString(char *str)
{
    int len = my_strlen(str);
    char *temp = (char*)realloc(str, (len + 1) * sizeof(char));
    if (temp == NULL)
        return str;
    return temp;
}


// //фунция для выделения памяти по массив строк 
// char** mem_str(int count, int string_length)
// {
//     char **array = (char**)malloc(count * sizeof(char*));
//     if (array == NULL)
//     {
//         perror("Ошибка выделения памяти для массива строк");
//         exit(EXIT_FAILURE);
//     }
//     for (int i = 0; i < count; i++)
//     {
//         *(array + i) = (char*)malloc((string_length + 1) * sizeof(char));
//         if (*(array + i) == NULL)
//         {
//             perror("Ошибка выделения памяти для строки");
//             exit(EXIT_FAILURE);
//         }
//     }
//     return array;
// }


// Функция для выбора рестарта программы
int restart_choice_func(int n)
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