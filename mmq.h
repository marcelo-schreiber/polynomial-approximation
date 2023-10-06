#include <stdlib.h>

/* Estrutura de um ponto */
typedef struct point
{
    double x;
    double y;
} point_t;

/* Esttura de pontos */
typedef struct points
{
    point_t *points;
    int num_of_points;
} points_t;

void aproximacao_polinomial_usando_mmq(points_t *points, unsigned int order);
