#include <stdio.h>
#include <math.h>

#define ARRAY_SIZE 10
#define OK 0
#define ERR_IO 1
#define ERR_INPUT 2
#define ERR_ARMSTRONG 3

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

int is_armstrong_number(int num)
{
    if (num <= 0)
        return 0;

    int n = (int) log10(num) + 1;
    int new_num = num, sum = 0;

    while (new_num > 0)
    {
        sum += (int) pow(new_num % 10, n);
        new_num /= 10;
    }

    return sum == num;
}

size_t armstrong_array(int arr[restrict], int armstrong_arr[restrict], size_t length)
{
    size_t j = 0;

    for (size_t i = 0; i < length; i++)
    {
        if (is_armstrong_number(arr[i]))
        {
            armstrong_arr[j] = arr[i];
            j++;
        }
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

    int armstrong_arr[ARRAY_SIZE];
    size_t armstrong_length = armstrong_array(arr, armstrong_arr, length);

    if (armstrong_length == 0)
    {
        printf("Array hasn't armstrong numbers\n");
        return ERR_ARMSTRONG;
    }

    print_array(armstrong_arr, armstrong_length);

    return OK;
}
