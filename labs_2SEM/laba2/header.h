#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define N 30
#define NUM_WIDTH 50
#define RESULT_WIDTH 50
#define COLOR_RESET   "\033[0m"
#define COLOR_HEADER  "\033[1;34m"
#define COLOR_TEXT    "\033[0;37m"
#define COLOR_DATA    "\033[0;32m"

// Структуры и объединения
struct stud_info 
{
    char *lastname;
    char *name;
    char *surname;
    int sem_number;
};

union exams 
{
    int *exam_number; // Для первого семестра
    float *result;    // Для второго семестра
};

struct student
{
    struct stud_info stud;
    union exams arr[2]; // Массив для хранения информации о номерах экзаменов и результатах для двух семестров
};

// Функции (исходные)
void showExamTable(char **exam_list, int count);
void showStudentsBySemester(struct student *students, int studentCount, char **exam_list, int examCount, int semester);
struct student* inputStudents(int *studentCount, int examCount, char **exam_list);
int getValidInt(int min, int max);
void readString(char *buffer, int max_length);
int my_strlen(const char *s);
char* optimizeString(char *str);
char** mem_str(int count, int string_length);
void inputExamList(char ***exam_list, int *examCount);
void clearMemory(struct student *students, int studentCount, char **exam_list, int examCount);
struct student* inputStudentsMulti(int *studentCount, int examCount1, char **exam_list1, int examCount2, char **exam_list2);
void showStudentsBySemesterMulti(struct student *students, int studentCount, int semester, char **exam_list, int examCount);
void clearMemoryMulti(struct student *students, int studentCount, char **exam_list1, int examCount1, char **exam_list2, int examCount2);
void repeatDisplayFunk (int repeatDisplay, struct student *students, int studentCount, char **exam_list1, char **exam_list2, int examCount1, int examCount2);
char ***mem_exam_list(int semestrCount);

