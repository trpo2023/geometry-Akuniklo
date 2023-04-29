#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libgeometry/check.h"

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

    int length = 0, count = 0, element = 0, error = 0, index = 0,
        number_of_circle = 1;
    int ind_open_bracket = 0, ind_close_bracket = 0, ind_last_num_elm = 0,
        ind_first_num_elm = 0, ind_second_num_elm = 0;

    float *array_x = (float *)malloc(index * sizeof(float));
    float *array_y = (float *)malloc(index * sizeof(float));
    float *array_rad = (float *)malloc(index * sizeof(float));

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

    char a[length + 1], b[6] = "circle";
    file = fopen("geometry.txt", "r");
    while (fgets(a, length + 1, file))
    {
        printf("%d. %s\n", number_of_circle, a);

        // check 'circle and finding index of '(' symbol
        ind_open_bracket = check_word(a, b, &error);

        // find index of ')' token
        ind_close_bracket = find_close_bracket(a, &length);

        // check first number
        ind_first_num_elm = check_first_num(a, &ind_open_bracket, &error);

        // check second number
        ind_second_num_elm = check_second_num(a, &ind_first_num_elm, &error);

        // check last number
        ind_last_num_elm = check_third_num(
            a, &ind_second_num_elm, &error, &ind_close_bracket);

        // check ')' symbol
        ind_close_bracket = check_close_bracket(a, &ind_last_num_elm, &length, &error);

        // check unexpected tokens
        check_unexpected_token(a, &ind_close_bracket, &length, &error);

        if (error == 0)
        {
            printf("No Errors!\n");
            float x = 0, y = 0, rad = 0;
            token(a, &x, &y, &rad, array_x, array_y, array_rad, index);
            index += 1;
        }

        error = 0;
        printf("\n");
        number_of_circle += 1;
    }

    intersects(array_x, array_y, array_rad, index);
    free(array_x);
    free(array_y);
    free(array_rad);

    return 0;
}