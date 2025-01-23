#include <stdio.h>
#include <math.h>

#define ERR_OK    0
#define ERR_IO    1
#define ERR_ENTER 2
#define EPS 1e-8

int g_x(double *g)
{
    double f = 1.0;
    int n = 1;
    double x;
    
    do
    {
        if (scanf("%lf", &x) != 1)
        {
            return ERR_IO;
        }
        else
        {
            if (x >= 0.0)
            {
                f *= 1.0 / (x + n);
                n++;
            }
        }
    }
    while (x >= 0.0);

    if (n == 1)
    {
        return ERR_ENTER;
    }
    
    *g = exp(f);

    return ERR_OK;
}

int main(void)
{
    double g;

    printf("Enter x (to stop enter negative number): \n");
    int rc = g_x(&g);

    if (rc == ERR_ENTER)
    {
        printf("You didn't enter any non-negative numbers\n");
        return ERR_ENTER;
    }
    else if (rc == ERR_IO)
    {
        printf("I/O error\n");
        return ERR_IO;
    }
    else
    {
        printf("g(x): %lf\n", g);   
    }

    return ERR_OK;
}
