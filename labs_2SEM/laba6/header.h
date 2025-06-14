/* header.h */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include "../../mylib/header_Lib.h"

#define N 50
#define M 100

#define COLOR_RESET   "\033[0m"
#define COLOR_HEADER  "\033[1;34m"
#define COLOR_TEXT    "\033[0;37m"
#define COLOR_DATA    "\033[0;32m"

// Структуры и объединения
struct stud_info 
{
    char lastname[M];
    char name[M];
    char surname[M];
    int sem_number;
};

union exams 
{
    int *exam_number; // Для первого семестра (номера предметов)
    float *result;    // Для второго семестра (оценки)
};

struct student
{
    struct stud_info stud;
    union exams arr[2]; // [0] – данные первого семестра; [1] – второго
};

// Прототипы функций
void showExamTable(char **exam_list, int count);
char** mem_str(int count, int string_length);
void inputExamList(char ***exam_list, int *examCount);

struct student* inputStudentsMulti(int studentCount, int examCount1, char **exam_list1, int examCount2, char **exam_list2);
void showStudentsBySemesterMulti(struct student *students, int studentCount, int semester, char **exam_list, int examCount);
void clearMemoryMulti(struct student *students, int studentCount, char **exam_list1, int examCount1, char **exam_list2, int examCount2);
void repeatDisplayFunk(int repeatDisplay, struct student *students, int studentCount, char **exam_list1, char **exam_list2, int examCount1, int examCount2);
struct student* moveSemesterData(struct student *students, int studentCount, int semester);
void clearAllStudents(struct student **students, int *studentCount, int *dataEntered);
char ***mem_exam_list(int semestrCount);

// Новые функции для работы с файлом:
void saveToFile(const char *filename, struct student *students, int studentCount, int semester, char **exam_list, int examCount);
struct student* loadFromFile(const char *filename, int *studentCount, int semester, char **exam_list, int examCount);

void menu(char ***exam_list1, int *examCount1, char ***exam_list2, int *examCount2, struct student **students, int *studentCount, int *dataEntered);
