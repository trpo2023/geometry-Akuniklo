#define _USE_MATH_DEFINES
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "check.h"

double sqrt(double sqrt)
{
    double root = sqrt / 3;
    int i;
    if (sqrt <= 0)
        return 0;
    for (i = 0; i < 32; i++)
        root = (root + sqrt / root) / 2;
    return root;
}
double pow_custom(double a)
{
    return a * a;
}

int check_circle_word(char* a, char* b, int* error)
{
    int open_index;

    for (int i = 0; i < 7; i++) {
        if (a[i] != b[i] && i < 6) {
            printf("Error at column %d: expected 'circle'\n", i);
            *error = 1;
            break;
        }
        open_index = i;
    }
    return open_index;
}

int search_close_index(char* a, int* length)
{
    int close_index;

    for (int i = 0; i < *length && a[i] != '\n'; i++) {
        if (a[i] == ')') {
            close_index = i;
        } else {
            close_index = *length - 1;
        }
    }
    return close_index;
}

int check_first_number(char* a, int* open_index, int* error)
{
    int first_index = 0;

    for (int i = *open_index + 1; a[i] != ' '; i++) {
        if (*error == 0) {
            if (a[i] == ',') {
                *error = 1;
                printf("\nError at column %d: expected '<space>' and "
                       "'<double>'",
                       i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-'
                && a[i] != ' ') {
                *error = 1;
                printf("\nError at column %d: expected '<double>'", i);
                break;
            }
            first_index = i;
        } else
            break;
    }
    return first_index;
}

int check_second_number(char* a, int* first_index, int* error)
{
    int second_index = 0;
    for (int i = *first_index + 2; a[i] != ','; i++) {
        if (*error == 0) {
            if (a[i] == ')') {
                *error = 1;
                printf("\nError at column %d: expected ',' and '<double>'", i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-') {
                *error = 1;
                printf("\nError at column %d: expected '<double>' or ',' "
                       "token",
                       i);
                break;
            }
            second_index = i;
        } else
            break;
    }
    return second_index;
}

int check_third_number(char* a, int* second_index, int* close_index, int* error)
{
    int third_index = 0;

    for (int i = *second_index + 3; i < *close_index; i++) {
        if (*error == 0) {
            if ((isdigit(a[i]) == 0 && a[i] != '.') || a[i] == '0') {
                if (a[i] == ')' || a[i] == '(' || a[i] == ' ') {
                    break;
                }
                *error = 1;
                printf("\nError at column %d: expected '<double>'", i);
                break;
            }
            third_index = i;
        } else
            break;
    }
    return third_index;
}

int get_close_index(char* a, int* third_index, int* length, int* error)
{
    int close_index = 0;

    for (int i = *third_index + 1; i < *length; i++) {
        if (*error == 0) {
            if (a[i] != ')') {
                *error = 1;
                printf("\nError at column %d: expected ')'", i);
                break;
            } else {
                close_index = i;
                break;
            }
        } else
            break;
    }
    return close_index;
}

int check_unexpected_tokens(char* a, int* close_index, int* length, int* error)
{
    for (int i = *close_index + 1; i < *length; i++) {
        if (*error == 0) {
            if (a[i] == '\n') {
                break;
            }

            if (a[i] != ' ') {
                *error = 1;
                printf("\nError at column %d: unexpected token", i);
                break;
            }
        } else
            break;
    }
    return *error;
}

void parse_circle_expression(char a[], float x[], float y[], float rad[])
{
    float square, perimeter;
    char del[] = "circle( ,)";
    *x = atof(strtok(a, del));
    *y = atof(strtok(NULL, del));
    *rad = atof(strtok(NULL, del));
    square = M_PI * (*rad) * (*rad);
    perimeter = 2 * M_PI * (*rad);
    printf("circle(%.3f, %.3f, %.3f)\n", *x, *y, *rad);
    printf("square = %.3f\tperimeter = %.3f\n", square, perimeter);
}

void find_intersections(float* x, float* y, float* rad, int amount)
{
    int intersections = 0;
    printf("\nIntersections:");
    for (int i = 0; i < amount; i++) {
        intersections = 0;
        printf("\ncircle %d. intersects ", i);
        for (int j = 0; j < amount; j++) {
            double r = pow_custom((x[j] - x[i])) + pow_custom((y[j] - y[i]));
            r = sqrt(r);
            if (r == 0 && rad[i] == rad[j] && j != i) {
                intersections++;
                printf("circle %d.\t", j);
            }
            if (rad[i] + rad[j] >= r && rad[i] + r >= rad[j]
                && r + rad[j] >= rad[i] && j != i) {
                intersections++;
                printf("circle %d.\t", j);
            }
        }
    }
    if (intersections == 0) {
        printf("nothing");
    }
    puts("\n");
}
