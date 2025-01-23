#include <stdio.h>

#define ARRAY_SIZE 10
#define OK 0
#define ERR_EMPTY_ARRAY 1
#define ERR_OUT_OF_RANGE 100

int scan_array(int arr[], size_t *length)
{
    int i = 0, x;
    int rc = OK;

    while ((scanf("%d", &x) == 1) && (rc == OK))
    {
        if (i < 10)
        {
            arr[i] = x;
            i++;
        }
        else
            rc = ERR_OUT_OF_RANGE;
    }

    *length = i;

    return rc;
}

void print_array(int arr[], size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selection_sort(int arr[], int length)
{
    int min_element;
    int temp;

    for (int i = 0; i < length; i++)
    {
        min_element = i;
        for (int j = i + 1; j < length; j++)
        {
            if (arr[j] < arr[min_element])
                min_element = j;
        }

        temp = arr[i];
        arr[i] = arr[min_element];
        arr[min_element] = temp;
    }
}

int main(void)
{
    int arr[ARRAY_SIZE];
    size_t length = 0;
    int rc = OK;

    printf("Enter integers (up to ten): ");
    rc = scan_array(arr, &length);

    if (length == 0)
    {
        printf("Array is empty\n");
        rc = ERR_EMPTY_ARRAY;
    }

    selection_sort(arr, (int) length);

    printf("Sorted array: ");
    print_array(arr, length);

    return rc;
}
