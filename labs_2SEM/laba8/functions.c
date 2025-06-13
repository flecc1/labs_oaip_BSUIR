#include "header.h"

char **mem_str(int count, int string_length) {
    char **array = (char **)malloc(count * sizeof(char *));
    if (array == NULL) {
        printf("Ошибка выделения памяти для массива строк");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < count; i++) {
        array[i] = (char *)malloc((string_length + 1) * sizeof(char));
        if (array[i] == NULL) {
            printf("Ошибка выделения памяти для строки");
            exit(EXIT_FAILURE);
        }
    }
    return array;
}

void inputExamList(char ***exam_list, int *examCount) {
    printf(COLOR_HEADER "\nВведите количество предметов: " COLOR_RESET);
    *examCount = getValidInt(1, INT32_MAX);

    *exam_list = mem_str(*examCount, N);

    printf(COLOR_HEADER "\nВведите список предметов:\n" COLOR_RESET);
    for (int i = 0; i < *examCount; i++) {
        printf(COLOR_HEADER "Предмет %d: " COLOR_RESET, i + 1);
        readString((*exam_list)[i], N);
    }
}

void showExamTable(char **exam_list, int count) {
    printf(COLOR_HEADER "\n%-10s%-30s\n" COLOR_RESET, "Number", "Subject");
    for (int i = 0; i < count; i++) {
        printf(COLOR_TEXT "%-10d%-30s\n" COLOR_RESET, i + 1, exam_list[i]);
    }
}

struct StudentQueue *createStudentQueue(struct student *initialStudent) {
    struct StudentQueue *q = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
    if (q == NULL) {
        printf("Ошибка выделения памяти для очереди студентов\n");
        exit(EXIT_FAILURE);
    }
    if (initialStudent != NULL) {
        struct StudentNode *node = (struct StudentNode *)malloc(sizeof(struct StudentNode));
        if (node == NULL) {
            printf("Ошибка выделения памяти для узла очереди\n");
            exit(EXIT_FAILURE);
        }
        node->data = *initialStudent;
        node->next = NULL;
        q->front = q->rear = node;
        q->count = 1;
    }
    else {
        q->front = q->rear = NULL;
        q->count = 0;
    }
    return q;
}

void enqueueStudent(struct StudentQueue *q, struct student s) {
    struct StudentNode *newNode = (struct StudentNode *)malloc(sizeof(struct StudentNode));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти для узла очереди\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = s;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

void freeStudentQueue(struct StudentQueue *q) {
    if (q == NULL) return;
    
    struct StudentNode *current = q->front;
    while (current) {
        struct StudentNode *temp = current;
        if (temp->data.arr[0].exam_number) {
            free(temp->data.arr[0].exam_number);
        }
        if (temp->data.arr[1].exam_number) {
            free(temp->data.arr[1].exam_number);
        }
        current = current->next;
        free(temp);
    }
    free(q);
}

void freeStudentQueueShallow(struct StudentQueue *q) {
    if (q == NULL) return;
    
    struct StudentNode *current = q->front;
    while (current) {
        struct StudentNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(q);
}

void clearExamList(char **list, int count) {
    if (list != NULL) {
        for (int i = 0; i < count; i++) {
            free(list[i]);
        }
        free(list);
    }
}

struct student inputSingleStudent(int examCount1, char **exam_list1, int examCount2, char **exam_list2, FILE *output) {
    struct student s;
    if (output == stdout) {
        fprintf(output, COLOR_HEADER "\nВвод данных студента\n" COLOR_RESET);
    }

    if (output == stdout) {
        fprintf(output, COLOR_HEADER "Введите фамилию: " COLOR_RESET);
    }
    readString(s.stud.lastname, STR_SIZE);

    if (output == stdout) {
        fprintf(output, COLOR_HEADER "Введите имя: " COLOR_RESET);
    }
    readString(s.stud.name, STR_SIZE);

    if (output == stdout) {
        fprintf(output, COLOR_HEADER "Введите отчество: " COLOR_RESET);
    }
    readString(s.stud.surname, STR_SIZE);

    s.stud.sem_number = 0;

    // Semester 1
    s.arr[0].exam_number = (int *)malloc(examCount1 * sizeof(int) + examCount1 * sizeof(float));
    if (s.arr[0].exam_number == NULL) {
        printf("Ошибка выделения памяти для данных экзаменов семестра 1");
        exit(EXIT_FAILURE);
    }
    int *exam_numbers = s.arr[0].exam_number;
    float *results = (float *)(exam_numbers + examCount1);

    if (output == stdout) {
        fprintf(output, COLOR_HEADER "\nВвод данных экзаменов для семестра 1:\n" COLOR_RESET);
        showExamTable(exam_list1, examCount1);
    }
    for (int j = 0; j < examCount1; j++) {
        if (output == stdout) {
            fprintf(output, COLOR_HEADER "Введите номер предмета для семестра 1 (от 1 до %d): " COLOR_RESET, examCount1);
        }
        int examIndex = getValidInt(1, examCount1);
        exam_numbers[j] = examIndex - 1;

        float res;
        if (output == stdout) {
            fprintf(output, COLOR_HEADER "Введите результат экзамена для предмета \"%s\" (от 0 до 10): " COLOR_RESET,
                   exam_list1[examIndex - 1]);
        }
        while (1) {
            if (scanf("%f", &res) == 1 && res >= 0 && res <= 10) {
                break;
            }
            else {
                if (output == stdout) {
                    fprintf(output, COLOR_TEXT "Ошибка ввода! Введите вещественное число от 0 до 10: " COLOR_RESET);
                }
                while (getchar() != '\n');
            }
        }
        results[j] = res;
        while (getchar() != '\n');
    }

    // Semester 2
    s.arr[1].exam_number = (int *)malloc(examCount2 * sizeof(int) + examCount2 * sizeof(float));
    if (s.arr[1].exam_number == NULL) {
        printf("Ошибка выделения памяти для данных экзаменов семестра 2");
        exit(EXIT_FAILURE);
    }
    int *exam_numbers2 = s.arr[1].exam_number;
    float *results2 = (float *)(exam_numbers2 + examCount2);

    if (output == stdout) {
        fprintf(output, COLOR_HEADER "\nВвод данных экзаменов для семестра 2:\n" COLOR_RESET);
        showExamTable(exam_list2, examCount2);
    }
    for (int j = 0; j < examCount2; j++) {
        if (output == stdout) {
            fprintf(output, COLOR_HEADER "Введите номер предмета для семестра 2 (от 1 до %d): " COLOR_RESET, examCount2);
        }
        int examIndex = getValidInt(1, examCount2);
        exam_numbers2[j] = examIndex - 1;

        float res;
        if (output == stdout) {
            fprintf(output, COLOR_HEADER "Введите результат экзамена для предмета \"%s\" (от 0 до 10): " COLOR_RESET,
                   exam_list2[examIndex - 1]);
        }
        while (1) {
            if (scanf("%f", &res) == 1 && res >= 0 && res <= 10) {
                break;
            }
            else {
                if (output == stdout) {
                    fprintf(output, COLOR_TEXT "Ошибка ввода! Введите вещественное число от 0 до 10: " COLOR_RESET);
                }
                while (getchar() != '\n');
            }
        }
        results2[j] = res;
        while (getchar() != '\n');
    }
    return s;
}

void addStudent(struct StudentQueue *q, int examCount1, char **exam_list1, int examCount2, char **exam_list2, FILE *output) {
    int numStudents;
    fprintf(output, "Сколько студентов добавить? ");
    numStudents = getValidInt(1, INT32_MAX);
    
    for (int i = 0; i < numStudents; i++) {
        struct student s = inputSingleStudent(examCount1, exam_list1, examCount2, exam_list2, output);
        enqueueStudent(q, s);
        fprintf(output, "Студент %s %s успешно добавлен.\n", s.stud.lastname, s.stud.name);
    }
}

int removeStudent(struct StudentQueue *q, char *lastname) {
    if (q == NULL || q->front == NULL) {
        printf("Очередь студентов пуста!\n");
        return 0;
    }

    struct StudentNode *current = q->front;
    struct StudentNode *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data.stud.lastname, lastname) == 0) {
            if (prev == NULL) {
                q->front = current->next;
                if (q->rear == current) {
                    q->rear = NULL;
                }
            }
            else {
                prev->next = current->next;
                if (q->rear == current) {
                    q->rear = prev;
                }
            }
            if (current->data.arr[0].exam_number) {
                free(current->data.arr[0].exam_number);
            }
            if (current->data.arr[1].exam_number) {
                free(current->data.arr[1].exam_number);
            }
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

void findStudent(struct StudentQueue *q, char *lastname, char **exam_list1, int examCount1, char **exam_list2, int examCount2, FILE *output) {
    if (q == NULL || q->front == NULL) {
        fprintf(output, "Очередь студентов пуста!\n");
        return;
    }

    struct StudentNode *current = q->front;
    int found = 0;
    while (current) {
        if (strcmp(current->data.stud.lastname, lastname) == 0) {
            displayStudentInfo(&(current->data), exam_list1, examCount1, exam_list2, examCount2, output);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        fprintf(output, COLOR_TEXT "\nСтудент с фамилией %s не найден.\n" COLOR_RESET, lastname);
    }
}

void displayStudentInfo(struct student *s, char **exam_list1, int examCount1, char **exam_list2, int examCount2, FILE *output) {
    fprintf(output, COLOR_HEADER "\nИнформация о студенте: %s %s %s\n" COLOR_RESET,
           s->stud.lastname, s->stud.name, s->stud.surname);

    if (s->arr[0].exam_number != NULL) {
        int *exam_numbers1 = s->arr[0].exam_number;
        float *results1 = (float *)((char *)exam_numbers1 + examCount1 * sizeof(int));
        fprintf(output, COLOR_HEADER "\nДанные за первый семестр:\n" COLOR_RESET);
        fprintf(output, COLOR_HEADER "%-30s%-30s%-30s%-30s%-10s\n" COLOR_RESET,
               "Lastnamae", "Name", "Surname", "Subject", "Result");
        for (int j = 0; j < examCount1; j++) {
            fprintf(output, COLOR_DATA "%-30s%-30s%-30s%-30s%-10.2f\n" COLOR_RESET, s->stud.lastname, s->stud.name, s->stud.surname, exam_list1[exam_numbers1[j]], results1[j]);
        }
    }
    else {
        fprintf(output, COLOR_TEXT "\nНет данных за первый семестр.\n" COLOR_RESET);
    }

    if (s->arr[1].exam_number != NULL) {
        int *exam_numbers2 = s->arr[1].exam_number;
        float *results2 = (float *)((char *)exam_numbers2 + examCount2 * sizeof(int));
        fprintf(output, COLOR_HEADER "\nДанные за второй семестр:\n" COLOR_RESET);
        fprintf(output, COLOR_HEADER "%-30s%-30s%-30s%-30s%-10s\n" COLOR_RESET,
               "Lastnamae", "Name", "Surname", "Subject", "Result");
        for (int j = 0; j < examCount2; j++) {
            fprintf(output, COLOR_DATA "%-30s%-30s%-30s%-30s%-10.2f\n" COLOR_RESET, s->stud.lastname, s->stud.name, s->stud.surname, exam_list2[exam_numbers2[j]], results2[j]);
        }
    }
    else {
        fprintf(output, COLOR_TEXT "\nНет данных за второй семестр.\n" COLOR_RESET);
    }
}

void showStudentsBySemesterMulti(struct StudentQueue *q, int semester, char **exam_list, int examCount, FILE *output) {
    if (q == NULL || q->front == NULL) {
        fprintf(output, "Очередь студентов пуста!\n");
        return;
    }

    fprintf(output, COLOR_HEADER "\nСписок студентов за семестр %d:\n" COLOR_RESET, semester);
    fprintf(output, COLOR_HEADER "%-30s%-30s%-30s%-30s%-10s\n" COLOR_RESET,
           "Lastnamae", "Name", "Surname", "Subject", "Result");

    struct StudentNode *current = q->front;
    while (current) {
        int *exam_numbers;
        float *results;
        if (semester == 1) {
            exam_numbers = current->data.arr[0].exam_number;
            results = (float *)((char *)exam_numbers + examCount * sizeof(int));
        } else {
            exam_numbers = current->data.arr[1].exam_number;
            results = (float *)((char *)exam_numbers + examCount * sizeof(int));
        }
        for (int j = 0; j < examCount; j++) {
            fprintf(output, COLOR_DATA "%-30s%-30s%-30s%-30s%-10.2f\n" COLOR_RESET, current->data.stud.lastname, current->data.stud.name,current->data.stud.surname, exam_list[exam_numbers[j]],results[j]);
        }
        current = current->next;
    }
}

struct StudentQueue *moveSemesterData(struct StudentQueue *q, int semester) {
    if (q == NULL) return createStudentQueue(NULL);
    
    struct StudentQueue *newQueue = createStudentQueue(NULL);
    struct StudentNode *current = q->front;
    while (current) {
        struct student newStudent;
        strcpy(newStudent.stud.lastname, current->data.stud.lastname);
        strcpy(newStudent.stud.name, current->data.stud.name);
        strcpy(newStudent.stud.surname, current->data.stud.surname);
        newStudent.stud.sem_number = current->data.stud.sem_number;
        newStudent.arr[0].exam_number = (semester == 1) ? current->data.arr[0].exam_number : current->data.arr[1].exam_number;
        newStudent.arr[1].exam_number = NULL;
        enqueueStudent(newQueue, newStudent);
        current = current->next;
    }
    return newQueue;
}

void saveToOutputFile(struct StudentQueue *q, int semester, char **exam_list, int examCount, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла для записи\n");
        return;
    }

    struct StudentQueue *filtered = moveSemesterData(q, semester);
    struct StudentNode *current = filtered->front;
    while (current) {
        int *exam_numbers;
        float *results;
        exam_numbers = current->data.arr[0].exam_number;
        results = (float *)((char *)exam_numbers + examCount * sizeof(int));
        for (int j = 0; j < examCount; j++) {
            fprintf(file, "%-30s %-30s %-30s %-30s %.2f\n", current->data.stud.lastname, current->data.stud.name, current->data.stud.surname, exam_list[exam_numbers[j]], results[j]);
        }
        current = current->next;
    }
    fclose(file);
    freeStudentQueueShallow(filtered);
    printf("Данные успешно сохранены в файл %s\n", filename);
}

void saveQueueToTextFile(struct StudentQueue *q, const char *filename, int semester, char **exam_list, int examCount) 
{
    saveToOutputFile(q, semester, exam_list, examCount, filename);
}

void saveQueueToBinaryFile(struct StudentQueue *q, const char *filename, int examCount1, int examCount2) 
{
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Ошибка открытия бинарного файла для записи\n");
        return;
    }

    struct StudentNode *current = q->front;
    while (current) 
    {
        fwrite(&current->data.stud, sizeof(struct stud_info), 1, file);
        
        fwrite(&examCount1, sizeof(int), 1, file);
        if (examCount1 > 0) 
        {
            int *exam_numbers = current->data.arr[0].exam_number;
            float *results = (float *)(exam_numbers + examCount1);
            fwrite(exam_numbers, sizeof(int), examCount1, file);
            fwrite(results, sizeof(float), examCount1, file);
        }

        fwrite(&examCount2, sizeof(int), 1, file);
        if (examCount2 > 0) 
        {
            int *exam_numbers = current->data.arr[1].exam_number;
            float *results = (float *)(exam_numbers + examCount2);
            fwrite(exam_numbers, sizeof(int), examCount2, file);
            fwrite(results, sizeof(float), examCount2, file);
        }
        
        current = current->next;
    }
    fclose(file);
    printf("Очередь успешно сохранена в бинарный файл %s\n", filename);
}

int fileExists(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file) 
    {
        fclose(file);
        return 1;
    }
    return 0;
}

void saveExamListToTextFile(char **exam_list, int count, const char *filename) 
{
    FILE *f = fopen(filename, "w");
    if (!f) 
    {
        printf("Ошибка при сохранении предметов в файл: %s\n", filename);
        return;
    }
    for (int i = 0; i < count; i++) 
    {
        fprintf(f, "%s\n", exam_list[i]);
    }
    fclose(f);
    printf("Список предметов сохранен в файл %s\n", filename);
}

char **loadExamListFromTextFile(int *count, const char *filename) 
{
    FILE *f = fopen(filename, "r");
    if (!f) 
    {
        printf("Не удалось открыть файл предметов: %s\n", filename);
        *count = 0;
        return NULL;
    }

    char buffer[N];
    int tempCount = 0;
    while (fgets(buffer, N, f)) 
    {
        tempCount++;
    }
    rewind(f);

    char **list = mem_str(tempCount, N);
    int i = 0;
    while (fgets(buffer, N, f) && i < tempCount) 
    {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(list[i], buffer, N);
        i++;
    }

    fclose(f);
    *count = tempCount;
    printf("Список предметов загружен из файла %s\n", filename);
    return list;
}

struct StudentQueue *loadQueueFromBinaryFile(const char *filename) 
{
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Ошибка открытия бинарного файла для чтения\n");
        return createStudentQueue(NULL);
    }

    struct StudentQueue *queue = createStudentQueue(NULL);
    struct student s;
    
    while (fread(&s.stud, sizeof(struct stud_info), 1, file) == 1) 
    {
        int examCount1;
        fread(&examCount1, sizeof(int), 1, file);
        if (examCount1 > 0) 
        {
            s.arr[0].exam_number = (int *)malloc(examCount1 * sizeof(int) + examCount1 * sizeof(float));
            fread(s.arr[0].exam_number, sizeof(int), examCount1, file);
            float *results = (float *)(s.arr[0].exam_number + examCount1);
            fread(results, sizeof(float), examCount1, file);
        } else 
        {
            s.arr[0].exam_number = NULL;
        }
        
        int examCount2;
        fread(&examCount2, sizeof(int), 1, file);
        if (examCount2 > 0) 
        {
            s.arr[1].exam_number = (int *)malloc(examCount2 * sizeof(int) + examCount2 * sizeof(float));
            fread(s.arr[1].exam_number, sizeof(int), examCount2, file);
            float *results = (float *)(s.arr[1].exam_number + examCount2);
            fread(results, sizeof(float), examCount2, file);
        } else 
        {
            s.arr[1].exam_number = NULL;
        }
        
        enqueueStudent(queue, s);
    }
    
    fclose(file);
    return queue;
}



struct student* loadFromFile(const char *filename, int *studentCount, int semester, char **exam_list, int examCount)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Не удалось открыть файл \"%s\" для чтения\n", filename);
        *studentCount = 0;
        return NULL;
    }

    int totalLines = 0;
    char buf[256];
    while (fgets(buf, sizeof(buf), fp)) totalLines++;
    if (totalLines == 0 || totalLines % examCount != 0) {
        printf("Файл \"%s\" имеет некорректное число строк (%d) для examCount=%d.\n", filename, totalLines, examCount);
        fclose(fp);
        *studentCount = 0;
        return NULL;
    }

    int cnt = totalLines / examCount;
    *studentCount = cnt;
    rewind(fp);

    struct student *students = malloc(cnt * sizeof(struct student));
    if (!students) {
        printf("Ошибка выделения памяти для студентов.\n");
        fclose(fp);
        *studentCount = 0;
        return NULL;
    }

    // Аллоцируем массив (examCount int + examCount float) для каждого студента
    for (int i = 0; i < cnt; i++) 
    {
        students[i].arr[semester-1].exam_number = malloc(examCount * (sizeof(int)+sizeof(float)));
        students[i].arr[1-(semester-1)].exam_number = NULL;
    }

    // Читаем построчно
    for (int i = 0; i < cnt; i++) 
    {
        int *exam_numbers = students[i].arr[semester-1].exam_number;
        float *results = (float *)((char*)exam_numbers + examCount*sizeof(int));
        char lastname[STR_SIZE], name[STR_SIZE], surname[STR_SIZE], subject[STR_SIZE];
        float grade;

        for (int j = 0; j < examCount; j++) 
        {
            if (!fgets(buf, sizeof(buf), fp)) 
            {
                printf("Неожиданный конец файла при чтении строки %d.\n", i*examCount+j+1);
                // Освобождаем всё
                for (int k = 0; k <= i; k++)
                    free(students[k].arr[semester-1].exam_number);
                free(students);
                fclose(fp);
                *studentCount = 0;
                return NULL;
            }
            // Разбираем строку: три слова ФИО, одно слово предмет, и число
            if (sscanf(buf, "%s %s %s %s %f", lastname, name, surname, subject, &grade) != 5) 
            {
                printf("Неправильный формат строки: %s", buf);
            }
            if (j == 0) 
            {
                strncpy(students[i].stud.lastname, lastname, STR_SIZE-1);
                strncpy(students[i].stud.name,     name,     STR_SIZE-1);
                strncpy(students[i].stud.surname,  surname,  STR_SIZE-1);
            }
            // ищем индекс предмета в exam_list
            int found = 0;
            for (int k = 0; k < examCount; k++) 
            {
                if (strcmp(subject, exam_list[k]) == 0) {
                    found = k;
                    break;
                }
            }
            exam_numbers[j] = found;
            results[j] = grade;
        }
    }
    fclose(fp);
    printf("Данные успешно загружены из файла \"%s\".\n", filename);
    return students;
}



struct StudentQueue *loadQueueFromTextFile(const char *filename, int semester, char **exam_list, int examCount)
{
    int studentCount = 0;
    struct student *students = loadFromFile(filename, &studentCount, semester, exam_list, examCount);
    if (!students) 
        return createStudentQueue(NULL);
    struct StudentQueue *queue = createStudentQueue(NULL);
    for (int i = 0; i < studentCount; i++) 
        enqueueStudent(queue, students[i]);
    free(students);
    return queue;
}

void rtrim(char *s) 
{
    for (int i = strlen(s) - 1; i >= 0; i--) 
    {
        if (*(s + i) == ' ' || *(s + i) == '\t' || *(s + i) == '\n')
            *(s + i) = '\0';
        else
            break;
    }
}


void mainMenu(char ***exam_list1, int *examCount1, char ***exam_list2, int *examCount2, struct StudentQueue **queue) {
    int choice;
    char filename[STR_SIZE];
    char lastname[STR_SIZE];
    int semester;
    
    while (1) {
        printf(COLOR_HEADER "\nГлавное меню:\n" COLOR_RESET);
        printf(" 1. Ввести список экзаменов для семестра 1\n");
        printf(" 2. Ввести список экзаменов для семестра 2\n");
        printf(" 3. Загрузить список экзаменов для семестра 1 из файла\n");
        printf(" 4. Загрузить список экзаменов для семестра 2 из файла\n");
        printf(" 5. Сохранить список экзаменов семестра 1 в файл\n");
        printf(" 6. Сохранить список экзаменов семестра 2 в файл\n");
        printf(" 7. Добавить студента\n");
        printf(" 8. Удалить студента\n");
        printf(" 9. Найти студента\n");
        printf("10. Очистить очередь студентов\n");
        printf("11. Вывести данные за семестр 1\n");
        printf("12. Вывести данные за семестр 2\n");
        printf("13. Сохранить очередь студентов в текстовый файл (с указанием семестра)\n");
        printf("14. Сохранить очередь студентов в бинарный файл\n");
        printf("15. Загрузить очередь студентов из текстового файла\n");
        printf("16. Загрузить очередь студентов из бинарного файла\n");
        printf("17. Выход\n");
        printf(COLOR_HEADER "Выберите пункт: " COLOR_RESET);
        
        choice = getValidInt(1, 17);
        switch (choice) {
            case 1:
                if (*exam_list1) {
                    clearExamList(*exam_list1, *examCount1);
                }
                inputExamList(exam_list1, examCount1);
                break;
            case 2:
                if (*exam_list2) {
                    clearExamList(*exam_list2, *examCount2);
                }
                inputExamList(exam_list2, examCount2);
                break;
            case 3:
                printf("Введите имя файла: ");
                readString(filename, STR_SIZE);
                if (*exam_list1) {
                    clearExamList(*exam_list1, *examCount1);
                }
                *exam_list1 = loadExamListFromTextFile(examCount1, filename);
                break;
            case 4:
                printf("Введите имя файла: ");
                readString(filename, STR_SIZE);
                if (*exam_list2) {
                    clearExamList(*exam_list2, *examCount2);
                }
                *exam_list2 = loadExamListFromTextFile(examCount2, filename);
                break;
            case 5:
                if (*exam_list1 == NULL || *examCount1 == 0) {
                    printf(COLOR_ERROR "Нет данных для сохранения (семестр 1)!\n" COLOR_RESET);
                    break;
                }
                printf("Введите имя файла: ");
                readString(filename, STR_SIZE);
                saveExamListToTextFile(*exam_list1, *examCount1, filename);
                break;
            case 6:
                if (*exam_list2 == NULL || *examCount2 == 0) {
                    printf(COLOR_ERROR "Нет данных для сохранения (семестр 2)!\n" COLOR_RESET);
                    break;
                }
                printf("Введите имя файла: ");
                readString(filename, STR_SIZE);
                saveExamListToTextFile(*exam_list2, *examCount2, filename);
                break;
            case 7:
                if (*exam_list1 == NULL || *examCount1 == 0 || *exam_list2 == NULL || *examCount2 == 0) {
                    printf(COLOR_ERROR "Сначала введите списки экзаменов для обоих семестров!\n" COLOR_RESET);
                    break;
                }
                if (*queue == NULL) {
                    *queue = createStudentQueue(NULL);
                }
                addStudent(*queue, *examCount1, *exam_list1, *examCount2, *exam_list2, stdout);
                break;
            case 8:
                if (*queue == NULL || (*queue)->count == 0) {
                    printf(COLOR_ERROR "Очередь студентов пуста!\n" COLOR_RESET);
                    break;
                }
                printf("Введите фамилию студента: ");
                readString(lastname, STR_SIZE);
                removeStudent(*queue, lastname);
                break;
            case 9:
                if (*queue == NULL || (*queue)->count == 0) {
                    printf(COLOR_ERROR "Очередь студентов пуста!\n" COLOR_RESET);
                    break;
                }
                printf("Введите фамилию студента: ");
                readString(lastname, STR_SIZE);
                findStudent(*queue, lastname, *exam_list1, *examCount1, *exam_list2, *examCount2, stdout);
                break;
            case 10:
                if (*queue) {
                    freeStudentQueue(*queue);
                    *queue = NULL;
                    printf("Очередь студентов очищена.\n");
                } else {
                    printf("Очередь студентов уже пуста.\n");
                }
                break;
            case 11:
                if (*queue == NULL || (*queue)->count == 0) {
                    printf(COLOR_ERROR "Очередь студентов пуста!\n" COLOR_RESET);
                    break;
                }
                if (*exam_list1 == NULL || *examCount1 == 0) {
                    printf(COLOR_ERROR "Список экзаменов для семестра 1 не введен!\n" COLOR_RESET);
                    break;
                }
                showStudentsBySemesterMulti(*queue, 1, *exam_list1, *examCount1, stdout);
                break;
            case 12:
                if (*queue == NULL || (*queue)->count == 0) {
                    printf(COLOR_ERROR "Очередь студентов пуста!\n" COLOR_RESET);
                    break;
                }
                if (*exam_list2 == NULL || *examCount2 == 0) {
                    printf(COLOR_ERROR "Список экзаменов для семестра 2 не введен!\n" COLOR_RESET);
                    break;
                }
                showStudentsBySemesterMulti(*queue, 2, *exam_list2, *examCount2, stdout);
                break;
            case 13:
                if (*queue == NULL || (*queue)->count == 0) {
                    printf(COLOR_ERROR "Очередь студентов пуста!\n" COLOR_RESET);
                    break;
                }
                printf("Выберите семестр (1 или 2): ");
                semester = getValidInt(1, 2);
                printf("Введите имя файла: ");
                readString(filename, STR_SIZE);
                if (semester == 1) {
                    saveQueueToTextFile(*queue, filename, semester, *exam_list1, *examCount1);
                } else {
                    saveQueueToTextFile(*queue, filename, semester, *exam_list2, *examCount2);
                }
                break;
            case 14:
                if (*queue == NULL || (*queue)->count == 0) {
                    printf(COLOR_ERROR "Очередь студентов пуста!\n" COLOR_RESET);
                    break;
                }
                printf("Введите имя файла: ");
                readString(filename, STR_SIZE);
                saveQueueToBinaryFile(*queue, filename, *examCount1, *examCount2);
                break;
                case 15: {
                    printf("Для какого семестра загрузка (1 или 2): ");
                    semester = getValidInt(1, 2);
                
                    if (semester == 1) {
                        // Загрузка первого семестра — перезаписываем очередь
                        if (*exam_list1 == NULL || *examCount1 == 0) {
                            printf("Ошибка: сначала загрузите список экзаменов для семестра 1!\n");
                            break;
                        }
                        printf("Введите имя файла: ");
                        readString(filename, STR_SIZE);
                        if (*queue) {
                            freeStudentQueue(*queue);
                        }
                        *queue = createStudentQueue(NULL);
                
                        int studentCount = 0;
                        struct student *students = loadFromFile(
                            filename,
                            &studentCount,
                            1,
                            *exam_list1,
                            *examCount1
                        );
                        if (!students) break;
                        for (int i = 0; i < studentCount; i++) {
                            // обнуляем второй семестр
                            students[i].arr[1].exam_number = NULL;
                            enqueueStudent(*queue, students[i]);
                        }
                        free(students);
                
                    } else {
                        // Загрузка второго семестра — дополняем существующих
                        if (*exam_list2 == NULL || *examCount2 == 0) {
                            printf("Ошибка: сначала загрузите список экзаменов для семестра 2!\n");
                            break;
                        }
                        if (*queue == NULL || (*queue)->count == 0) {
                            printf("Ошибка: сперва загрузите первый семестр (пункт 15 -> семестр 1).\n");
                            break;
                        }
                        printf("Введите имя файла: ");
                        readString(filename, STR_SIZE);
                
                        int studentCount = 0;
                        struct student *students = loadFromFile( filename, &studentCount, 2, *exam_list2, *examCount2);
                        if (!students) break;
                
                        // для каждого загруженного студента ищем по фамилии
                        for (int i = 0; i < studentCount; i++) {
                            struct StudentNode *cur = (*queue)->front;
                            int found = 0;
                            while (cur) {
                                if (strcmp(cur->data.stud.lastname,
                                           students[i].stud.lastname) == 0) {
                                    // обновляем второй семестр
                                    if (cur->data.arr[1].exam_number)
                                        free(cur->data.arr[1].exam_number);
                                    cur->data.arr[1].exam_number = students[i].arr[1].exam_number;
                                    found = 1;
                                    break;
                                }
                                cur = cur->next;
                            }
                            if (!found) {
                                // новый студент — первый семестр пуст
                                students[i].arr[0].exam_number = NULL;
                                enqueueStudent(*queue, students[i]);
                            }
                        }
                        free(students);
                    }
                    break;
                }                                
            case 16:
                printf("Введите имя файла: ");
                readString(filename, STR_SIZE);
                if (*queue) {
                    freeStudentQueue(*queue);
                }
                *queue = loadQueueFromBinaryFile(filename);
                break;
            case 17:
                return;
        }
    }
}