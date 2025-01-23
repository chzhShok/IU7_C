#include "student_db_utils.h"

double average_mark(FILE *f)
{
    double sum = 0.0;
    student_t student;
    int count = 0;

    while (fread(&student, sizeof(student_t), 1, f) != 0)
    {
        for (int i = 0; i < CLASS_COUNT; i++)
            sum += (student.marks_t)[i];
        count += 4;
    }

    fseek(f, 0, SEEK_SET);
    return sum / count;
}

size_t appropriate_lines(FILE *f, student_t approp_students[], double average)
{
    student_t student;
    size_t array_ind = 0;

    while (fread(&student, sizeof(student_t), 1, f) != 0)
    {
        double sum = 0.0;
        for (size_t i = 0; i < CLASS_COUNT; i++)
            sum += (student.marks_t)[i];

        double line_average = sum / CLASS_COUNT;
        if (line_average >= average)
            approp_students[array_ind++] = student;
    }

    fseek(f, 0, SEEK_SET);
    return array_ind;
}

int rewrite_file(FILE *f, student_t students[], size_t array_size)
{
    if (my_ftruncate(f) != 0)
        return IO_ERROR;

    for (size_t i = 0; i < array_size; i++)
        if (fwrite(&(students[i]), sizeof(student_t), 1, f) == 0)
            return IO_ERROR;

    return 0;
}

int delete_by_condition(FILE *f)
{
    size_t size;
    if (file_size(f, &size) == IO_ERROR)
        return IO_ERROR;

    size_t num = size / sizeof(student_t);
    if (num == 0)
        return EMPTY_FILE;

    double average = average_mark(f);

    student_t students[STUDENTS_LEN];
    size_t students_size = appropriate_lines(f, students, average);

    if (rewrite_file(f, students, students_size) == IO_ERROR)
        return IO_ERROR;

    return OK;
}

