#include <stdio.h>
#include <math.h>

#define ARRAY_SIZE 10
#define EPS 1e-8 
#define OK 0
#define ERR_IO 1
#define ERR_INPUT 2
#define ERR_GEOMETRIC 3

int scan_array(int arr[], size_t length)
{
    for (size_t i = 0; i < length; i++)
        if (scanf("%d", &arr[i]) != 1)
            return ERR_IO;

    return OK;
}

double geometric_mean(int arr[], size_t length)
{
    double p = 1.0;
    int pos_numbers = 0;

    for (size_t i = 0; i < length; i++)
    {
        if (arr[i] > 0)
        {
            p *= arr[i];
            pos_numbers++;
        }
    }

    if (pos_numbers == 0)
        return -1.0;
    
    return pow(p, 1.0 / pos_numbers);
}

int main(void)
{
    int arr[ARRAY_SIZE];
    size_t length;

    printf("Enter length of array (has to be between one and ten): ");
    if (scanf("%zu", &length) != 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    } 

    if (length < 1 || length > 10)
    {
        printf("Invalid length input (has to be between one and ten)");
        return ERR_INPUT;
    }

    printf("Enter integers: ");
    if (scan_array(arr, length) == 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    double g = geometric_mean(arr, length);
    if (fabs(g + 1.0) < EPS)
    {
        printf("Array hasn't positive numbers");
        return ERR_GEOMETRIC;
    }

    printf("Geometric mean: %lf\n", g);

    return OK;
}

