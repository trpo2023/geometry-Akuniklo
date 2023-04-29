#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/errors.h>
#include <libgeometry/geometry.h>

#define MAX_SIZE 300

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