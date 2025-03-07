#include <stdio.h>
#include <math.h>
#include <wchar.h>
int main ()
{     
    int y;
    int y_1;
    int r = 1;
    double a, b ,c;
    double d;
    double x_1, x_2;
        
     while(r ==1) 
    {
    
        while(1)
        {
            printf("введите коэвиценты квадратного уравнения(a,b,c) посл каждой цифры нажмите ввод\n");
            rewind(stdin);
            y = scanf("%lf%lf%lf", &a,&b,&c);
            if (y !=3)
            {
                printf("такой символ не поддерживается введите число \n");
            }
            else if(y == 3) break;
        }
        d = b*b - 4*a*c;
        if (d<0) 
        {
            printf("дискриминант меньше нуля, действительных корнец нет\n");
        }
        else if (d == 0)
        {
            x_1 = (-b + sqrt(d)) / (2*a);
            printf("дискриминант равен 0, корни уравнения x_1 = %.2lf\n", x_1);
        }
        else if (d>0)
        {
            x_1 = (-b + sqrt(d))/(2*a);
            x_1 = (-b + sqrt(d))/(2*a);
            printf("дискриминант больше 0,корни уравнения x_1 = %.2lf, x_2 = %.2lf\n", x_1, x_2);
        }
        while(1) 
        {
            printf("еесли хоиите начать программ заново пишите 1, любой цифра отичная от 1 ведет за собой выход программы:   ");
            y_1 = scanf("%d", &r);
            rewind(stdin);
            if(y_1 != 1) 
            {
                printf("такой символ не подходит введите число \n");
            }
            else if(y_1 == 1) break;
        }
    }
            return 0;
}