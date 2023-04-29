#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/geometry.h>
#include <libgeometry/errors.h>

#define M_PI 3.14159265358979323846

Circle *CircleExtractor(char *str, long int len)
{
    Circle *temporary = (Circle *)malloc(sizeof(Circle));
    char *bracket_open_first = strchr(str, '(');
    char *bracket_closed_last = strrchr(str, ')');
    int i, j;
    char container[len], *istr;
    char sep[2] = ", ";

    for (i = bracket_open_first - str + 1, j = 0; i < bracket_closed_last - str;
         i++, j++)
    {
        container[j] = str[i];
    }
    container[j] = '\0';

    istr = strtok(container, sep);
    temporary->center.x = atof(istr);
    istr = strtok(0, sep);
    temporary->center.y = atof(istr);
    istr = strtok(0, sep);
    temporary->radius = atof(istr);

    return temporary;
}

double CircleAreaCalc(double radius)
{
    double area = M_PI * radius * radius;
    return area;
}

double CirclePerimeterCalc(double radius)
{
    double perimeter = 2 * M_PI * radius;
    return perimeter;
}
int BasicChecker(char *str, long int len, char *name, long int *column)
{
    int error_num = 0;

    error_num = NameChecker(name, column);
    if (error_num == 0)
    {
        error_num = BracketsChecker(str, strlen(name) - 1, column);
        if (error_num == 0)
        {
            error_num = UnexpectedTokenChecker(str, column);
        }
    }
    return error_num;
}

int BracketsChecker(char *str, long int name_len, long int *column)
{
    int column_func = 0;
    int error_column_open;
    int error_column_close;
    int column_flag = 0;
    int error_flag_brackets = 0;
    int stack = 0;
    do
    {
        if (*str == '(')
        {
            error_column_open = column_func;
            column_flag = 1;
            stack++;
            str++;
        }
        else
        {
            if (*str == ')')
            {
                error_column_close = column_func;
                if (--stack < 0)
                {
                    if (column_flag == 1)
                    {
                        error_flag_brackets = 1;
                        *column = error_column_open + 1;
                        break;
                    }
                    else if (column_flag == 0)
                    {
                        error_flag_brackets = 1;
                        *column = name_len;
                        break;
                    }
                }
            }
            str++;
        }
        column_func++;
    } while (*str);
    if (stack > 0)
    {
        error_flag_brackets = 5;
        *column = error_column_close + 1;
    }
    return error_flag_brackets;
}

int NameChecker(char *str, long int *column)
{
    char figure_name[][10] = {"circle", "triangle", "polygon"};
    int i, error_flag_name = 2;
    for (i = 0; i < 3; i++)
    {
        if (strncmp(str, figure_name[i], strlen(figure_name[i])) == 0)
        {
            error_flag_name = 0;
        }
    }
    if (error_flag_name != 0)
        *column = 0;
    return error_flag_name;
}

int UnexpectedTokenChecker(char *str, long int *column)
{
    int error_flag_token = 0;

    char *bracket_closed_last;

    bracket_closed_last = strrchr(str, ')');

    if (bracket_closed_last - str + 2 != strlen(str))
    {
        error_flag_token = 3;
        *column = bracket_closed_last - str + 1;
    }

    return error_flag_token;
}

int isNumber(char *str)
{
    int floating_point = 0;
    int i;
    int minus = 0;
    int error_flag_container = 0;
    int len = strlen(str);

    for (i = 0; i < len; i++)
    {
        if ((i == 0) && (str[i] == '-'))
        {
            minus = 1;
            continue;
        }
        else if ((isdigit(str[minus]) == 0) || (isdigit(str[len - 1]) == 0))
        {
            error_flag_container = 4;
            break;
        }
        else if (((i > minus) || (i < len - 1)) && (str[i] == '.'))
        {
            floating_point++;
            if (floating_point > 1)
            {
                error_flag_container = 4;
                break;
            }
        }
        else if (
            ((i > minus) || (i < len - 1)) && ((isdigit(str[i]) == 0) && (str[i] != '.')))
        {
            error_flag_container = 4;
            break;
        }
    }
    return error_flag_container;
}

int CircleContentChecker(char *str, long int len)
{
    char *bracket_open_first = strchr(str, '(');
    char *bracket_closed_last = strrchr(str, ')');
    int i, j, error_extract = 0;
    char container[len], *istr;
    char sep[2] = ", ";

    for (i = bracket_open_first - str + 1, j = 0; i < bracket_closed_last - str;
         i++, j++)
    {
        container[j] = str[i];
    }
    container[j + 1] = '\0';

    istr = strtok(container, sep);
    error_extract = isNumber(istr);
    if (error_extract == 0)
    {
        istr = strtok(0, sep);
        error_extract = isNumber(istr);
        if (error_extract == 0)
        {
            istr = strtok(0, sep);
            error_extract = isNumber(istr);
            if (error_extract == 0)
            {
                istr = strtok(0, sep);
                if (istr)
                    error_extract = 6;
            }
        }
    }

    return error_extract;
}

void ErrorOutput(int error_num, int line, long int column)
{
    switch (error_num)
    {
    case 1:
        printf("%sError: expected '(' [line %d column "
               "%ld]%s\n",
               RED,
               line,
               column,
               RESET);
        break;
    case 2:
        printf("%sError: expected 'circle', 'triangle' or "
               "'polygon' [line "
               "%d "
               "column %ld]%s\n",
               RED,
               line,
               column,
               RESET);
        break;
    case 3:
        printf("%sError: unexpected token [line %d "
               "column %ld]%s\n",
               RED,
               line,
               column,
               RESET);
        break;
    case 4:
        printf("%sError: expected <double> in brackets [line "
               "%d]%s\n",
               RED,
               line,
               RESET);
        break;
    case 5:
        printf("%sError: expected ')' [line %d column %ld]%s\n",
               RED,
               line,
               column,
               RESET);
        break;
    case 6:
        printf("%sError: unexpected token in brackets [line "
               "%d]%s\n",
               RED,
               line,
               RESET);
        break;
    default:
        break;
    }
}
int main()
{
    FILE *geometry;

    Circle circles[20];
    Circle *tmp_circle;

    char str1[MAX_SIZE];
    char figure_name[][10] = {"circle", "triangle", "polygon"};

    int line, error_num = 0, id_circle = 0;

    geometry = fopen("../res/geometry.txt", "r");

    if (geometry == NULL)
    {
        printf("FILE READ ERROR!");
    }
    else
    {
        line = 1;
        while (!feof(geometry))
        {
            if (fgets(str1, MAX_SIZE, geometry) != NULL)
            {
                int len = strlen(str1);
                char name[len];
                long int column = 0;
                printf("%d. %s", line, str1);

                for (int i = 0; i < len; i++)
                {
                    if (str1[i] == '(')
                    {
                        name[i] = '\0';
                        break;
                    }
                    name[i] = tolower(str1[i]);
                }

                error_num = BasicChecker(str1, len, name, &column);

                if (error_num == 0)
                {
                    if (strncmp(name, figure_name[0], strlen(figure_name[0])) == 0)
                    {
                        error_num = CircleContentChecker(str1, len);
                        if (error_num == 0)
                        {
                            tmp_circle = CircleExtractor(str1, len);
                            circles[id_circle] = *tmp_circle;
                            id_circle++;
                        }
                    }
                }
                if (error_num != 0)
                {
                    ErrorOutput(error_num, line, column);
                }
                line++;
            }
        }
        fclose(geometry);
    }

    puts("\nOutput");
    for (int i = 0; i < id_circle; i++)
    {
        circles[i].area = CircleAreaCalc(circles[i].radius);
        circles[i].perimeter = CirclePerimeterCalc(circles[i].perimeter);
        printf("\n%d. circle(%.1lf %.1lf, %.1lf)\n\tperimeter = %.1lf\n\tarea "
               "= %.1lf\n",
               i + 1,
               circles[i].center.x,
               circles[i].center.y,
               circles[i].radius,
               circles[i].perimeter,
               circles[i].area);
    }
    return 0;
}
