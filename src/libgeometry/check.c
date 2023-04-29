#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "check.h"

#define _USE_MATH_DEFINES

int check_word(char *a, char *b, int *error)
{
    int ind_open_bracket = 0;
    for (int i = 0; i < 7; i++)
    {
        if (a[i] != b[i] && i < 6)
        {
            printf("Error at column %d: expected 'circle'\n", i);
            *error = 1;
            break;
        }
        ind_open_bracket = i;

        if (i == 6 && a[i] != '(')
        {
            printf("Error at column %d: expected '('\n", i);
            *error = 1;
            return 0;
            break;
        }
    }
    if (*error == 1)
    {
        ind_open_bracket += 1;
    }
    return ind_open_bracket;
}

int find_close_bracket(char *a, int *length)
{
    int ind_close_bracket = 0;
    for (int i = 0; i < *length && a[i] != '\n'; i++)
    {
        if (a[i] == ')')
        {
            ind_close_bracket = i;
        }
    }
    return ind_close_bracket;
}

// check first number
int check_first_num(char *a, int *ind_open_bracket, int *error)
{
    int ind_first_num_elm = 0;
    for (int i = *ind_open_bracket + 1; a[i] != ' '; i++)
    {
        if (*error == 0)
        {
            if (a[i] == ',')
            {
                *error = 1;
                printf("Error at column %d: expected '<space>' and "
                       "'<double>'\n",
                       i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-' && a[i] != ' ')
            {
                *error = 1;
                printf("Error at column %d: expected '<double>'\n", i);
                return i;
                break;
            }
            ind_first_num_elm = i;
        }
        else
        {
            break;
        }
    }
    return ind_first_num_elm;
}

// check second number
int check_second_num(char *a, int *ind_first_num_elm, int *error)
{
    int ind_second_num_elm = 0;
    for (int i = *ind_first_num_elm + 2; a[i] != ','; i++)
    {
        if (*error == 0)
        {
            if (a[i] == ')')
            {
                *error = 1;
                printf("Error at column %d: expected ',' and '<double>'\n", i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-')
            {
                *error = 1;
                printf("Error at column %d: expected '<double>' or ',' "
                       "token\n",
                       i);
                return i;
                break;
            }
            ind_second_num_elm = i;
        }
        else
        {
            break;
        }
    }
    return ind_second_num_elm;
}

// check last number
int check_third_num(
    char *a, int *ind_second_num_elm, int *error, int *ind_close_bracket)
{
    int ind_last_num_elm = 0;
    for (int i = *ind_second_num_elm + 3; i < *ind_close_bracket; i++)
    {
        if (*error == 0)
        {
            if ((isdigit(a[i]) == 0 && a[i] != '.') || a[i] == '0')
            {
                if (a[i] == ')' || a[i] == '(' || a[i] == ' ')
                {
                    break;
                }
                *error = 1;
                printf("Error at column %d: expected '<double>'\n", i);
                break;
            }
            ind_last_num_elm = i;
        }
        else
        {
            break;
        }
    }
    return ind_last_num_elm;
}

// check ')' symbol
int check_close_bracket(char *a, int *ind_last_num_elm, int *length, int *error)
{
    int ind_close_bracket = 0;
    for (int i = *ind_last_num_elm + 1; i < *length; i++)
    {
        if (*error == 0)
        {
            if (a[i] != ')')
            {
                *error = 1;
                printf("Error at column %d: expected ')'\n", *ind_last_num_elm);
                break;
            }
            else
            {
                ind_close_bracket = i;
                break;
            }
        }
        else
        {
            break;
        }
    }
    return ind_close_bracket;
}

// check unexpected tokens
int check_unexpected_token(
    char *a, int *ind_close_bracket, int *length, int *error)
{
    for (int i = *ind_close_bracket + 1; i < *length; i++)
    {
        if (*error == 0)
        {
            if (a[i] == '\n')
            {
                break;
            }

            if (a[i] != ' ')
            {
                *error = 1;
                printf("Error at column %d: unexpected token\n", i);
                break;
            }
        }
        else
        {
            break;
        }
    }
    return *error;
}

void token(
    char *a,
    float *x,
    float *y,
    float *rad,
    float *array_x,
    float *array_y,
    float *array_rad,
    int index)
{
    float square, perimetr;
    char del[] = "circle( ,)";
    *x = atof(strtok(a, del));
    array_x[index] = *x;
    *y = atof(strtok(NULL, del));
    array_y[index] = *y;
    *rad = atof(strtok(NULL, del));
    array_rad[index] = *rad;
    square = M_PI * *rad * *rad;
    perimetr = 2 * M_PI * *rad;
    printf("x = %.3f\ty = %.3f\trad = %.3f\n", *x, *y, *rad);
    printf("square = %.3f\tperimetr = %.3f\n", square, perimetr);
}

void intersects(float *array_x, float *array_y, float *array_rad, int index)
{
    printf("\nIntersections:");
    for (int i = 0; i < index; i++)
    {
        printf("\ncircle %d. intersects circle ", i + 1);
        for (int j = 0; j < index; j++)
        {
            // distance between centers
            double centers = sqrt(pow(array_x[j] - array_x[i], 2) + pow(array_y[j] - array_y[i], 2));
            // checking for the coincidence of two circles
            if (centers == 0 && array_rad[i] == array_rad[j] && j != i)
            {
                // intersects
                printf("%d. ", j + 1);
                break;
            }
            // checking for the intersection of circles according to the
            // triangle rule
            if (array_rad[i] + array_rad[j] >= centers && array_rad[i] + centers >= array_rad[j] && centers + array_rad[j] >= array_rad[i] && j != i)
            {
                // intersects
                printf("%d. ", j + 1);
                break;
            }
        }
    }
}