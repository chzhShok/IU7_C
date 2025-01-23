#include <stdio.h>

#define ERR_OK   0
#define ERR_IO   1
#define ERR_TIME 2
#define EPS 1e-8

int main(void)
{
    double v0; 
    double a;
    double t;

    printf("Enter the initial velocity v0, acceleration a, time t: \n");
    if (scanf("%lf", &v0) != 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    }
    if (scanf("%lf", &a) != 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    }
    if (scanf("%lf", &t) != 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    if (t < -EPS)
    {
        printf("Time entered incorrectly (has to be non-negative)\n");
        return ERR_TIME;
    }

    double s;
    double v;
    
    v = v0 * t;
    s = v + (a * t * t) / 2.0;

    printf("Displacement: %lf\n", s);

    return ERR_OK;
}
