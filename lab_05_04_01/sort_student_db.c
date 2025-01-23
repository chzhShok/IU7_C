#include "student_db_utils.h"

int get_line_by_pos(FILE *f, size_t pos, student_t *student)
{
    if (pos == 0)
        pos++;

    fseek(f, (long) ((pos - 1) * sizeof(student_t)), SEEK_SET);
    if (fread(student, sizeof(student_t), 1, f) == 0)
        return IO_ERROR;

    return OK;
}

int put_line_by_pos(FILE *f, size_t pos, student_t student)
{
    if (pos == 0)
        pos++;

    fseek(f, (long) ((pos - 1) * sizeof(student_t)), SEEK_SET);
    if (fwrite(&student, sizeof(student_t), 1, f) == 0)
        return IO_ERROR;

    return OK;
}

int compare(student_t student, student_t min_student)
{
    if (strcmp(student.lastname_t, min_student.lastname_t) < 0)
        return 1;
    else if (strcmp(student.lastname_t, min_student.lastname_t) == 0)
        if (strcmp(student.name_t, min_student.name_t) < 0)
            return 1;

    return 0;
}

int swap_lines(size_t i, size_t min_ind, FILE *f)
{
    student_t min_student, student;
    if (get_line_by_pos(f, i, &student) != OK)
        return IO_ERROR;

    if (get_line_by_pos(f, min_ind, &min_student) != OK)
        return IO_ERROR;

    if (put_line_by_pos(f, i, min_student) != OK)
        return IO_ERROR;

    if (put_line_by_pos(f, min_ind, student) != OK)
        return IO_ERROR;

    return OK;
}

int sort_students(FILE *f)
{
    size_t size;
    if (file_size(f, &size) == IO_ERROR)
        return IO_ERROR;

    size_t number_count = size / sizeof(student_t) + 1;
    if (number_count == 1)
        return EMPTY_FILE;

    for (size_t i = 0; i < number_count; i++)
    {
        size_t min_ind = i;
        student_t min_student;
        if (get_line_by_pos(f, i, &min_student) == IO_ERROR)
            return IO_ERROR;

        for (size_t j = i + 1; j < number_count; j++)
        {
            student_t student;
            if (get_line_by_pos(f, j, &student) == IO_ERROR)
                return IO_ERROR;

            if (compare(student, min_student))
            {
                min_ind = j;
                min_student = student;
            }
        }

        if (i != min_ind)
            if (swap_lines(i, min_ind, f) == IO_ERROR)
                return IO_ERROR;
    }

    return OK;
}
