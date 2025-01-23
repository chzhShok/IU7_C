#include "student_db_utils.h"

int condition(char s1[LASTNAME_LENGTH], char s2[LASTNAME_LENGTH], size_t s2_len)
{
    if (strncmp(s1, s2, s2_len) == 0)
        return 1;
    return 0;
}

int print_bd_in_another_file(FILE *f_src, FILE *f_dst, char substr[LASTNAME_LENGTH], int *write)
{
    size_t size;
    if (file_size(f_src, &size) == IO_ERROR)
        return IO_ERROR;

    size_t number_count = size / sizeof(student_t);
    if (number_count == 0)
        return EMPTY_FILE;

    student_t student;
    size_t subst_len = strlen(substr);

    while (fread(&student, sizeof(student_t), 1, f_src))
    {
        if (condition(student.lastname_t, substr, subst_len))
        {
            if (fwrite(&student, sizeof(student_t), 1, f_dst) == 0)
                return IO_ERROR;
            (*write)++;
        }
    }

    return OK;
}
