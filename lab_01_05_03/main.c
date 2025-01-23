#include <stdio.h>

#define ERR_OK   0
#define ERR_IO   1
#define ERR_NUMS 2

int gcd(int a, int b)
{
    int min_num = 0;
    int max_divider = 1;

    if (a < b)
        min_num = a;
    else
        min_num = b;

    for (int i = 1; i <= min_num; i++)
    {
        if ((a % i == 0) && (b % i == 0))
        {
            max_divider = i;
        }
    }

    return max_divider;    
}

int main(void)
{
    int a, b;

    printf("Enter natural numbers a, b: \n");
    if (scanf("%d%d", &a, &b) != 2)
    {
        printf("I/O error\n");
        return ERR_IO;
    }
    if ((a <= 0) || (b <= 0))
    {
        printf("Numbers entered incorrectly (has to natural)\n");
        return ERR_NUMS;
    }

    int max_divider;
    max_divider = gcd(a, b);
    printf("Max common divider: %d\n", max_divider);

    return ERR_OK;
}
