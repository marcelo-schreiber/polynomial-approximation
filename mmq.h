#include <stdlib.h>

typedef struct point
{
    double x;
    double y;
} point_t;

typedef struct points
{
    point_t *points;
    int num_of_points;
} points_t;

void aproximate_function_by_points_using_least_square(points_t *points, unsigned int order);