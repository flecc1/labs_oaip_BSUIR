#include "header.h"

int main()
{
    do
    {
        // Инициализируем все переменные, которые потом будут использоваться в menu()
        char **exam_list1 = NULL;
        int examCount1 = 0;
        char **exam_list2 = NULL;
        int examCount2 = 0;
        struct student *students = NULL;
        int studentCount = 0;
        int dataEntered = 0;
        // Запускаем меню
        menu(&exam_list1,&examCount1, &exam_list2, &examCount2, &students, &studentCount, &dataEntered);
        clearMemoryMulti(students, studentCount, exam_list1, examCount1, exam_list2, examCount2);
        printf("\nНачать заново? 1–да, 0–нет: ");
    }while (getValidInt(0, 1) == 1);
    return 0;
}
