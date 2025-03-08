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
        char **exam_list1 = NULL;
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
        
        // Цикл для выбора семестра для вывода информации
        repeatDisplayFunk(1, students, studentCount, exam_list1, exam_list2, examCount1, examCount2);
        // int repeatDisplay = 1;
        // while(repeatDisplay)
        // {
        //     printf(COLOR_HEADER "\nВведите номер семестра для вывода информации (1 или 2, 0 для завершения отображения): " COLOR_RESET);
        //     int semester = getValidInt(0, 2);
        //     if(semester == 0)
        //         break;
        //     if (semester == 1)
        //         showStudentsBySemesterMulti(students, studentCount, 1, exam_list1, examCount1);
        //     else
        //         showStudentsBySemesterMulti(students, studentCount, 2, exam_list2, examCount2);
        // }
        
        // Очистка выделенной памяти
        clearMemoryMulti(students, studentCount, exam_list1, examCount1, exam_list2, examCount2);
        
        printf(COLOR_HEADER "\nЗапустить программу заново? (1 - да, 0 - нет): " COLOR_RESET);
        repeatProgram = getValidInt(0, 1);
    }
    return 0;
}
