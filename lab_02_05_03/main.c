#include <stdio.h>

#define ARRAY_SIZE 10
#define OK 0
#define ERR_IO 1
#define ERR_INPUT 2

int scan_array(int arr[], size_t length)
{
    for (size_t i = 0; i < length; i++)
        if (scanf("%d", &arr[i]) != 1)
            return ERR_IO;

    return OK;
}

int min_product(int *pa, size_t length)
{
    int min_product = *pa * *(pa + 1);
    int product;

    for (size_t i = 1; i < length - 1; i++)
    {
        product = *(pa + i) * *(pa + i + 1);
        if (product < min_product)
            min_product = product;
    }

    return min_product;
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

    if (length < 2 || length > 10)
    {
        printf("Invalid length input (has to be between one and ten)\n");
        return ERR_INPUT;
    }

    printf("Enter integers: ");
    if (scan_array(arr, length) == 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    int *pa = arr;
    int min;
    min = min_product(pa, length);

    printf("Minimum product of neighboring elements: %d\n", min);

    return OK;
}
