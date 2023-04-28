#pragma once

#define RESET "\033[0m"
#define RED "\033[1;31m"

int BasicChecker(
    char *str, long int len, char *name, long int *column, int *type_id);
int BracketsChecker(char *str, long int name_len, long int *column);
int NameChecker(char *str, long int *column, int *type_id);
int UnexpectedTokenChecker(char *str, long int *column);
int CircleContentChecker(char *str, long int len);
int isNumber(char *str);
void ErrorOutput(int error_num, int line, long int column);

typedef struct
{
    float x;
    float y;
} Point;

typedef struct
{
    Point center;
    float radius;
    float perimeter;
    float area;
    int *intersects;
} Circle;

Circle *CircleExtractor(char *str, long int len);
double CircleAreaCalc(double radius);
double CirclePerimeterCalc(double radius);
