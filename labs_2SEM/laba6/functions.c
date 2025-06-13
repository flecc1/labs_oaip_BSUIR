/* functions.c */
#include "header.h"

// Выделение памяти для массива строк [используется только при вводе списка предметов]
char** mem_str(int count, int string_length)
{
    char **array = (char**)malloc(count * sizeof(char*));
    if (array == NULL)
    {
        printf("Ошибка выделения памяти для массива строк");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < count; i++)
    {
        *(array + i) = (char*)malloc((string_length + 1) * sizeof(char));
        if (*(array + i) == NULL)
        {
            printf("Ошибка выделения памяти для строки");
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


// Показать таблицу предметов (номер + название)
void showExamTable(char **exam_list, int count)
{
    printf(COLOR_HEADER "\n%-10s%-30s\n" COLOR_RESET, "Number", "Subject");
    for (int i = 0; i < count; i++)
    {
        printf(COLOR_TEXT "%-10d%-30s\n" COLOR_RESET, i + 1, *(exam_list + i));
    }
}


// Ввод данных студентов с экзаменами для обоих семестров.
// Вместо динамических строк используем статические массивы (size = M).
struct student* inputStudentsMulti(int studentCount, int examCount1, char **exam_list1, int examCount2, char **exam_list2)
{
    // *studentCount передаётся в функцию с корректным числом студентов
    struct student *students = (struct student *)malloc((studentCount) * sizeof(struct student));
    if (students == NULL)
    {
        printf("Ошибка выделения памяти для студентов");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < studentCount; i++)
    {
        printf(COLOR_HEADER "\nВвод данных студента %d\n" COLOR_RESET, i + 1);
        /* Очистка буфера перед вводом строк */
        rewind(stdin);

        printf(COLOR_HEADER "Введите фамилию: " COLOR_RESET);
        readString((students + i)->stud.lastname, M);

        printf(COLOR_HEADER "Введите имя: " COLOR_RESET);
        readString((students + i)->stud.name, M);

        printf(COLOR_HEADER "Введите отчество: " COLOR_RESET);
        readString((students + i)->stud.surname, M);

        // Семестр 1: выделяем блок памяти под examCount1 int + examCount1 float (результаты):
        (students + i)->arr[0].exam_number = (int *)malloc(examCount1 * sizeof(int) + examCount1 * sizeof(float));
        if ((students + i)->arr[0].exam_number == NULL)
        {
            printf("Ошибка выделения памяти для данных экзаменов семестра 1");
            exit(EXIT_FAILURE);
        }
        int *exam_numbers1 = (students + i)->arr[0].exam_number;
        float *results1 = ((float*)exam_numbers1) + examCount1;

        printf(COLOR_HEADER "\nВвод данных экзаменов для семестра 1:\n" COLOR_RESET);
        showExamTable(exam_list1, examCount1);
        for (int j = 0; j < examCount1; j++)
        {
            printf(COLOR_HEADER "Введите номер предмета для семестра 1 (от 1 до %d): " COLOR_RESET, examCount1);
            int examIndex = getValidInt(1, examCount1);
            *(exam_numbers1 + j) = examIndex - 1;

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
            *(results1 + j) = res;
            while(getchar() != '\n');
        }

        // Семестр 2: аналогично
        (students + i)->arr[1].exam_number = (int *)malloc(examCount2 * sizeof(int) + examCount2 * sizeof(float));
        if ((students + i)->arr[1].exam_number == NULL)
        {
            printf("Ошибка выделения памяти для данных экзаменов семестра 2");
            exit(EXIT_FAILURE);
        }
        int *exam_numbers2 = (students + i)->arr[1].exam_number;
        float *results2 = ((float*)exam_numbers2) + examCount2;

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
// Фамилия, Имя, Отчество и Предмет – по 30 символов; Оценка – по 10.
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
            exam_numbers = (students + i)->arr[0].exam_number;
            results = (float*)((char*)exam_numbers + examCount * sizeof(int));
        }
        else
        {
            exam_numbers = (students + i)->arr[1].exam_number;
            results = (float*)((char*)exam_numbers + examCount * sizeof(int));
        }
        for (int j = 0; j < examCount; j++)
        {
            printf(COLOR_DATA "%-30s%-30s%-30s%-30s%-10.2f\n" COLOR_RESET, (students + i)->stud.lastname, (students + i)->stud.name,(students + i)->stud.surname,exam_list[ exam_numbers[j] ], *(results + j));
        }
    }
}


// Очистка памяти студентов и списков предметов
void clearMemoryMulti(struct student *students, int studentCount, char **exam_list1, int examCount1, char **exam_list2, int examCount2)
{
    for (int i = 0; i < studentCount; i++)
    {
        free((students + i)->arr[0].exam_number);
        free((students + i)->arr[1].exam_number);
    }
    free(students);

    for (int i = 0; i < examCount1; i++)
    {
        free(*(exam_list1 + i));
    }
    free(exam_list1);

    for (int i = 0; i < examCount2; i++)
    {
        free(*(exam_list2 + i));
    }
    free(exam_list2);
}


// Функция копирует данные выбранного семестра в новый массив студентов (для отображения)
struct student* moveSemesterData(struct student *students, int studentCount, int semester)
{
    struct student *newArray = malloc(studentCount * sizeof(struct student));
    if (newArray == NULL) {
         perror("Ошибка выделения памяти для нового массива студентов");
         exit(EXIT_FAILURE);
    }
    for (int i = 0; i < studentCount; i++) {
         // Скопируем лишь ссылки на строки и номера экзаменов
         memcpy((newArray + i)->stud.lastname, (students + i)->stud.lastname, M);
         memcpy((newArray + i)->stud.name, (students + i)->stud.name,     M);
         memcpy((newArray + i)->stud.surname, (students + i)->stud.surname,  M);
         newArray[i].stud.sem_number = 0;

         // Перемещаем указатель на номер/результат нужного семестра
         (newArray + i)->arr[0].exam_number = students[i].arr[semester - 1].exam_number;
    }
    return newArray;
}


void repeatDisplayFunk(int repeatDisplay, struct student *students, int studentCount, char **exam_list1, char **exam_list2, int examCount1, int examCount2)
{
while (repeatDisplay)
{
    printf(COLOR_HEADER "\nВведите номер семестра для вывода информации (1 или 2, 0 для завершения отображения): " COLOR_RESET);
    int semester = getValidInt(0, 2);
    if (semester == 0)
    break;

    // Определяем список предметов и их количество для выбранного семестра
    char **exam_list = (semester == 1) ? exam_list1 : exam_list2;
    int examCount = (semester == 1) ? examCount1 : examCount2;

    // Если для этого семестра нет ни одного предмета — показываем ошибку
    if (exam_list == NULL || examCount == 0)
    {
    printf(COLOR_TEXT "Ошибка: для семестра %d нет списка предметов! Сначала введите список предметов.\n" COLOR_RESET, semester);
    continue;
    }

    // Если студентов ещё нет вовсе — тоже ошибка
    if (students == NULL || studentCount == 0)
    {
    printf(COLOR_TEXT "Ошибка: нет ни одного студента. Сначала введите данные студентов.\n" COLOR_RESET);
    continue;
    }

    // Проверим, выделена ли память под оценки этого семестра хотя бы для первого студента.
    // (Если она не выделена — значит, данные этого семестра не вводились/не загружались.)
    if (students[0].arr[semester - 1].exam_number == NULL)
    {
    printf(COLOR_TEXT "Ошибка: у студентов нет данных по семестру %d! Сначала введите или загрузите оценки.\n" COLOR_RESET, semester);
    continue;
    }

    // Всё в порядке — копируем указатели на нужный семестр и выводим
    struct student *filteredStudents = moveSemesterData(students, studentCount, semester);

    // showStudentsBySemesterMulti автоматически печатает заголовок и саму таблицу
    showStudentsBySemesterMulti(filteredStudents, studentCount, 1, exam_list, examCount);

    free(filteredStudents);
    }
}




// Вспомогательная функция: убирает пробелы/табуляции/переносы справа
static void rtrim(char *s) 
{
    for (int i = strlen(s) - 1; i >= 0; i--) 
    {
        if (*(s + i) == ' ' || *(s + i) == '\t' || *(s + i) == '\n')
            *(s + i) = '\0';
        else
            break;
    }
}

// ---------------------
//  Сохранение в текстовый файл
// ---------------------
void saveToFile(const char *filename, struct student *students, int studentCount, int semester, char **exam_list, int examCount)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("Не удалось открыть файл \"%s\" для записи\n", filename);
        return;
    }

    for (int i = 0; i < studentCount; i++)
    {
        // Пропускаем первые examCount int’ов, чтобы взять сразу указатель на float’ы
        int *idxs = (students + i)->arr[semester - 1].exam_number;
        float *results = (float *)((char *)idxs + examCount * sizeof(int));

        for (int j = 0; j < examCount; j++)
        {
            // Печатаем ровные 30/30/30/30/10 символов: ФИО, имя, отчество, предмет, оценка
            fprintf(fp, "%-30s" "%-30s" "%-30s" "%-30s" "%-10.2f\n", students[i].stud.lastname, students[i].stud.name, students[i].stud.surname, exam_list[j], results[j]);
        }
    }
    fclose(fp);
    printf("Данные успешно записаны в файл \"%s\".\n", filename);
}


struct student* loadFromFile(const char *filename, int *studentCount, int semester, char **exam_list, int examCount) 
{
    FILE *fp = fopen(filename, "r");
    if (!fp) 
    {
        printf("Не удалось открыть файл \"%s\" для чтения\n", filename);
        *studentCount = 0;
        return NULL;
    }

    // 1) Считаем количество строк
    int totalLines = 0;
    char buf[512];
    while (fgets(buf, sizeof(buf), fp))
        totalLines++;
    if (totalLines == 0 || totalLines % examCount != 0) {
        printf("Файл \"%s\" имеет некорректное число строк (%d) для examCount=%d.\n", filename, totalLines, examCount);
        fclose(fp);
        *studentCount = 0;
        return NULL;
    }

    int cnt = totalLines / examCount;
    *studentCount = cnt;
    rewind(fp);

    // 2) Выделяем массив студентов
    struct student *students = malloc(cnt * sizeof(struct student));
    if (!students) 
    {
        printf("Ошибка выделения памяти для студентов.\n");
        fclose(fp);
        *studentCount = 0;
        return NULL;
    }

    // 3) Для каждого студента выделяем место под examCount int + examCount float
    for (int i = 0; i < cnt; i++) 
    {
        (students + i)->arr[semester - 1].exam_number = malloc(examCount * sizeof(int) + examCount * sizeof(float));
        if (!(students + i)->arr[semester - 1].exam_number) 
        {
            printf("Ошибка выделения памяти для оценок.\n");
            for (int k = 0; k < i; k++)
                free((students + k)->arr[semester - 1].exam_number);
            free(students);
            fclose(fp);
            *studentCount = 0;
            return NULL;
        }
        // Другой семестр обнуляем
        if (semester == 1)
            (students + i)->arr[1].exam_number = NULL;
        else
            (students + i)->arr[0].exam_number = NULL;

        // Обнуляем ФИО
        memset((students + i)->stud.lastname, 0, M);
        memset((students + i)->stud.name, 0, M);
        memset((students + i)->stud.surname, 0, M);
        (students + i)->stud.sem_number = 0;
    }

    // 4) Читаем построчно и заполняем данные
    for (int i = 0; i < cnt; i++) 
    {
        float *results = (float *)((char *)(students + i)->arr[semester - 1].exam_number + examCount * sizeof(int));
        int *exam_numbers = (students + i)->arr[semester - 1].exam_number;

        for (int j = 0; j < examCount; j++) 
        {
            if (!fgets(buf, sizeof(buf), fp)) 
            {
                printf("Неожиданный конец файла на строке %d.\n", i * examCount + j + 1);
                for (int k = 0; k < cnt; k++)
                    free((students + k)->arr[semester - 1].exam_number);
                free(students);
                fclose(fp);
                *studentCount = 0;
                return NULL;
            }

            // Извлекаем ФИО: [0..29] – фамилия, [30..59] – имя, [60..89] – отчество
            char tmp_last[31], tmp_name[31], tmp_sur[31];
            memcpy(tmp_last, buf + 0, 30); tmp_last[30] = '\0';
            memcpy(tmp_name, buf + 30, 30); tmp_name[30] = '\0';
            memcpy(tmp_sur, buf + 60, 30); tmp_sur[30]  = '\0';

            if (j == 0)
            {
                rtrim(tmp_last);
                rtrim(tmp_name);
                rtrim(tmp_sur);
                // Копируем ФИО без
                strncpy((students + i)->stud.lastname, tmp_last, M - 1);
                strncpy((students + i)->stud.name, tmp_name, M - 1);
                strncpy((students + i)->stud.surname,  tmp_sur,  M - 1);
            }

            // Получаем название предмета: [90..119]
            char tmp_subj[31];
            memcpy(tmp_subj, buf + 90, 30);
            tmp_subj[30] = '\0';
            rtrim(tmp_subj);

            // Находим индекс предмета в exam_list
            int foundIndex = 0;
            for (int k = 0; k < examCount; k++) {
                if (strcmp(tmp_subj, exam_list[k]) == 0) {
                    foundIndex = k;
                    break;
                }
            }
            exam_numbers[j] = foundIndex;

            // Считываем оценку с позиции 120
            float grade = 0.0f;
            sscanf(buf + 120, "%f", &grade);
            results[j] = grade;
        }
    }

    fclose(fp);
    printf("Данные успешно загружены из файла \"%s\".\n", filename);
    return students;
}



// Выделение памяти для массива указателей на указатели
char ***mem_exam_list(int semestrCount)
{
    char ***exam_list_array = malloc(semestrCount * sizeof(char **));
    if (!exam_list_array)
    {
        printf("Ошибка выделения памяти для строк.\n");
        return NULL;
    }

    for (int i = 0; i < semestrCount; i++)
    {
        *(exam_list_array + i) = malloc(semestrCount * sizeof(char *));
        if (*(exam_list_array + i) == NULL)
        {
            printf("Ошибка выделения памяти для строк.\n");
            for (int k = 0; k < i; k++) {
                free(*(exam_list_array + k));
            }
            free(exam_list_array);
            return NULL;
        }
        for (int j = 0; j < semestrCount; j++)
        {
            *(*(exam_list_array + i) + j) = NULL;
        }
    }
    return exam_list_array;
}


void clearAllStudents(struct student **students, int *studentCount, int *dataEntered) 
{
    if (*students == NULL) 
    {
        // Нечего освобождать
        return;
    }
    // Для каждого студента освобождаем память под оба семестра, если она выделена
    for (int i = 0; i < *studentCount; i++) 
    {
        if ((*students)[i].arr[0].exam_number) 
        {
            free((*students)[i].arr[0].exam_number);
        }
        if ((*students)[i].arr[1].exam_number) 
        {
            free((*students)[i].arr[1].exam_number);
        }
    }
    // Освобождаем сам массив студентов
    free(*students);
    *students = NULL;
    *studentCount = 0;
    *dataEntered = 0;
}




// Добавляем функцию меню, принимающую ссылки на внешние переменные
void menu(char ***exam_list1, int *examCount1, char ***exam_list2, int *examCount2, struct student **students, int *studentCount, int *dataEntered)
{
    int choice = -1;
    while (choice != 0)
    {
        printf(COLOR_HEADER "\n=== Главное меню ===\n" COLOR_RESET);
        printf(COLOR_TEXT "1) Ввести списки предметов (2 семестра)\n" COLOR_RESET);
        printf(COLOR_TEXT "2) Ввести данные студентов и их оценки\n" COLOR_RESET);
        printf(COLOR_TEXT "3) Показать данные студентов по семестру\n" COLOR_RESET);
        printf(COLOR_TEXT "4) Сохранить данные в файл\n" COLOR_RESET);
        printf(COLOR_TEXT "5) Загрузить данные из файла\n" COLOR_RESET);
        printf(COLOR_TEXT   "6) Удалить всех студентов\n" COLOR_RESET);
        printf(COLOR_TEXT "0) Выйти\n" COLOR_RESET);
        printf(COLOR_HEADER "Ваш выбор: " COLOR_RESET);
        choice = getValidInt(0, 6);
        switch (choice)
        {
            case 1:
            {
                // Если уже были введены старые списки, очищаем их
                if (*exam_list1 != NULL)
                {
                    for (int i = 0; i < *examCount1; i++)
                        free((*exam_list1)[i]);
                    free(*exam_list1);
                    *exam_list1 = NULL;
                    *examCount1 = 0;
                }
                if (*exam_list2 != NULL)
                {
                    for (int i = 0; i < *examCount2; i++)
                        free((*exam_list2)[i]);
                    free(*exam_list2);
                    *exam_list2 = NULL;
                    *examCount2 = 0;
                }

                // Вводим списки предметов
                printf(COLOR_HEADER "\nВвод списка предметов для семестра 1:\n" COLOR_RESET);
                inputExamList(exam_list1, examCount1);
                printf(COLOR_HEADER "\nВвод списка предметов для семестра 2:\n" COLOR_RESET);
                inputExamList(exam_list2, examCount2);

                // Если были введены студенты ранее — очищаем их, т.к. список предметов изменился
                if (*students != NULL)
                {
                    clearMemoryMulti(*students, *studentCount, *exam_list1, *examCount1, *exam_list2, *examCount2);
                    *students = NULL;
                    *studentCount = 0;
                    *dataEntered = 0;
                }
                break;
            }
            case 2:
            {
                if (*exam_list1 == NULL || *exam_list2 == NULL)
                {
                    printf(COLOR_TEXT "Сначала введите списки предметов (пункт 1)!\n" COLOR_RESET);
                    break;
                }
            
                // Спросим, сколько студентов добавить
                printf(COLOR_HEADER "\nСколько студентов добавить? " COLOR_RESET);
                int toAdd = getValidInt(1, INT32_MAX);
            
                // Вызовем inputStudentsMulti, чтобы ввести именно toAdd студентов
                int newCount = toAdd;
                struct student *newStudents = inputStudentsMulti(newCount, *examCount1, *exam_list1, *examCount2, *exam_list2);
                // now newCount == toAdd (если всё прошло успешно)
            
                if (newStudents == NULL || newCount == 0)
                {
                    printf(COLOR_TEXT "Не удалось добавить студентов.\n" COLOR_RESET);
                    break;
                }
            
                if (*students == NULL)
                {
                    // Ранее не было студентов — просто присоединим новый массив
                    *students = newStudents;
                    *studentCount = newCount;
                    *dataEntered = 1;
                }
                else
                {
                    // Уже есть студенты — расширим существующий массив с помощью realloc
                    int oldCount = *studentCount;
                    int total = oldCount + newCount;
            
                    struct student *resized = 
                        realloc(*students, total * sizeof(struct student));
                    if (!resized)
                    {
                        printf(COLOR_TEXT "Ошибка выделения памяти при добавлении студентов.\n" COLOR_RESET);
                        // Освободим временную часть, поскольку она не уйдёт в *students
                        for (int i = 0; i < newCount; i++)
                        {
                            free(newStudents[i].arr[0].exam_number);
                            free(newStudents[i].arr[1].exam_number);
                        }
                        free(newStudents);
                        break;
                    }
                    // Копируем только что введённых студентов в конец:
                    memcpy(resized + oldCount, newStudents, 
                           newCount * sizeof(struct student));
                    free(newStudents);
            
                    *students = resized;
                    *studentCount = total;
                    *dataEntered = 1;
                }
                break;
            }            
            case 3:
            {
                if (!*dataEntered)
                {
                    printf(COLOR_TEXT "Сначала введите данные студентов (пункт 2)!\n" COLOR_RESET);
                    break;
                }
                // Повторный вызов функции отображения: она сама спрашивает семестр
                repeatDisplayFunk(1, *students, *studentCount, *exam_list1, *exam_list2, *examCount1, *examCount2);
                break;
            }
            case 4:
            {
                if (!*dataEntered)
                {
                    printf(COLOR_TEXT "Сначала введите данные студентов (пункт 2)!\n" COLOR_RESET);
                    break;
                }
                printf(COLOR_HEADER "Для какого семестра сохранить данные? (1 или 2): " COLOR_RESET);
                int sem = getValidInt(1, 2);
                printf(COLOR_HEADER "Введите имя файла для сохранения: " COLOR_RESET);
                char filename[256];
                scanf("%255s", filename);
                while(getchar() != '\n');
                if (sem == 1)
                    saveToFile(filename, *students, *studentCount, 1, *exam_list1, *examCount1);
                else
                    saveToFile(filename, *students, *studentCount, 2, *exam_list2, *examCount2);
                break;
            }
            case 5:
            {
                printf(COLOR_HEADER "Для какого семестра загрузить данные? (1 или 2): " COLOR_RESET);
                int sem = getValidInt(1, 2);

                // Проверим, введён ли список предметов для этого семестра
                if ((sem == 1 && *exam_list1 == NULL) ||
                    (sem == 2 && *exam_list2 == NULL))
                {
                    printf(COLOR_TEXT "Невозможно загрузить: сначала введите список предметов для семестра %d (пункт 1)!\n" COLOR_RESET, sem);
                    break;
                }

                // Запрашиваем имя файла
                printf(COLOR_HEADER "Введите имя файла для загрузки: " COLOR_RESET);
                char filename[256];
                scanf("%255s", filename);
                while (getchar() != '\n');

                // Если массива студентов ещё нет, создаём новый массив только для этого семестра:
                if (*students == NULL)
                {
                    // loadFromFile создаёт новый массив структур student и заполняет именно arr[sem-1]
                    *students = loadFromFile(filename, studentCount, sem, (sem == 1) ? *exam_list1 : *exam_list2, (sem == 1) ? *examCount1 : *examCount2);
                    if (*students != NULL && *studentCount > 0)
                    {
                        // Для другого семестра оставим NULL
                        for (int i = 0; i < *studentCount; i++)
                        {
                            if (sem == 1)
                                (*students)[i].arr[1].exam_number = NULL;
                            else
                                (*students)[i].arr[0].exam_number = NULL;
                        }
                        *dataEntered = 1;
                    }
                }
                else
                {
                    // Массив студентов уже есть. Узнаём, сколько сейчас студентов
                    int existingCount = *studentCount;

                    // Загрузим временный массив из файла, чтобы сравнить studentCount
                    int tempCount = 0;
                    struct student *temp = loadFromFile(filename, &tempCount, sem, (sem == 1) ? *exam_list1 : *exam_list2, (sem == 1) ? *examCount1 : *examCount2);

                    if (temp == NULL || tempCount == 0)
                    {
                        // loadFromFile сам вывел сообщение об ошибке
                        break;
                    }
                    // Если число студентов не совпадает — невозможно совместить
                    if (tempCount != existingCount)
                    {
                        printf(COLOR_TEXT "Ошибка: файл содержит %d студентов, а в памяти сейчас %d. Нельзя объединить.\n" COLOR_RESET,
                            tempCount, existingCount);
                        // Освободим временный массив того семестра
                        for (int i = 0; i < tempCount; i++)
                            free(temp[i].arr[sem-1].exam_number);
                        free(temp);
                        break;
                    }

                    // Если для этого семестра данные уже есть — спросим, перезаписать ли
                    if ((*students)[0].arr[sem - 1].exam_number != NULL)
                    {
                        printf(COLOR_TEXT "Данные по семестру %d уже загружены. Перезаписать их? (1 – да, 0 – нет): " COLOR_RESET, sem);
                        int confirm = getValidInt(0, 1);
                        if (confirm == 0)
                        {
                            // Освободим временный массив
                            for (int i = 0; i < tempCount; i++)
                                free(temp[i].arr[sem-1].exam_number);
                            free(temp);
                            break;
                        }
                        // Если перезаписываем – освободим старую память по этому семестру
                        for (int i = 0; i < existingCount; i++)
                        {
                            free((*students)[i].arr[sem - 1].exam_number);
                            (*students)[i].arr[sem - 1].exam_number = NULL;
                        }
                    }

                    // Теперь переносим (перемещаем) указатели из temp в основной массив
                    for (int i = 0; i < existingCount; i++)
                    {
                        (*students)[i].arr[sem - 1].exam_number = temp[i].arr[sem - 1].exam_number;
                        // Копируем ФИО из temp (они совпадают по порядку с (*students))
                        strncpy((*students)[i].stud.lastname, temp[i].stud.lastname, M);
                        strncpy((*students)[i].stud.name, temp[i].stud.name, M);
                        strncpy((*students)[i].stud.surname, temp[i].stud.surname, M);
                    }

                    // Освободим временный массив структур (его память exam_number уже перенесена)
                    free(temp);
                    *dataEntered = 1;
                }
                break;
            }  
            case 6: 
            {
                // 6) «Удалить всех студентов» — вызываем вспомогательную функцию
                if (*students == NULL) {
                    printf(COLOR_TEXT "Нет данных о студентах, нечего удалять.\n" COLOR_RESET);
                } else {
                    clearAllStudents(students, studentCount, dataEntered);
                    printf(COLOR_TEXT "Все студенты удалены.\n" COLOR_RESET);
                }
                break;
            }
            case 0:
            {
                printf(COLOR_HEADER "Завершение программы.\n" COLOR_RESET);
                break;
            }
            default:
                printf(COLOR_TEXT "Некорректный выбор, попробуйте снова.\n" COLOR_RESET);
                break;
        }
    }
}
