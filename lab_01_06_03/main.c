#include <stdio.h>
#include <math.h>

#define ERR_OK   0
#define ERR_IO   1
#define ERR_LINE 2
#define EPS 1e-8

int dot_position(double x1, double y1, double x2, double y2, double x_dot, double y_dot)
{
    double d;

    d = (x_dot - x1) * (y2 - y1) - (y_dot - y1) * (x2 - x1);
    if (fabs(d) < EPS)
    {
        return 1;
    }
    else if (d > 0)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    double x1, y1;
    double x2, y2;
    double x_dot, y_dot;

    printf("Enter the coordinates of the first point of the line: \n");
    if (scanf("%lf%lf", &x1, &y1) != 2)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    printf("Enter the coordinates of the second point of the line: \n");
    if (scanf("%lf%lf", &x2, &y2) != 2)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    printf("Enter the coordinates of the dot: \n");
    if (scanf("%lf%lf", &x_dot, &y_dot) != 2)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    if ((fabs(x1 - x2) < EPS) && (fabs(y1 - y2) < EPS))
    {
        printf("Entered a dot, not a straight line\n");
        return ERR_LINE;
    }

    int location;

    location = dot_position(x1, y1, x2, y2, x_dot, y_dot);
    printf("Location of the dot (zero - above the straight line, one - on the straight line, two - under the straight lines): %d\n", location);

    return ERR_OK;
}
