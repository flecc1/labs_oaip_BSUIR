#include "header.h"


char** mem_str(int count, int string_length)
{
    char **array = (char**)malloc(count * sizeof(char*));
    if (array == NULL)
    {
        perror("Ошибка выделения памяти для массива строк");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < count; i++)
    {
        *(array + i) = (char*)malloc((string_length + 1) * sizeof(char));
        if (*(array + i) == NULL)
        {
            perror("Ошибка выделения памяти для строки");
            exit(EXIT_FAILURE);
        }
    }
    return array;
}

// Функция ввода списка предметов
void inputExamList(char ***exam_list, int *examCount)
{
    printf(COLOR_HEADER "\nВведите количество предметов: " COLOR_RESET);
    *examCount = getValidInt(1, INT32_MAX);
    
    *exam_list = mem_str(*examCount, N);
    
    printf(COLOR_HEADER "\nВведите список предметов:\n" COLOR_RESET);
    for (int i = 0; i < *examCount; i++)
    {
        printf(COLOR_HEADER "Предмет %d: " COLOR_RESET, i + 1);
        readString(*((*exam_list) + i), N);
    }
}


void showExamTable(char **exam_list, int count)
{
    printf(COLOR_HEADER "\n%-10s%-30s\n" COLOR_RESET, "Number", "Subject");
    for (int i = 0; i < count; i++)
    {
        printf(COLOR_TEXT "%-10d%-30s\n" COLOR_RESET, i + 1, *(exam_list + i));
    }
}


// Функция ввода данных студентов с экзаменами для обоих семестров.
// Для каждого студента вводятся номера предметов и результаты для семестра 1 и семестра 2.
// Результаты вводятся в диапазоне от 0 до 10.
struct student* inputStudentsMulti(int *studentCount, int examCount1, char **exam_list1, int examCount2, char **exam_list2)
{
    struct student *students = (struct student *)malloc((*studentCount) * sizeof(struct student));
    if (students == NULL)
    {
        perror("Ошибка выделения памяти для студентов");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < *studentCount; i++)
    {
        printf(COLOR_HEADER "\nВвод данных студента %d\n" COLOR_RESET, i + 1);
        
        (*(students + i)).stud.lastname = (char *)malloc(N * sizeof(char));
        (*(students + i)).stud.name     = (char *)malloc(N * sizeof(char));
        (*(students + i)).stud.surname  = (char *)malloc(N * sizeof(char));
        if ((*(students + i)).stud.lastname == NULL ||
            (*(students + i)).stud.name == NULL ||
            (*(students + i)).stud.surname == NULL)
        {
            perror("Ошибка выделения памяти для строк студента");
            exit(EXIT_FAILURE);
        }

        /* Очистка буфера перед вводом строк */
        rewind(stdin);

        printf(COLOR_HEADER "Введите фамилию: " COLOR_RESET);
        readString((*(students + i)).stud.lastname, N);
        (*(students + i)).stud.lastname = optimizeString((*(students + i)).stud.lastname);

        printf(COLOR_HEADER "Введите имя: " COLOR_RESET);
        readString((*(students + i)).stud.name, N);
        (*(students + i)).stud.name = optimizeString((*(students + i)).stud.name);

        printf(COLOR_HEADER "Введите отчество: " COLOR_RESET);
        readString((*(students + i)).stud.surname, N);
        (*(students + i)).stud.surname = optimizeString((*(students + i)).stud.surname);

        /* Поле sem_number не используется в новой логике – устанавливаем в 0 */
        (*(students + i)).stud.sem_number = 0;
        
        /* Выделяем память для экзаменов семестра 1 (один блок для int и float) */
        (*(students + i)).arr[0].exam_number = (int *)malloc(examCount1 * sizeof(int) + examCount1 * sizeof(float));
        if ((*(students + i)).arr[0].exam_number == NULL)
        {
            perror("Ошибка выделения памяти для данных экзаменов семестра 1");
            exit(EXIT_FAILURE);
        }
        int *exam_numbers = (*(students + i)).arr[0].exam_number;
        /* Используем арифметику указателей с приведением к float* */
        float *results = ((float*)exam_numbers) + examCount1;
        
        /* Ввод данных экзаменов для семестра 1 */
        printf(COLOR_HEADER "\nВвод данных экзаменов для семестра 1:\n" COLOR_RESET);
        showExamTable(exam_list1, examCount1);
        for (int j = 0; j < examCount1; j++)
        {
            printf(COLOR_HEADER "Введите номер предмета для семестра 1 (от 1 до %d): " COLOR_RESET, examCount1);
            int examIndex = getValidInt(1, examCount1);
            *(exam_numbers + j) = examIndex - 1;
            
            float res;
            printf(COLOR_HEADER "Введите результат экзамена для предмета \"%s\" (от 0 до 10): " COLOR_RESET,
            *(exam_list1 + examIndex - 1));
            while (1)
            {
                if (scanf("%f", &res) == 1 && res >= 0 && res <= 10)
                    break;
                else
                {
                    printf(COLOR_TEXT "Ошибка ввода! Введите вещественное число от 0 до 10: " COLOR_RESET);
                    while(getchar() != '\n');
                }
            }
            *(results + j) = res;
            while(getchar() != '\n');
        }
        
        /* Выделяем память для экзаменов семестра 2 (один блок для int и float) */
        (*(students + i)).arr[1].exam_number = (int *)malloc(examCount2 * sizeof(int) + examCount2 * sizeof(float));
        if ((*(students + i)).arr[1].exam_number == NULL)
        {
            perror("Ошибка выделения памяти для данных экзаменов семестра 2");
            exit(EXIT_FAILURE);
        }
        int *exam_numbers2 = (*(students + i)).arr[1].exam_number;
        /* Аналогично вычисляем указатель на результаты без приведения к (char*) */
        float *results2 = ((float*)exam_numbers2) + examCount2;
        
        /* Ввод данных экзаменов для семестра 2 */
        printf(COLOR_HEADER "\nВвод данных экзаменов для семестра 2:\n" COLOR_RESET);
        showExamTable(exam_list2, examCount2);
        for (int j = 0; j < examCount2; j++)
        {
            printf(COLOR_HEADER "Введите номер предмета для семестра 2 (от 1 до %d): " COLOR_RESET, examCount2);
            int examIndex = getValidInt(1, examCount2);
            *(exam_numbers2 + j) = examIndex - 1;
            
            float res;
            printf(COLOR_HEADER "Введите результат экзамена для предмета \"%s\" (от 0 до 10): " COLOR_RESET,
                   *(exam_list2 + examIndex - 1));
            while (1)
            {
                if (scanf("%f", &res) == 1 && res >= 0 && res <= 10)
                    break;
                else
                {
                    printf(COLOR_TEXT "Ошибка ввода! Введите вещественное число от 0 до 10: " COLOR_RESET);
                    while(getchar() != '\n');
                }
            }
            *(results2 + j) = res;
            while(getchar() != '\n');
        }
    }
    return students;
}


// Функция вывода данных студентов по выбранному семестру (1 или 2)
// Таблица выводится с использованием пробелов, все столбцы выровнены по левому краю.
// Фамилия, Имя, Отчество и Предмет – по 40 символов; Оценка – по 10.
void showStudentsBySemesterMulti(struct student *students, int studentCount, int semester, char **exam_list, int examCount)
{
    printf(COLOR_HEADER "\nСписок студентов за семестр %d:\n" COLOR_RESET, semester);
    printf(COLOR_HEADER "%-30s%-30s%-30s%-30s%-10s\n" COLOR_RESET, "Lastnamae", "Name", "Surname", "Subject", "Result");
    
    for (int i = 0; i < studentCount; i++)
    {
        int *exam_numbers;
        float *results;
        if (semester == 1)
        {
            exam_numbers = (*(students + i)).arr[0].exam_number;
            results = (float*)((char*)exam_numbers + examCount * sizeof(int));
        }
        else
        {
            exam_numbers = (*(students + i)).arr[1].exam_number;
            results = (float*)((char*)exam_numbers + examCount * sizeof(int));
        }
        for (int j = 0; j < examCount; j++)
        {
            printf(COLOR_DATA "%-30s%-30s%-30s%-30s%-10.2f\n" COLOR_RESET,
                   (*(students + i)).stud.lastname,
                   (*(students + i)).stud.name,
                   (*(students + i)).stud.surname,
                   *(exam_list + *(exam_numbers + j)),
                   *(results + j));
        }
    }
}

// Функция очистки памяти для студентов и списков предметов
void clearMemoryMulti(struct student *students, int studentCount, char **exam_list1, int examCount1, char **exam_list2, int examCount2)
{
    for (int i = 0; i < studentCount; i++)
    {
        free((*(students + i)).stud.lastname);
        free((*(students + i)).stud.name);
        free((*(students + i)).stud.surname);

        free((*(students + i)).arr[0].exam_number);
        free((*(students + i)).arr[1].exam_number);
    }
    free(students);
    
    for (int i = 0; i < examCount1; i++)
    {
        if (*(exam_list1 + i))
            free(*(exam_list1 + i));
    }
    free(exam_list1);
    
    for (int i = 0; i < examCount2; i++)
    {
        if (*(exam_list2 + i))
            free(*(exam_list2 + i));
    }
    free(exam_list2);
}

void repeatDisplayFunk(int repeatDisplay, struct student *students, int studentCount, char **exam_list1, char **exam_list2, int examCount1, int examCount2)
{
    while(repeatDisplay)
    {
        printf(COLOR_HEADER "\nВведите номер семестра для вывода информации (1 или 2, 0 для завершения отображения): " COLOR_RESET);
        int semester = getValidInt(0, 2);
        if(semester == 0)
            break;
        if (semester == 1)
            showStudentsBySemesterMulti(students, studentCount, 1, exam_list1, examCount1);
        else
            showStudentsBySemesterMulti(students, studentCount, 2, exam_list2, examCount2);
    }   
}


char ***mem_exam_list(int semestrCount)
{
    // Выделяем память для массива указателей на указатели (размер: semestrCount)
    char ***exam_list_array = malloc(semestrCount * sizeof(char **));
    if (!exam_list_array)
    {
        printf("Ошибка выделения памяти для строк.\n");
        return NULL;
    }

    // Для каждого элемента первого измерения выделяем память для второго измерения
    for (int i = 0; i < semestrCount; i++)
    {
        *(exam_list_array + i) = malloc(semestrCount * sizeof(char *));
        if (*(exam_list_array + i) == NULL)
        {
            printf("Ошибка выделения памяти для строк.\n");
            // Освобождаем ранее выделенную память
            for (int k = 0; k < i; k++) {
                free(*(exam_list_array + k));
            }
            free(exam_list_array);
            return NULL;
        }
        // Инициализируем каждый указатель третьего измерения значением NULL
        for (int j = 0; j < semestrCount; j++)
        {
            *(*(exam_list_array + i) + j) = NULL;
        }
    }
    return exam_list_array;
}
