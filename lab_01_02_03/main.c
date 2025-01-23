#include <stdio.h>
#include <math.h>

#define PI (2.0 * asin(1.0))
#define EPS 1e-8
#define ERR_OK       0
#define ERR_IO       1
#define ERR_TRIANGLE 2
#define ERR_SIDES    3

int main(void)
{
    double a, b;

    printf("Enter sides of the triangle (a, b): \n");
    if (scanf("%lf%lf", &a, &b) != 2)
    {
        printf("I/O error\n");
        return ERR_IO;
    }
    if (a < EPS || b < EPS)
    {
        printf("Side entered incorrectly (has to be positive)\n");
        return ERR_SIDES;
    }
    
    double phi;
    
    printf("Enter the angle between thr sides (phi): \n");
    if (scanf("%lf", &phi) != 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    phi = fabs(phi);
    phi = PI * phi / 180.0;

    if (fabs(sin(phi)) < EPS)
    {
        printf("Triangle doesn't exist (angle is equal to zero)\n");
        return ERR_TRIANGLE;
    }

    double s;
    
    s = 0.5 * a * b * sin(phi);
    s = fabs(s);

    printf("Area of the triangle: %lf\n", s); 

    return ERR_OK;
}
