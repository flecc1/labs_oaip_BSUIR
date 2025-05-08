#include <stdlib.h>
#include <stdio.h>
#include "header.h"

int main()
{
    int restart = 1;
    do
    {
        struct tree *root = NULL;    
        root = menu(root);
        printf("Хотите запустить программу снова? (1 - да, 0 - нет): ");
        restart = getValidInt(0, 1);
        deltree(root);
    }
    while(restart);
    return 0;
}