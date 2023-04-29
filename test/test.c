#include <stdio.h>
#include <string.h>

#include "../src/libgeometry/check.h"
#include "../thirdparty/ctest.h"

CTEST(input_check, check_word_1)
{
    char *a = "circle(1.2 2, 1.4)";
    char *b = "circle";
    int error = 0;

    int expected = 0;
    check_word(a, b, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, check_word_2)
{
    char *a = "ciccle(1.2 2, 1.4)";
    char *b = "circle";
    int error = 0;

    int expected = 1;
    check_word(a, b, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, check_open_bracket_1)
{
    char *a = "circle(1.2 2, 1.4)";
    char *b = "circle";
    int error = 0;

    int expected = 6;
    int real = check_word(a, b, &error);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, check_open_bracket_2)
{
    char *a = "circle1.2 2, 1.4)";
    char *b = "circle";

    int error = 0;

    int expected = 1;
    check_word(a, b, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, find_close_bracket_1)
{
    char *a = "circle(1.2 2, 1.4)";
    int len = strlen(a);

    int expected = 17;
    int real = find_close_bracket(a, &len);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, find_close_bracket_2)
{
    char *a = "circle(1.2 2, 1.4";
    int len = strlen(a);

    int expected = 0;
    int real = find_close_bracket(a, &len);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, first_number_1)
{
    char *a = "circle(1.2 2, 1.4)";
    int ind_open_bracket = 6;
    int error = 0;

    int expected = 9;
    int real = check_first_num(a, &ind_open_bracket, &error);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, first_number_2)
{
    char *a = "circle(a 2, 1.4)";
    int error = 0;
    int ind_open_bracket = 6;

    int expected = 1;
    check_first_num(a, &ind_open_bracket, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, second_number_1)
{
    char *a = "circle(1.2 2, 1.4)";
    int error = 0;
    int ind_first_number = 9;

    int expected = 11;
    int real = check_second_num(a, &ind_first_number, &error);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, second_number_2)
{
    char *a = "circle(1.2 a, 1.4)";
    int error = 0;
    int ind_first_number = 9;

    int expected = 1;
    check_second_num(a, &ind_first_number, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, third_number_1)
{
    char *a = "circle(1.2 2, 1.4)";
    int ind_second_number = 11;
    int ind_close_bracket = 17;
    int error = 0;

    int expected = 16;
    int real = check_third_num(
        a, &ind_second_number, &error, &ind_close_bracket);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, third_number_2)
{
    char *a = "circle(1.2 2, x)";
    int ind_second_number = 11;
    int ind_close_bracket = 15;
    int error = 0;

    int expected = 1;
    check_third_num(a, &ind_second_number, &error, &ind_close_bracket);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, check_close_bracket_1)
{
    char *a = "circle(1.2 2, 1.4)";
    int ind_third_number = 16;
    int len = strlen(a);
    int error = 0;

    int expected = 17;
    int real = check_close_bracket(a, &ind_third_number, &len, &error);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, check_close_bracket_2)
{
    char *a = "circle(1.2 2, 1.4a";
    int ind_third_number = 16;
    int len = strlen(a);
    int error = 0;

    int expected = 1;
    check_close_bracket(a, &ind_third_number, &len, &error);
    int real = error;

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, check_unexpected_token_1)
{
    char *a = "circle(1.2 2, 1.4)";
    int ind_close_bracket = 17;
    int len = strlen(a);
    int error = 0;

    int expected = 0;
    int real = check_unexpected_token(a, &ind_close_bracket, &len, &error);

    ASSERT_EQUAL(expected, real);
}

CTEST(input_check, check_unexpected_token_2)
{
    char *a = "circle(1.2 2, 1.4) a";
    int ind_close_bracket = 17;
    int len = strlen(a);
    int error = 0;

    int expected = 1;
    int real = check_unexpected_token(a, &ind_close_bracket, &len, &error);

    ASSERT_EQUAL(expected, real);
}