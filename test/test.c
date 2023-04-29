#include <ctest.h>
#include <ctype.h>
#include <string.h>

#include <errors.h>
#include <geometry.h>

// type id = 3 - wrong format
// 0 - circle
// 1 - triangle
// 2 - polygon

CTEST(partest, test_name_1)
{
    char str[] = "poawlygon((3 -2.0, 3.0 2, 1.0 0, 3.0 -2, 3.0 2, 3 -2.0)) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(2, error_num);
    ASSERT_EQUAL(3, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(partest, test_double_in_brackets_1)
{
    char str[] = "circle(10x 0, 1.5) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(4, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(partest, test_double_in_brackets_2)
{
    char str[] = "circle(10 0, 1..5) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(4, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(partest, test_left_bracket)
{
    char str[] = "circle(10 0, 1.5)) ";

    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(1, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(7, column);
}

CTEST(partest, test_right_bracket)
{
    char str[] = "circle((10 0, 1.5) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(5, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(18, column);
}

CTEST(partest, test_token_after_brackets)
{
    char str[] = "circle(10 0, 1.5) wowo ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(3, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(17, column);
}

CTEST(partest, test_unneded_token)
{
    char str[] = "circle(10 0, 1.5 1.4) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(6, error_num);
    ASSERT_EQUAL(0, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(partest, test_name_2)
{
    char str[] = "triangle((-3.0 -2, -1 0.0, -3.0 2.0, -3 -2)) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(0, error_num);
    ASSERT_EQUAL(1, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(partest, test_name_3)
{
    char str[] = "polygon((-3.0 -2, -1 0.0, -3.0 2.0, -3 -2)) ";
    int type_id = 0;
    int error_num = 0;
    long int column = 0;
    error_num = isWKT(str, &column, &type_id);

    ASSERT_EQUAL(0, error_num);
    ASSERT_EQUAL(2, type_id);
    ASSERT_EQUAL(0, column);
}

CTEST(lextest, test_CircleExtracor_func_1)
{
    Circle *circ;
    char str[] = "circle(10 0, 1.5) ";
    long int len = strlen(str);
    circ = CircleExtractor(str, len);

    ASSERT_DBL_NEAR(10, circ->center.x);
    ASSERT_DBL_NEAR(0, circ->center.y);
    ASSERT_DBL_NEAR(1.5, circ->radius);
}

CTEST(lextest, test_CircleExtracor_func_2)
{
    Circle *circ;
    char str[] = "circle(0 0, 0) ";
    long int len = strlen(str);
    circ = CircleExtractor(str, len);

    ASSERT_DBL_NEAR(0, circ->center.x);
    ASSERT_DBL_NEAR(0, circ->center.y);
    ASSERT_DBL_NEAR(0, circ->radius);
}

CTEST(lextest, test_CircleExtracor_func_3)
{
    Circle *circ;
    char str[] = "circle(0 0, -2) ";
    long int len = strlen(str);
    circ = CircleExtractor(str, len);

    ASSERT_DBL_NEAR(0, circ->center.x);
    ASSERT_DBL_NEAR(0, circ->center.y);
    ASSERT_DBL_NEAR(2, circ->radius);
}

CTEST(lextest, test_CircleExtracor_func_4)
{
    Circle *circ;
    char str[] = "circle(32.123123 -45.126665, -2.123129) ";
    long int len = strlen(str);
    circ = CircleExtractor(str, len);
    double tol = 0.00001;

    ASSERT_DBL_NEAR_TOL(32.123123, circ->center.x, tol);
    ASSERT_DBL_NEAR_TOL(-45.126665, circ->center.y, tol);
    ASSERT_DBL_NEAR_TOL(2.123129, circ->radius, tol);
}

CTEST(lextest, test_CircleExtracor_func_5)
{
    Circle *circ;
    char str[] = "circle(321231.123123 -451231.126665, -200009.123129) ";
    long int len = strlen(str);
    circ = CircleExtractor(str, len);
    double tol = 0.005;

    ASSERT_DBL_NEAR_TOL(321231.123123, circ->center.x, tol);
    ASSERT_DBL_NEAR_TOL(-451231.126665, circ->center.y, tol);
    ASSERT_DBL_NEAR_TOL(200009.123129, circ->radius, tol);
}

CTEST(calctest, test_math_1)
{
    Circle *circ;
    char str[] = "circle(0 0, 10) ";
    long int len = strlen(str);
    circ = CircleExtractor(str, len);
    double tol = 0.01;

    circ->area = CircleAreaCalc(circ->radius);
    circ->perimeter = CirclePerimeterCalc(circ->radius);

    ASSERT_DBL_NEAR_TOL(314.16, circ->area, tol);
    ASSERT_DBL_NEAR_TOL(62.83, circ->perimeter, tol);
}

CTEST(calctest, test_math_2)
{
    Circle *circ;
    char str[] = "circle(0 0, 0) ";
    long int len = strlen(str);
    circ = CircleExtractor(str, len);
    double tol = 0.01;

    circ->area = CircleAreaCalc(circ->radius);
    circ->perimeter = CirclePerimeterCalc(circ->radius);

    ASSERT_DBL_NEAR_TOL(0, circ->area, tol);
    ASSERT_DBL_NEAR_TOL(0, circ->perimeter, tol);
}

CTEST(calctest, test_math_3)
{
    Circle *circ;
    char str[] = "circle(-100 -10000, -10) ";
    long int len = strlen(str);
    circ = CircleExtractor(str, len);
    double tol = 0.01;

    circ->area = CircleAreaCalc(circ->radius);
    circ->perimeter = CirclePerimeterCalc(circ->radius);

    ASSERT_DBL_NEAR_TOL(314.16, circ->area, tol);
    ASSERT_DBL_NEAR_TOL(62.83, circ->perimeter, tol);
}

CTEST(calctest, test_math_4)
{
    Circle *circ;
    char str[] = "circle(-100 -10000, 0) ";
    long int len = strlen(str);
    circ = CircleExtractor(str, len);
    double tol = 0.01;

    circ->area = CircleAreaCalc(circ->radius);
    circ->perimeter = CirclePerimeterCalc(circ->radius);

    ASSERT_DBL_NEAR_TOL(0, circ->area, tol);
    ASSERT_DBL_NEAR_TOL(0, circ->perimeter, tol);
}