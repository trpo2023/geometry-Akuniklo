#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../src/libgeometry/check.h"
#include "../thirdparty/ctest.h"

CTEST(check_circle_word, correct_word_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    char b[] = "circle";
    int error = 0;
    int result = check_circle_word(a, b, &error);

    ASSERT_EQUAL(6, result);
    ASSERT_EQUAL(0, error);
}

CTEST(search_close_index, correct_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    int length = strlen(a);
    int result = search_close_index(a, &length);

    ASSERT_EQUAL(20, result);
}

CTEST(search_close_index, no_close_bracket_test)
{
    char a[] = "circle(0.0, 0.0, 1.0";
    int length = strlen(a);
    int result = search_close_index(a, &length);

    ASSERT_EQUAL(19, result);
}

CTEST(check_first_number, correct_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    int open_index = 6, error = 0;
    int result = check_first_number(a, &open_index, &error);

    ASSERT_EQUAL(9, result);
    ASSERT_EQUAL(1, error);
}

CTEST(check_first_number, error_input_test)
{
    char a[] = "circle(0.0x, 0.0, 1.0)";
    int open_index = 6, error = 1;
    int result = check_first_number(a, &open_index, &error);

    ASSERT_EQUAL(1, error);
    ASSERT_NOT_EQUAL(11, result);
}

CTEST(check_second_number, correct_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    int first_index = 11, error = 0;
    int result = check_second_number(a, &first_index, &error);

    ASSERT_EQUAL(14, result);
    ASSERT_EQUAL(0, error);
}

CTEST(check_second_number, error_input_test)
{
    char a[] = "circle(0.0, 0.x, 1.0)";
    int first_index = 11, error = 0;
    int result = check_second_number(a, &first_index, &error);

    ASSERT_NOT_EQUAL(16, result);
    ASSERT_EQUAL(1, error);
}

CTEST(check_third_number, correct_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    int second_index = 16, error = 1, close_index = 17;
    int result = check_third_number(a, &second_index, &close_index, &error);

    ASSERT_EQUAL(0, result);
}

CTEST(check_third_number, error_input_test)
{
    char a[] = "circle(0.0, 0.0, 1.x)";
    int second_index = 16, error = 1, close_index = 17;
    int result = check_third_number(a, &second_index, &close_index, &error);

    ASSERT_NOT_EQUAL(21, result);
    ASSERT_EQUAL(1, error);
}
CTEST(get_close_index, no_error_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)";
    int third_index = 7, length = strlen(a), error = 0;
    int result = get_close_index(a, &third_index, &length, &error);

    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(1, error);
}

CTEST(get_close_index, error_test)
{
    char a[] = "circle(0.0, 0.0, 1.0";
    int third_index = 7, length = strlen(a), error = 0;
    int result = get_close_index(a, &third_index, &length, &error);

    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(1, error);
}

CTEST(check_unexpected_tokens, no_error_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)\n";
    int close_index = 14, length = strlen(a), error = 0;
    int result = check_unexpected_tokens(a, &close_index, &length, &error);

    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error);
}

CTEST(check_unexpected_tokens, error_test)
{
    char a[] = "circle(0.0, 0.0, 1.0)x";
    int close_index = 14, length = strlen(a), error = 0;
    int result = check_unexpected_tokens(a, &close_index, &length, &error);

    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error);
}
