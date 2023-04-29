#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/check.h>

#define _USE_MATH_DEFINE_

void token(char *a)
{
    float x, y, rad, square, perimetr;
    char del[] = "circle( ,)";
    x = atof(strtok(a, del));
    y = atof(strtok(NULL, del));
    rad = atof(strtok(NULL, del));
    square = M_PI * rad * rad;
    perimetr = 2 * M_PI * rad;
    printf("x = %.3f\ty = %.3f\trad = %.3f\n", x, y, rad);
    printf("square = %.3f\tperimetr = %.3f\n", square, perimetr);
}

int main()
{
    FILE *file1;
    FILE *file;

    file1 = fopen("geometry.txt", "r");

    if (!file1)
    {
        printf("Error: cannot open file. Check name of file\n");
        return 0;
    }

    int ind_open_bracket = 0, ind_close_bracket = 0, ind_last_num_elm = 0,
        ind_first_num_elm = 0, ind_second_num_elm = 0;
    int length = 0, count = 0, element = 0, error = 0;

    while (1)
    {
        element = fgetc(file1);
        if (element == EOF)
        {
            if (feof(file1) != 0)
            {
                break;
            }
        }
        count++;
    }

    length = count;
    fclose(file1);

    char a[length], b[6] = "circle";
    file = fopen("geometry.txt", "r");
    while (fgets(a, length + 1, file))
    {
        printf("%s", a);

        // check 'circle and finding index of '(' symbol
        check_word(a, b, &error, &ind_open_bracket);

        // printf("error = %d\tind_open_bracket = %d\n", error,
        // ind_open_bracket);

        // find index of ')' token
        find_close_bracket(a, &length, &ind_close_bracket);
        // printf("ind_close_bracket = %d\n", ind_close_bracket);

        // check first number
        check_first_num(a, &ind_open_bracket, &ind_first_num_elm, &error);
        // printf("ind_first_num_elm = %d\n", ind_first_num_elm);

        // check second number
        check_second_num(a, &ind_first_num_elm, &ind_second_num_elm, &error);
        // printf("ind_second_num_elm = %d\n", ind_second_num_elm);

        // check last number
        check_third_num(
            a,
            &ind_second_num_elm,
            &ind_last_num_elm,
            &error,
            &ind_close_bracket);
        // printf("ind_last_num_elm = %d\n", ind_last_num_elm);

        // check ')' symbol
        check_close_bracket(
            a, &ind_last_num_elm, &length, &ind_close_bracket, &error);
        // printf("ind_close_bracket = %d\n", ind_close_bracket);

        // check unexpected tokens
        check_unexpected_token(a, &ind_close_bracket, &length, &error);

        if (error == 0)
        {
            printf("No Errors!\n");
            token(a);
        }

        error = 0;
        printf("\n");
    }
    return 0;
}