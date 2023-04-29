#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libgeometry/check.h"

int main()
{
    FILE* file1;
    FILE* file;
    file1 = fopen("geometry.txt", "r");
    if (!file1) {
        printf("Error! Cannot open file. Check file name.\n");
        return 0;
    }
    int length = 0, count = 0, element = 0, error = 0;
    while (1) {
        element = fgetc(file1);
        if (element == EOF) {
            if (feof(file1) != 0) {
                break;
            }
        }
        count++;
    }
    length = count;
    fclose(file1);
    int amount = 0;
    float* x_arr = (float*)malloc(amount * sizeof(float));
    float* y_arr = (float*)malloc(amount * sizeof(float));
    float* rad_arr = (float*)malloc(amount * sizeof(float));

    char a[length], b[6] = "circle";
    file = fopen("geometry.txt", "r");
    while (fgets(a, length + 1, file)) {
        int open_index = check_circle_word(a, b, &error);

        int close_index = search_close_index(a, &length);

        int first_index = check_first_number(a, &open_index, &error);

        int second_index = check_second_number(a, &first_index, &error);

        int third_index
                = check_third_number(a, &second_index, &close_index, &error);

        close_index = get_close_index(a, &third_index, &length, &error);

        error = check_unexpected_tokens(a, &close_index, &length, &error);
        if (error == 0) {
            puts("\n");
            float x = 0, y = 0, radius = 0;
            parse_circle_expression(a, &x, &y, &radius);
            x_arr[amount] = x;
            y_arr[amount] = y;
            rad_arr[amount] = radius;
            amount += 1;
        }

        error = 0;
        puts("\n");
    }

    find_intersections(x_arr, y_arr, rad_arr, amount);
    return 0;
}
