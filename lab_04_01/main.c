#include "my_string.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    int tests = 0, passed = 0;

    // my_strpbrk
    // TEST 1
    {
        tests++;
        char str[] = "1234567890";
        char *ans1 = strpbrk(str, "28");
        char *ans2 = my_strpbrk(str, "28");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 2
    {
        tests++;
        char str[] = "1245789";
        char *ans1 = strpbrk(str, "360");
        char *ans2 = my_strpbrk(str, "360");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 3
    {
        tests++;
        char str[] = "1";
        char *ans1 = strpbrk(str, "123");
        char *ans2 = my_strpbrk(str, "123");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 4
    {
        tests++;
        char str[] = "happyhappyhappy";
        char *ans1 = strpbrk(str, "happy");
        char *ans2 = my_strpbrk(str, "happy");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 5
    {
        tests++;
        char str[] = "happyhappyhappy";
        char *ans1 = strpbrk(str, "grustno");
        char *ans2 = my_strpbrk(str, "grustno");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 6
    {
        tests++;
        char str[] = "happyhappyhappy";
        char *ans1 = strpbrk(str, "");
        char *ans2 = my_strpbrk(str, "");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 7
    {
        tests++;
        char str[] = "";
        char *ans1 = strpbrk(str, "happy");
        char *ans2 = my_strpbrk(str, "happy");

        if (ans1 == ans2)
            passed++;
    }


    // my_strspn
    // TEST 1
    {
        tests++;
        char str[] = "1234567890";
        size_t ans1 = my_strspn(str, "321");
        size_t ans2 = strspn(str, "321");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 2
    {
        tests++;
        char str[] = "1234567890";
        size_t ans1 = my_strspn(str, "6");
        size_t ans2 = strspn(str, "6");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 3
    {
        tests++;
        char str[] = "23563124";
        size_t ans1 = my_strspn(str, "1234");
        size_t ans2 = strspn(str, "1234");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 4
    {
        tests++;
        char str[] = "palebluedot";
        size_t ans1 = my_strspn(str, "blue");
        size_t ans2 = strspn(str, "blue");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 5
    {
        tests++;
        char str[] = "palebluedot";
        size_t ans1 = my_strspn(str, "earth");
        size_t ans2 = strspn(str, "earth");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 6
    {
        tests++;
        char str[] = "palebluedot";
        size_t ans1 = my_strspn(str, "");
        size_t ans2 = strspn(str, "");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 7
    {
        tests++;
        char str[] = "palebluedot";
        size_t ans1 = my_strspn(str, "????");
        size_t ans2 = strspn(str, "????");

        if (ans1 == ans2)
            passed++;
    }

    // my_strcspn
    // TEST 1
    {
        tests++;
        char str[] = "1234567890";
        size_t ans1 = my_strcspn(str, "465");
        size_t ans2 = strcspn(str, "465");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 2
    {
        tests++;
        char str[] = "123445123312456";
        size_t ans1 = my_strcspn(str, "465");
        size_t ans2 = strcspn(str, "465");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 3
    {
        tests++;
        char str[] = "1234567888";
        size_t ans1 = my_strcspn(str, "9");
        size_t ans2 = strcspn(str, "9");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 4
    {
        tests++;
        char str[] = "palebluedot?blue?";
        size_t ans1 = my_strcspn(str, "blue");
        size_t ans2 = strcspn(str, "blue");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 5
    {
        tests++;
        char str[] = "palebluedotth";
        size_t ans1 = my_strcspn(str, "earth");
        size_t ans2 = strcspn(str, "earth");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 6
    {
        tests++;
        char str[] = "palebluedot";
        size_t ans1 = my_strcspn(str, "");
        size_t ans2 = strcspn(str, "");

        if (ans1 == ans2)
            passed++;
    }

    // TEST 7
    {
        tests++;
        char str[] = "...palebluedot";
        size_t ans1 = my_strcspn(str, "????");
        size_t ans2 = strcspn(str, "????");

        if (ans1 == ans2)
            passed++;
    }


    // my_strchr
    // TEST 1
    {
        tests++;
        char str[] = "1234567890";
        char *ans1 = my_strchr(str, '5');
        char *ans2 = strchr(str, '5');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 2
    {
        tests++;
        char str[] = "123456";
        char *ans1 = my_strchr(str, '9');
        char *ans2 = strchr(str, '9');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 3
    {
        tests++;
        char str[] = "1234567890";
        char *ans1 = my_strchr(str, '1');
        char *ans2 = strchr(str, '1');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 4
    {
        tests++;
        char str[] = "23445674";
        char *ans1 = my_strchr(str, '4');
        char *ans2 = strchr(str, '4');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 5
    {
        tests++;
        char str[] = "aaaaaaa     b     \0 b";
        char *ans1 = my_strchr(str, 'b');
        char *ans2 = strchr(str, 'b');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 6
    {
        tests++;
        char str[] = "coooool teanager";
        char *ans1 = my_strchr(str, 'o');
        char *ans2 = strchr(str, 'o');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 7
    {
        tests++;
        char str[] = "coooool teanager ";
        char *ans1 = my_strchr(str, ' ');
        char *ans2 = strchr(str, ' ');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 8
    {
        tests++;
        char str[] = "coooool! teanager?!";
        char *ans1 = my_strchr(str, '!');
        char *ans2 = strchr(str, '!');

        if (ans1 == ans2)
            passed++;
    }


    // my_strrchr
    // TEST 1
    {
        tests++;
        char str[] = "23445674";
        char *ans1 = my_strrchr(str, '4');
        char *ans2 = strrchr(str, '4');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 2
    {
        tests++;
        char str[] = "12345678";
        char *ans1 = my_strrchr(str, '8');
        char *ans2 = strrchr(str, '8');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 3
    {
        tests++;
        char str[] = "123456";
        char *ans1 = my_strrchr(str, '9');
        char *ans2 = strrchr(str, '9');

        if (ans1 == ans2)
            passed++;
    }


    // TEST 4
    {
        tests++;
        char str[] = "coooool teanager";
        char *ans1 = my_strrchr(str, 'o');
        char *ans2 = strrchr(str, 'o');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 5
    {
        tests++;
        char str[] = "coooool teanager ";
        char *ans1 = my_strrchr(str, ' ');
        char *ans2 = strrchr(str, ' ');

        if (ans1 == ans2)
            passed++;
    }

    // TEST 6
    {
        tests++;
        char str[] = "coooool! teanager?!";
        char *ans1 = my_strrchr(str, '!');
        char *ans2 = strrchr(str, '!');

        if (ans1 == ans2)
            passed++;
    }

    printf("Tests failed: %d\n", tests - passed);
    return 0;
}
