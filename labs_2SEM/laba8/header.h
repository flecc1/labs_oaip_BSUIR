#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include "../../mylib/header_Lib.h"

#define N 50
#define STR_SIZE 100
#define COLOR_HEADER "\033[1;34m"
#define COLOR_TEXT "\033[0;37m"
#define COLOR_DATA "\033[0;32m"
#define COLOR_ERROR "\033[1;31m"

struct stud_info {
    char lastname[STR_SIZE];
    char name[STR_SIZE];
    char surname[STR_SIZE];
    int sem_number;
};

union exams {
    int *exam_number;
    float *result;
};

struct student {
    struct stud_info stud;
    union exams arr[2];
};

struct StudentNode {
    struct student data;
    struct StudentNode *next;
};

struct StudentQueue {
    struct StudentNode *front;
    struct StudentNode *rear;
    int count;
};

// Function declarations
char **mem_str(int count, int string_length);
void inputExamList(char ***exam_list, int *examCount);
void showExamTable(char **exam_list, int count);

struct StudentQueue *createStudentQueue(struct student *initialStudent);
void enqueueStudent(struct StudentQueue *q, struct student s);
void freeStudentQueue(struct StudentQueue *q);
void freeStudentQueueShallow(struct StudentQueue *q);

struct student inputSingleStudent(int examCount1, char **exam_list1, int examCount2, char **exam_list2, FILE *output);
void displayStudentInfo(struct student *s, char **exam_list1, int examCount1, char **exam_list2, int examCount2, FILE *output);
void addStudent(struct StudentQueue *q, int examCount1, char **exam_list1, int examCount2, char **exam_list2, FILE *output);
int removeStudent(struct StudentQueue *q, char *lastname);
void findStudent(struct StudentQueue *q, char *lastname, char **exam_list1, int examCount1, char **exam_list2, int examCount2, FILE *output);
void clearExamList(char **list, int count);
void showStudentsBySemesterMulti(struct StudentQueue *q, int semester, char **exam_list, int examCount, FILE *output);
struct StudentQueue *moveSemesterData(struct StudentQueue *q, int semester);

void saveQueueToTextFile(struct StudentQueue *q, const char *filename, int semester, char **exam_list, int examCount);
void saveQueueToBinaryFile(struct StudentQueue *q, const char *filename, int examCount1, int examCount2);
struct StudentQueue *loadQueueFromTextFile(const char *filename, int semester, char **exam_list, int examCount);
struct StudentQueue *loadQueueFromBinaryFile(const char *filename);
void saveExamListToTextFile(char **exam_list, int count, const char *filename);
char **loadExamListFromTextFile(int *count, const char *filename);
int fileExists(const char *filename);

void mainMenu(char ***exam_list1, int *examCount1, char ***exam_list2, int *examCount2, struct StudentQueue **queue);
void rtrim(char *s);