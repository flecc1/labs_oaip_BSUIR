#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "../../mylib/header_Lib.h"
#include <string.h>

#define N 50
#define COLOR_RESET   "\033[0m"
#define COLOR_HEADER  "\033[1;34m"
#define COLOR_TEXT    "\033[0;37m"
#define COLOR_DATA    "\033[0;32m"

// Структура для информации о студенте
struct stud_info {
    char *lastname;
    char *name;
    char *surname;
    int sem_number; // не используется, но оставлено для совместимости
};

// Объединение для хранения номеров экзаменов и результатов
union exams {
    int *exam_number; // блок памяти: сначала номера экзаменов, затем результаты (float)
    float *result;
};

// Структура студента
struct student {
    struct stud_info stud;
    union exams arr[2]; // данные для двух семестров
};

// Узел очереди студентов
struct StudentNode {
    struct student data;
    struct StudentNode *next;
};

// Очередь студентов
struct StudentQueue {
    struct StudentNode *front;
    struct StudentNode *rear;
    int count;
};

// Прототипы функций для работы со строковыми массивами и списками предметов
char** mem_str(int count, int string_length);
void inputExamList(char ***exam_list, int *examCount);
void showExamTable(char **exam_list, int count);


struct StudentQueue* createStudentQueue(struct student *initialStudent);
void enqueueStudent(struct StudentQueue *q, struct student s);
void freeStudentQueue(struct StudentQueue *q);


// Освобождает только узлы очереди (данные студентов не трогаются) т.к. используется для копий.
void freeStudentQueueShallow(struct StudentQueue *q);
struct StudentQueue* inputStudentsMulti(int *studentCount, int examCount1, char **exam_list1, int examCount2, char **exam_list2);
void showStudentsBySemesterMulti(struct StudentQueue *q, int semester, char **exam_list, int examCount);
struct StudentQueue* moveSemesterData(struct StudentQueue *q, int semester);
void repeatDisplayFunk(struct StudentQueue *q, char **exam_list1, char **exam_list2, int examCount1, int examCount2);

// Дополнительная функция для ввода одного студента
struct student inputSingleStudent(int examCount1, char **exam_list1, int examCount2, char **exam_list2);

// Функция для вывода информации о конкретном студенте (по обоим семестрам)
void displayStudentInfo(struct student *s, char **exam_list1, int examCount1, char **exam_list2, int examCount2);
void addStudent(struct StudentQueue *q, int examCount1, char **exam_list1, int examCount2, char **exam_list2);
int removeStudent(struct StudentQueue *q, char *lastname);
void findStudent(struct StudentQueue *q, char *lastname, char **exam_list1, int examCount1, char **exam_list2, int examCount2);
void clearExamLists(char **exam_list1, int examCount1, char **exam_list2, int examCount2);
void showMainMenu(struct StudentQueue *queue, char **exam_list1, int examCount1, char **exam_list2, int examCount2);