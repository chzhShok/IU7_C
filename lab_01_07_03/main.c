#include <stdio.h>
#include <math.h>

#define ERR_OK    0
#define ERR_IO    1
#define ERR_ENTER 2
#define EPS 1e-8

double atan_series(double x, double eps)
{
    int n = 1;
    double last = x;
    double s = 0.0;

    while (fabs(last) >= eps)
    {
        s += last;
        last = (-last * x * x * (2 * (n - 1) + 1)) / (2 * n + 1);
        n++;
    }
    return s;
}

int main(void)
{
    double eps;
    double x;

    printf("Enter x and epsilon:\n");
    if (scanf("%lf%lf", &x, &eps) != 2)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    if ((x > 1.0 || x < -1.0) || (eps <= 0.0 || eps > 1.0))
    {
        printf("x has to be less than one and more than minus one. Epsilon has to less than one and more than zero\n");
        return ERR_ENTER;
    }

    double f, s;

    f = atan(x);
    s = atan_series(x, eps);

    double absolute_error, relative_error;

    absolute_error = fabs(f - s);
    if (fabs(f) < EPS)
    {
        relative_error = 0.0;
    }
    else
    {
        relative_error = absolute_error / fabs(f);
    }

    printf("Approximate value of the function: %lf\n", s);
    printf("Actual value of the function: %lf\n", f);
    printf("Absolute error: %lf\n", absolute_error);
    printf("Relative error: %lf\n", relative_error);

    return ERR_OK;
}
