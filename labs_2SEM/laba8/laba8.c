#include "header.h"

int main() {
    int repeatProgram;
    do {
        char **exam_list1 = NULL;
        int examCount1 = 0;
        char **exam_list2 = NULL;
        int examCount2 = 0;
        struct StudentQueue *queue = NULL;
        mainMenu(&exam_list1, &examCount1, &exam_list2, &examCount2, &queue);
        if (exam_list1) clearExamList(exam_list1, examCount1);
        if (exam_list2) clearExamList(exam_list2, examCount2);
        if (queue) freeStudentQueue(queue);
        printf(COLOR_HEADER "\nЗапустить программу заново? (1 - да, 0 - нет): " COLOR_RESET);
        repeatProgram = getValidInt(0, 1);
    } while (repeatProgram);
    return 0;
}