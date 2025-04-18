#include "header.h"

// Функция выделения памяти для массива строк (адресная арифметика используется для доступа к элементам)
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

// Ввод списка предметов (доступ к элементам через адресную арифметику)
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

// Вывод таблицы предметов (при выборе элементов используется арифметика указателей)
void showExamTable(char **exam_list, int count)
{
    printf(COLOR_HEADER "\n%-10s%-30s\n" COLOR_RESET, "Number", "Subject");
    for (int i = 0; i < count; i++) 
    {
        printf(COLOR_TEXT "%-10d%-30s\n" COLOR_RESET, i + 1, *(exam_list + i));
    }
}

// Создание очереди студентов с параметром initialStudent.
struct StudentQueue* createStudentQueue(struct student *initialStudent)
{
    struct StudentQueue *q = (struct StudentQueue*)malloc(sizeof(struct StudentQueue));
    if (q == NULL) 
    {
        printf("Ошибка выделения памяти для очереди студентов\n");
        exit(EXIT_FAILURE);
    }
    if (initialStudent != NULL) 
    {
        struct StudentNode *node = (struct StudentNode*)malloc(sizeof(struct StudentNode));
        if (node == NULL) 
        {
            printf("Ошибка выделения памяти для узла очереди\n");
            exit(EXIT_FAILURE);
        }
        node->data = *initialStudent;
        node->next = NULL;
        q->front = q->rear = node;
        q->count = 1;
    } else 
    {
        q->front = q->rear = NULL;
        q->count = 0;
    }
    return q;
}

// Добавление студента в конец очереди
void enqueueStudent(struct StudentQueue *q, struct student s)
{
    struct StudentNode *newNode = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    if (newNode == NULL)
    {
        printf("Ошибка выделения памяти для узла очереди\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = s;
    newNode->next = NULL;
    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
    } else 
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

// Освобождение памяти всей очереди (данные студентов освобождаются)
void freeStudentQueue(struct StudentQueue *q)
{
    struct StudentNode *current = q->front;
    while (current)
    {
        struct StudentNode *temp = current;
        free(temp->data.stud.lastname);
        free(temp->data.stud.name);
        free(temp->data.stud.surname);
        free(temp->data.arr[0].exam_number);
        free(temp->data.arr[1].exam_number);
        current = current->next;
        free(temp);
    }
    free(q);
}

// Освобождение памяти очереди только для узлов (данные студентов остаются)
void freeStudentQueueShallow(struct StudentQueue *q)
{
    struct StudentNode *current = q->front;
    while (current)
    {
        struct StudentNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(q);
}





// Ввод одного студента с экзаменами для двух семестров.
struct student inputSingleStudent(int examCount1, char **exam_list1, int examCount2, char **exam_list2)
{
    struct student s;
    printf(COLOR_HEADER "\nВвод данных студента\n" COLOR_RESET);
    
    s.stud.lastname = (char*)malloc(N * sizeof(char));
    s.stud.name     = (char*)malloc(N * sizeof(char));
    s.stud.surname  = (char*)malloc(N * sizeof(char));
    if (s.stud.lastname == NULL || s.stud.name == NULL || s.stud.surname == NULL)
    {
        printf("Ошибка выделения памяти для строк студента");
        exit(EXIT_FAILURE);
    }
    
    rewind(stdin);
    
    printf(COLOR_HEADER "Введите фамилию: " COLOR_RESET);
    readString(s.stud.lastname, N);
    s.stud.lastname = optimizeString(s.stud.lastname);
    
    printf(COLOR_HEADER "Введите имя: " COLOR_RESET);
    readString(s.stud.name, N);
    s.stud.name = optimizeString(s.stud.name);
    
    printf(COLOR_HEADER "Введите отчество: " COLOR_RESET);
    readString(s.stud.surname, N);
    s.stud.surname = optimizeString(s.stud.surname);
    
    s.stud.sem_number = 0;
    
    // Для семестра 1 выделяем память; доступ к элементам осуществляется через арифметику указателей.
    s.arr[0].exam_number = (int*)malloc(examCount1 * sizeof(int) + examCount1 * sizeof(float));
    if (s.arr[0].exam_number == NULL)
    {
        printf("Ошибка выделения памяти для данных экзаменов семестра 1");
        exit(EXIT_FAILURE);
    }
    int *exam_numbers = s.arr[0].exam_number;
    float *results = ((float*)exam_numbers) + examCount1;
    
    printf(COLOR_HEADER "\nВвод данных экзаменов для семестра 1:\n" COLOR_RESET);
    showExamTable(exam_list1, examCount1);
    for (int j = 0; j < examCount1; j++)
    {
        printf(COLOR_HEADER "Введите номер предмета для семестра 1 (от 1 до %d): " COLOR_RESET, examCount1);
        int examIndex = getValidInt(1, examCount1);
        *(exam_numbers + j) = examIndex - 1;
        
        float res;
        printf(COLOR_HEADER "Введите результат экзамена для предмета \"%s\" (от 0 до 10): " COLOR_RESET,
               *(exam_list1 + (examIndex - 1)));
        while (1) 
        {
            if (scanf("%f", &res) == 1 && res >= 0 && res <= 10)
                break;
            else {
                printf(COLOR_TEXT "Ошибка ввода! Введите вещественное число от 0 до 10: " COLOR_RESET);
                while(getchar() != '\n');
            }
        }
        *(results + j) = res;
        while(getchar() != '\n');
    }
    
    // Для семестра 2 аналогично
    s.arr[1].exam_number = (int*)malloc(examCount2 * sizeof(int) + examCount2 * sizeof(float));
    if (s.arr[1].exam_number == NULL) 
    {
        printf("Ошибка выделения памяти для данных экзаменов семестра 2");
        exit(EXIT_FAILURE);
    }
    int *exam_numbers2 = s.arr[1].exam_number;
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
               *(exam_list2 + (examIndex - 1)));
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
    return s;
}

// Функция ввода студентов с экзаменационными оценками для двух семестров
struct StudentQueue* inputStudentsMulti(int *studentCount, int examCount1, char **exam_list1, int examCount2, char **exam_list2)
{
    printf(COLOR_HEADER "\nВведите количество студентов: " COLOR_RESET);
    *studentCount = getValidInt(1, INT32_MAX);
    
    struct StudentQueue *queue = createStudentQueue(NULL);
    for (int i = 0; i < *studentCount; i++)
    {
        struct student s = inputSingleStudent(examCount1, exam_list1, examCount2, exam_list2);
        enqueueStudent(queue, s);
    }
    return queue;
}

// Функция вывода студентов за выбранный семестр.
void showStudentsBySemesterMulti(struct StudentQueue *q, int semester, char **exam_list, int examCount)
{
    printf(COLOR_HEADER "\nСписок студентов за семестр %d:\n" COLOR_RESET, semester);
    printf(COLOR_HEADER "%-30s%-30s%-30s%-30s%-10s\n" COLOR_RESET,
           "Lastnamae", "Name", "Surname", "Subject", "Result");
    
    struct StudentNode *current = q->front;
    while (current) {
        int *exam_numbers;
        float *results;
        // В новой очереди все данные экзаменов записаны в arr[0]
        exam_numbers = current->data.arr[0].exam_number;
        results = (float*)((char*)exam_numbers + examCount * sizeof(int));
        for (int j = 0; j < examCount; j++) {
            printf(COLOR_DATA "%-30s%-30s%-30s%-30s%-10.2f\n" COLOR_RESET,
                   current->data.stud.lastname,
                   current->data.stud.name,
                   current->data.stud.surname,
                   *(exam_list + *(exam_numbers + j)),
                   *(results + j));
        }
        current = current->next;
    }
}

// Функция moveSemesterData создает новую очередь для выбранного семестра.
struct StudentQueue* moveSemesterData(struct StudentQueue *q, int semester)
{
    struct StudentQueue *newQueue = createStudentQueue(NULL);
    struct StudentNode *current = q->front;
    while (current)
    {
        struct student newStudent;
        newStudent.stud.lastname = current->data.stud.lastname;
        newStudent.stud.name     = current->data.stud.name;
        newStudent.stud.surname  = current->data.stud.surname;
        newStudent.stud.sem_number = current->data.stud.sem_number;
        // Копируем данные экзаменов выбранного семестра в arr[0]
        newStudent.arr[0].exam_number = (semester == 1) ? current->data.arr[0].exam_number : current->data.arr[1].exam_number;
        newStudent.arr[1].exam_number = NULL;
        enqueueStudent(newQueue, newStudent);
        current = current->next;
    }
    return newQueue;
}

// Отдельная функция добавления студента.
// После добавления вызывается вывод обновлённой информации для обоих семестров.
void addStudent(struct StudentQueue *q, int examCount1, char **exam_list1, int examCount2, char **exam_list2)
{
    struct student s = inputSingleStudent(examCount1, exam_list1, examCount2, exam_list2);
    enqueueStudent(q, s);
    printf("Студент успешно добавлен.\n");
    // Вывод обновлённой информации за первый семестр
    struct StudentQueue *filtered1 = moveSemesterData(q, 1);
    printf(COLOR_HEADER "\nИнформация за первый семестр:\n" COLOR_RESET);
    showStudentsBySemesterMulti(filtered1, 1, exam_list1, examCount1);
    freeStudentQueueShallow(filtered1);
    // Вывод обновлённой информации за второй семестр
    struct StudentQueue *filtered2 = moveSemesterData(q, 2);
    printf(COLOR_HEADER "\nИнформация за второй семестр:\n" COLOR_RESET);
    showStudentsBySemesterMulti(filtered2, 2, exam_list2, examCount2);
    freeStudentQueueShallow(filtered2);
}

// Отдельная функция удаления студента по фамилии.
int removeStudent(struct StudentQueue *q, char *lastname)
{
    struct StudentNode *current = q->front;
    struct StudentNode *prev = NULL;
    while (current != NULL)
    {
        if (strcmp(current->data.stud.lastname, lastname) == 0)
        {
            if (prev == NULL) //удаляем первого в очереди
            {
                q->front = current->next;
                if (q->rear == current) //Убираем текущий узел из начала очереди
                    q->rear = NULL;
            } else                          //удаляем из середины или конца
            {
                prev->next = current->next;     //Пропускаем current, «перешивая» список — prev теперь указывает на следующий за current
                if (q->rear == current)         //Если удаляемый узел — последний (rear), то rear нужно сдвинуть назад на prev
                    q->rear = prev;
            }
            free(current->data.stud.lastname);
            free(current->data.stud.name);
            free(current->data.stud.surname);
            free(current->data.arr[0].exam_number);
            free(current->data.arr[1].exam_number);
            free(current);
            q->count--;
            printf("Студент успешно удалён.\n");
            return 1;
        }
        prev = current;
        current = current->next;
    }
    printf("Студент с фамилией %s не найден.\n", lastname);
    return 0;
}

// Функция для вывода информации о конкретном студенте (по обоим семестрам)
void displayStudentInfo(struct student *s, char **exam_list1, int examCount1, char **exam_list2, int examCount2)
{
    printf(COLOR_HEADER "\nИнформация о студенте: %s %s %s\n" COLOR_RESET,
           s->stud.lastname, s->stud.name, s->stud.surname);
    
    // Вывод данных за первый семестр
    if (s->arr[0].exam_number != NULL)
    {
        int *exam_numbers1 = s->arr[0].exam_number;
        float *results1 = (float*)((char*)exam_numbers1 + examCount1 * sizeof(int));
        printf(COLOR_HEADER "\nДанные за первый семестр:\n" COLOR_RESET);
        printf(COLOR_HEADER "%-30s%-30s%-30s%-30s%-10s\n" COLOR_RESET,
           "Lastnamae", "Name", "Surname", "Subject", "Result");
        for (int j = 0; j < examCount1; j++)
        {
         printf(COLOR_DATA "%-30s%-30s%-30s%-30s%-10.2f\n" COLOR_RESET,
                s->stud.lastname,
                s->stud.name,
                s->stud.surname,
                *(exam_list1 + *(exam_numbers1 + j)),
                *(results1 + j));
    }
    } else 
    {
        printf(COLOR_TEXT "\nНет данных за первый семестр.\n" COLOR_RESET);
    }
    
    // Вывод данных за второй семестр
    if (s->arr[1].exam_number != NULL)
    {
        int *exam_numbers2 = s->arr[1].exam_number;
        float *results2 = (float*)((char*)exam_numbers2 + examCount2 * sizeof(int));
        printf(COLOR_HEADER "\nДанные за второй семестр:\n" COLOR_RESET);
        printf(COLOR_HEADER "%-30s%-30s%-30s%-30s%-10s\n" COLOR_RESET,
            "Lastnamae", "Name", "Surname", "Subject", "Result");
        for (int j = 0; j < examCount1; j++)
        {
            printf(COLOR_DATA "%-30s%-30s%-30s%-30s%-10.2f\n" COLOR_RESET,
            s->stud.lastname,
            s->stud.name,
            s->stud.surname,
            *(exam_list2 + *(exam_numbers2 + j)),
            *(results2 + j));
        }    
    }
    else
    {
        printf(COLOR_TEXT "\nНет данных за второй семестр.\n" COLOR_RESET);
    }
}

// Отдельная функция поиска студента по фамилии.
// Для каждого найденного студента выводится информация по обоим семестрам.
void findStudent(struct StudentQueue *q, char *lastname, char **exam_list1, int examCount1, char **exam_list2, int examCount2)
{
    struct StudentNode *current = q->front;
    int found = 0;
    while (current)
    {
        if (strcmp(current->data.stud.lastname, lastname) == 0)
        {
            displayStudentInfo(&(current->data), exam_list1, examCount1, exam_list2, examCount2);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
    {
        printf(COLOR_TEXT "\nСтудент с фамилией %s не найден.\n" COLOR_RESET, lastname);
    }
}

// Функция repeatDisplayFunk позволяет неограниченное число раз выполнять операции над очередью студентов.
// Меню включает: вывод информации за первый/второй семестр, добавление, удаление, поиск ученика и выход в главное меню.
void repeatDisplayFunk(struct StudentQueue *q, char **exam_list1, char **exam_list2, int examCount1, int examCount2)
{
    int exitInner = 0;
    while (!exitInner)
    {
        printf(COLOR_HEADER "\nМеню: \n" COLOR_RESET);
        printf("1. Вывод информации за первый семестр\n");
        printf("2. Вывод информации за второй семестр\n");
        printf("3. Добавить ученика\n");
        printf("4. Удалить ученика по фамилии\n");
        printf("5. Найти ученика по фамилии\n");
        printf("6. Выход в главное меню\n");
        printf("Выберите пункт: ");
        int choice = getValidInt(1, 6);
        switch (choice)
        {
            case 1: 
            {
                struct StudentQueue *filtered = moveSemesterData(q, 1);
                showStudentsBySemesterMulti(filtered, 1, exam_list1, examCount1);
                freeStudentQueueShallow(filtered);
                break;
            }
            case 2: 
            {
                struct StudentQueue *filtered = moveSemesterData(q, 2);
                showStudentsBySemesterMulti(filtered, 2, exam_list2, examCount2);
                freeStudentQueueShallow(filtered);
                break;
            }
            case 3: 
            {
                addStudent(q, examCount1, exam_list1, examCount2, exam_list2);
                break;
            }
            case 4: 
            {
                char lastname[N];
                printf("Введите фамилию для удаления: ");
                readString(lastname, N);
                removeStudent(q, lastname);
                break;
            }
            case 5: 
            {
                char lastname[N];
                printf("Введите фамилию для поиска: ");
                readString(lastname, N);
                findStudent(q, lastname, exam_list1, examCount1, exam_list2, examCount2);
                break;
            }
            case 6:
            {
                exitInner = 1;
                break;
            }
        }
    }
}

// Функция очистки памяти для списков предметов (при доступе к элементам используется адресная арифметика)
void clearExamLists(char **exam_list1, int examCount1, char **exam_list2, int examCount2) 
{
    int i;
    for (i = 0; i < examCount1; i++)
    {
        if (*(exam_list1 + i))
            free(*(exam_list1 + i));
    }
    free(exam_list1);
    
    for (i = 0; i < examCount2; i++)
    {
        if (*(exam_list2 + i))
            free(*(exam_list2 + i));
    }
    free(exam_list2);
}

void showMainMenu(struct StudentQueue *queue, char **exam_list1, int examCount1, char **exam_list2, int examCount2)
{
    repeatDisplayFunk(queue, exam_list1, exam_list2, examCount1, examCount2);
}