#include "my_string.h"
#include <string.h>

char *my_strpbrk(const char *s, const char *charset)
{
    char *ans = NULL;

    for (size_t i = 0; s[i] != '\0'; i++)
        for (size_t j = 0; charset[j] != '\0'; j++)
            if (s[i] == charset[j])
                return (char *) &s[i];

    return ans;
}

size_t my_strspn(const char *s, const char *charset)
{
    size_t length = 0;
    size_t last_ind = -1;
    int stop = 1;

    int not_found = 1;
    for (size_t i = 0; charset[i] != '\0'; i++)
        if (s[0] == charset[i])
            not_found = 0;

    if (not_found == 1)
        return 0;

    for (size_t i = 0; s[i] != '\0' && stop; i++)
    {
        not_found = 1;
        for (size_t j = 0; charset[j] != '\0' && not_found; j++)
            if (s[i] == charset[j])
            {
                if ((int) last_ind == -1)
                {
                    last_ind = i;
                    length++;
                }
                else if (i - last_ind != 1)
                    stop = 0;
                else if (i - last_ind == 1)
                {
                    length++;
                    last_ind++;
                }
                not_found = 0;
            }
    }

    return length;
}

size_t my_strcspn(const char *s, const char *reject)
{
    size_t length = 0;
    int stop = 1;

    for (size_t i = 0; s[i] != '\0' && stop; i++)
    {
        int not_found = 1;
        for (size_t j = 0; reject[j] != '\0' && not_found; j++)
            if (s[i] == reject[j])
                not_found = 0;

        if (not_found)
            length++;
        else
            stop = 0;
    }

    return length;
}

char *my_strchr(const char *s, int c)
{
    size_t len = strlen(s);
    for (size_t i = 0; i <= len; i++)
        if (s[i] == c)
            return (char *) &s[i];

    return NULL;
}

char *my_strrchr(const char *s, int c)
{
    char *ans = NULL;
    size_t len = strlen(s);

    for (size_t i = 0; i <= len; i++)
        if (s[i] == c)
            ans = (char *) &s[i];

    return ans;
}
