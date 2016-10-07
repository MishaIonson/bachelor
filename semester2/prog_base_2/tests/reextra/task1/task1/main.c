#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

int getRealNumsNumber(char* line)
{

    int length = 0;
    while(line[length] != '\0')
        length++;

    int answer = 0;
    for (int i = 0; i < length; i++)
    {
        if (((int)line[i] >= 48) && ((int)line[i] <= 57))
        {
            while (((int)line[i] >= 48) && ((int)line[i] <= 57))
            {
                i++;
                if (i >= length)
                    return answer;
            }
            if (line[i] == '.')
            {
                i++;
                if (i >= length)
                    return answer;
                if (((int)line[i] >= 48) && ((int)line[i] <= 57))
                {
                    answer++;
                    while(((int)line[i] >= 48) && ((int)line[i] <= 57))
                    {
                        i++;
                        if (i >= length)
                            return answer;
                    }

                }
                else
                    continue;
            }
            else
                continue;
        }
    }

    return answer;
}

static void getRealNumsNumber_test1(void **state){
    assert_int_equal(getRealNumsNumber("asd1.2asda2.2sd2.2a2.4231"), 4);
}

static void getRealNumsNumber_test2(void **state){
    assert_int_equal(getRealNumsNumber("asd1.2"), 1);
}

static void getRealNumsNumber_test3(void **state){
    assert_int_equal(getRealNumsNumber("12.2 2.1a asd2222 ..."), 2);
}

static void getRealNumsNumber_test4(void **state){
    assert_int_equal(getRealNumsNumber("    .   2.2 .   1.123  .  "), 2);
}

static void getRealNumsNumber_test5(void **state){
    assert_int_equal(getRealNumsNumber("hello2.2iwantA2.12 .222 . 222"), 2);
}

static void getRealNumsNumber_test6(void **state){
    assert_int_equal(getRealNumsNumber("i .2 a.2 1.2 12. asd"), 1);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(getRealNumsNumber_test1),
        cmocka_unit_test(getRealNumsNumber_test2),
        cmocka_unit_test(getRealNumsNumber_test3),
        cmocka_unit_test(getRealNumsNumber_test4),
        cmocka_unit_test(getRealNumsNumber_test5),
        cmocka_unit_test(getRealNumsNumber_test6)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
