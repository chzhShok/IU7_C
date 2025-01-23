#include <stdio.h>
#include <math.h>

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

void print_array(int arr[], size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int reversed_num(int num)
{
    int n = (int) log10(num);
    int new_num = 0, k = (int) pow(10, n);

    while (num > 0)
    {
        new_num += (num % 10) * k;
        num /= 10;
        k /= 10;
    }

    return new_num;
}

size_t insert_reversed_elements(int arr[], int arr_with_reversed[], size_t length)
{
    int j = 0;

    for (size_t i = 0; i < length; i++)
    {
        arr_with_reversed[j] = arr[i];
        if (arr[i] > 0)
        {
            j++;
            arr_with_reversed[j] = reversed_num(arr[i]);
        }
        j++;
    }

    return j;
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

    int arr_with_reversed[2 * ARRAY_SIZE];
    size_t length_arr_with_reversed = insert_reversed_elements(arr, arr_with_reversed, length);

    print_array(arr_with_reversed, length_arr_with_reversed);

    return OK;
}
