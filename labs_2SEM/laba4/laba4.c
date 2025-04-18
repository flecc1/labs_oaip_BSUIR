#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>



int main() {
    int repeatProgram = 1;
    do
    {
        char **exam_list1 = NULL;
        int examCount1;
        char **exam_list2 = NULL;
        int examCount2;
        do
        { 
            printf("\nВвод списка предметов для семестра 1:\n");
            inputExamList(&exam_list1, &examCount1);
            
            printf("\nВвод списка предметов для семестра 2:\n");
            inputExamList(&exam_list2, &examCount2);
            
            int studentCount;
            printf(COLOR_HEADER "\nВведите количество студентов: " COLOR_RESET);
            studentCount = getValidInt(1, INT32_MAX);
            
            // Ввод данных студентов с экзаменационными оценками для обоих семестров
            struct StudentQueue *queue = inputStudentsMulti(&studentCount, examCount1, exam_list1, examCount2, exam_list2);
            
            // Вызов главного меню для работы с очередью студентов
            showMainMenu(queue, exam_list1, examCount1, exam_list2, examCount2);
            
            freeStudentQueue(queue);
            printf("Хотите ввести другие данные? (1 - да, 0 - нет): ");
        }while(getValidInt(0, 1));

        clearExamLists(exam_list1, examCount1, exam_list2, examCount2);
        
        printf(COLOR_HEADER "\nЗапустить программу заново? (1 - да, 0 - нет): " COLOR_RESET);
        repeatProgram = getValidInt(0, 1);
    }while (repeatProgram);
    return 0;
}
