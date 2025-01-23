#include <limits.h>
#include <stdarg.h>
#include <stddef.h>

#include "my_snprintf.h"

#define BUFFER 32

static int int_to_str(char *buffer, size_t buffer_size, long value, int is_signed)
{
    char temp[BUFFER];
    int index = 0;
    int negative = 0;

    int is_long_min = 0;

    if (is_signed && value < 0)
    {
        negative = 1;
        if (value == LONG_MIN)
        {
            is_long_min = 1;
            value++;
            value = -value;
        }
        else
        {
            value = -value;
        }
    }

    if (is_long_min)
    {
        long tmp_val = (value % 10) + 1;
        temp[index++] = '0' + tmp_val;
    }
    else
    {
        temp[index++] = '0' + (value % 10);
    }
    value /= 10;

    while (value != 0)
    {
        temp[index++] = '0' + (value % 10);
        value /= 10;
    }

    if (negative)
        temp[index++] = '-';

    int written = 0;
    for (int i = index - 1; i >= 0; --i)
    {
        if (written < (int) buffer_size - 1)
            buffer[written] = temp[i];
        written++;
    }

    if (written < (int) buffer_size)
        buffer[written] = '\0';

    return written;
}

static int str_copy(char *buffer, int buffer_size, const char *src)
{
    int written = 0;
    while (*src)
    {
        if (written < buffer_size - 1)
            buffer[written] = *src;
        written++;
        src++;
    }

    if (written < buffer_size)
        buffer[written] = '\0';

    return written;
}

static int d_spec(int value, int *buffer_pos, int n, char *s)
{
    char temp[BUFFER];
    int len = int_to_str(temp, sizeof(temp), value, 1);
    for (int i = 0; i < len; i++)
    {
        if (*buffer_pos < n - 1 && s)
            s[*buffer_pos] = temp[i];
        (*buffer_pos)++;
    }

    return len;
}

static int ld_spec(long value, int *buffer_pos, int n, char *s)
{
    char temp[BUFFER];

    int len = int_to_str(temp, sizeof(temp), value, 1);
    for (int i = 0; i < len; i++)
    {
        if (*buffer_pos < (int) n - 1 && s)
            s[*buffer_pos] = temp[i];
        (*buffer_pos)++;
    }

    return len;
}

static int hd_spec(short value, int *buffer_pos, int n, char *s)
{
    char temp[BUFFER];
    int len = int_to_str(temp, sizeof(temp), value, 1);
    for (int i = 0; i < len; i++)
    {
        if (*buffer_pos < (int) n - 1 && s)
            s[*buffer_pos] = temp[i];
        (*buffer_pos)++;
    }

    return len;
}

static int c_spec(char value, int *buffer_pos, int n, char *s)
{
    if (*buffer_pos < (int) n - 1 && s)
        s[*buffer_pos] = value;
    (*buffer_pos)++;

    return 1;
}

static int s_spec(const char *value, int *buffer_pos, int n, char *s)
{
    if (value == NULL)
        return -1;

    int len = str_copy(NULL, 0, value);
    for (int i = 0; i < len; i++)
    {
        if (*buffer_pos < (int) n - 1 && s)
            s[*buffer_pos] = value[i];
        (*buffer_pos)++;
    }

    return len;
}

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    if (!format || (!s && n > 0))
        return -1;

    va_list args;
    va_start(args, format);

    int written = 0;
    int buffer_pos = 0;

    while (*format)
    {
        if (*format == '%' && *(format + 1))
        {
            format++;

            if (*format == 'd')
            {
                int value = va_arg(args, int);
                written += d_spec(value, &buffer_pos, (int) n, s);
            }
            else if (*format == 'l' && *(format + 1) == 'd')
            {
                format++;
                long value = va_arg(args, long);

                written += ld_spec(value, &buffer_pos, (int) n, s);
            }
            else if (*format == 'h' && *(format + 1) == 'd')
            {
                format++;
                short value = (short) va_arg(args, int);

                written += hd_spec(value, &buffer_pos, (int) n, s);
            }
            else if (*format == 'c')
            {
                char value = (char) va_arg(args, int);

                written += c_spec(value, &buffer_pos, (int) n, s);
            }
            else if (*format == 's')
            {
                const char *value = va_arg(args, const char *);

                int len = s_spec(value, &buffer_pos, (int) n, s);
                if (len == -1)
                    return len;

                written += len;
            }
            else
            {
                va_end(args);
                if (n > 0 && s)
                {
                    if (buffer_pos < (int) n)
                        s[buffer_pos] = '\0';
                    else
                        s[n - 1] = '\0';
                }
                return -1;
            }
        }
        else
        {
            if (buffer_pos < (int) n - 1 && s)
                s[buffer_pos] = *format;
            buffer_pos++;
            written++;
        }

        if (*format)
            format++;
    }

    if (n > 0 && s)
    {
        if (buffer_pos < (int) n)
            s[buffer_pos] = '\0';
        else
            s[n - 1] = '\0';
    }

    va_end(args);
    return written;
}
