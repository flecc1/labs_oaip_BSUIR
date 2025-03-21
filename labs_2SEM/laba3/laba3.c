#include "header.h"
int main()
{
    char *str = NULL;
    int repeatProgram = 1;  
    do
    {
        do
        {
            printf("Введите математическое выражение: ");
            getValidString(&str);
            
            if (checkParentheses(str))
                printf("Скобки расставлены правильно.\n");
            else
                printf("Обнаружена ошибка в расстановке скобок.\n");
            printf("Хотите ввести другое выражение? (1 - да, 0 - нет): ");
        } while (getValidInt(0, 1));
        
        freeMemory(&str);
        
        printf("Хотите запустить программу заново? (1 - да, 0 - выход): ");
        repeatProgram = getValidInt(0, 1);
     
    } while (repeatProgram);
    return 0;
}
