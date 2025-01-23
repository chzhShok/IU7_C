#include "student_db_utils.h"

int file_size(FILE *f, size_t *size)
{
    long sz;

    if (fseek(f, 0L, SEEK_END))
        return IO_ERROR;

    sz = ftell(f);
    if (sz < 0)
        return IO_ERROR;

    *size = (size_t) sz;

    return fseek(f, 0L, SEEK_SET);
}

int import(FILE *f_txt, FILE *f_bin)
{
    student_t student;
    while (fscanf(f_txt, "%s%s%u%u%u%u", student.lastname_t, student.name_t, &((student.marks_t)[0]), &((student.marks_t)[1]), &((student.marks_t)[2]), &((student.marks_t)[3])) == 6)
        fwrite(&student, sizeof(student_t), 1, f_bin);

    return OK;
}

int export(FILE *f_bin, FILE *f_txt)
{
    student_t student;

    while (fread(&student, sizeof(student_t), 1, f_bin) != 0)
        fprintf(f_txt, "%s\n%s\n%u %u %u %u\n", student.lastname_t, student.name_t, (student.marks_t)[0], (student.marks_t)[1], (student.marks_t)[2], (student.marks_t)[3]);

    return OK;
}

void print_file(FILE *f)
{
    fseek(f, 0, SEEK_SET);

    student_t student;

    while (fread(&student, sizeof(student_t), 1, f) != 0)
        printf("%s\n%s\n%u %u %u %u\n", student.lastname_t, student.name_t, (student.marks_t)[0], (student.marks_t)[1], (student.marks_t)[2], (student.marks_t)[3]);
}

int my_ftruncate(FILE *f) 
{
    int file_descriptor;
    
    #ifdef _WIN32
    file_descriptor = _fileno(f);
    #else
    file_descriptor = fileno(f);
    #endif
    
    #ifdef _WIN32
    if (_chsize_s(file_descriptor, 0) != 0)
        return -1;
    #else
    if (ftruncate(file_descriptor, 0) == -1)
        return -1;
    #endif
    
    return 0;
}
