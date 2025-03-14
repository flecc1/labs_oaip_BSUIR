#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>




int main()
{
    int repeatProgram = 1;
    while(repeatProgram)
    {
        char **exam_list1 = NULL; // массив который хранит список предметов для 
        int examCount1;
        char **exam_list2 = NULL;
        int examCount2;
        
        // Ввод списка предметов для семестра 1
        printf("\nВвод списка предметов для семестра 1:\n");
        inputExamList(&exam_list1, &examCount1);
        
        // Ввод списка предметов для семестра 2
        printf("\nВвод списка предметов для семестра 2:\n");
        inputExamList(&exam_list2, &examCount2);
        
        int studentCount;
        printf(COLOR_HEADER "\nВведите количество студентов: " COLOR_RESET);
        studentCount = getValidInt(1, INT32_MAX);
        
        // Ввод данных студентов с экзаменационными оценками для обоих семестров
        struct student *students = inputStudentsMulti(&studentCount, examCount1, exam_list1, examCount2, exam_list2);
        repeatDisplayFunk(1, students, studentCount, exam_list1, exam_list2, examCount1, examCount2);
        clearMemoryMulti(students, studentCount, exam_list1, examCount1, exam_list2, examCount2);
        
        printf(COLOR_HEADER "\nЗапустить программу заново? (1 - да, 0 - нет): " COLOR_RESET);
        repeatProgram = getValidInt(0, 1);
    }
    return 0;
}
