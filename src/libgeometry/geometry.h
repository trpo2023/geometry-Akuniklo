#pragma once

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
