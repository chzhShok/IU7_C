#include <stdio.h>
#include <stdlib.h>

#define ERR_OK  0
#define ERR_IO  1
#define ERR_NUM 2

int main(void)
{
    int num;

    printf("Enter three-digit number: \n");
    if (scanf("%d", &num) != 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    num = abs(num);
    if (num < 100 || num > 999)
    {
        printf("Number entered incorrectly (has to be three-digit)\n");
        return ERR_NUM;
    }
    
    int p = 1;
    while (num > 0)
    {
        p *= (num % 10);
        num /= 10;
    }

    printf("Product of the digits of a number: %d\n", p);

    return ERR_OK;
}
