#include "header.h"
int main()
{
    char *str = NULL;
    int repeatProgram = 1;  
    do
    {
        do
        {
            printf(YELLOW "Введите математическое выражение: " RESET);
            getValidString(&str);
            
            if (checkParentheses(str))
                printf(GREEN "Скобки расставлены правильно.\n" RESET);
            else
                printf(RED "Обнаружена ошибка в расстановке скобок.\n" RESET);
            printf(BLUE "Хотите ввести другое выражение? (1 - да, 0 - нет): " RESET);
        } while (getValidInt(0, 1));
        
        freeMemory(&str);
        
        printf(YELLOW "Хотите запустить программу заново? (1 - да, 0 - выход): " RESET);
        repeatProgram = getValidInt(0, 1);
     
    } while (repeatProgram);
    return 0;
}
