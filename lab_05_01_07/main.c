#include "file_utils.h"

int main(void)
{
    int count = 0;

    printf("Enter sequence of numbers: ");
    int rc = process(stdin, &count);
    if (rc == NOT_ENOUGH_DATA)
    {
        printf("Not enough data\n");
        return rc;
    }

    printf("Number of local maxima in the sequence: %d\n", count);

    return 0;
}
