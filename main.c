/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */

#include "mmq.h"
#include <stdio.h>

int main(void)
{

  int n, k, i;
  scanf("%d", &n);
  scanf("%d", &k);

  points_t *points = (points_t *)malloc(sizeof(points_t) * (k + 1));
  points->num_of_points = k - 1;
  points->points = (point_t *)malloc(points->num_of_points * sizeof(point_t));

  for (i = 0; i < points->num_of_points; i++)
  {
    scanf("%lf %lf\n", &(points->points[i].x), &(points->points[i].y));
  }

  aproximate_function_by_points_using_least_square(points, n - 1);

  return 0;
}

// return 0;
// // void aproximate_function_by_points_using_least_square(points_t *points, unsigned int order)

// points_t points;
// points.num_of_points = 11;
// points.points = (point_t *)malloc(points.num_of_points * sizeof(point_t));

// // 11 pontos
// points.points[0].x = 1872;
// points.points[0].y = 9.9;

// points.points[1].x = 1890;
// points.points[1].y = 14.3;

// points.points[2].x = 1900;
// points.points[2].y = 17.4;

// points.points[3].x = 1920;
// points.points[3].y = 30.6;

// points.points[4].x = 1940;
// points.points[4].y = 41.2;

// points.points[5].x = 1950;
// points.points[5].y = 51.9;

// points.points[6].x = 1960;
// points.points[6].y = 70.2;

// points.points[7].x = 1970;
// points.points[7].y = 93.1;

// points.points[8].x = 1980;
// points.points[8].y = 119.0;

// points.points[9].x = 1991;
// points.points[9].y = 146.2;

// points.points[10].x = 1996;
// points.points[10].y = 157.1;
