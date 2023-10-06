/*

Autores:
Marcelo Augusto Rissette Schreiber GRR20220063
Felipe Quaresma Vieira GRR20215516

*/

#include "float_ops.h"
#include "mmq.h"
#include "utils.h"
#include "matrix.h"

//funcao read points
points_t *read_points(int n)
{
    points_t *points = (points_t *)malloc(sizeof(points_t) * (n + 1));
    points->num_of_points = n;
    points->points = (point_t *)malloc(points->num_of_points * sizeof(point_t));

    for (int i = 0; i < points->num_of_points; i++)
    {
        scanf("%lf %lf\n", &(points->points[i].x), &(points->points[i].y));
    }

    return points;
}

//funcao que cria Matrix A
Matrix cria_matrix_A(points_t *points, unsigned int order)
{
    int num_points = points->num_of_points;

    // Cria a matriz de coeficientes A e o vetor B
    Matrix A;
    A.size = order + 1;
    A.data = (Interval **)malloc(A.size * sizeof(Interval *));

    //Metodo dos minimos quadrados
    for (int i = 0; i < A.size; i++)
    {
        A.data[i] = (Interval *)malloc(A.size * sizeof(Interval));
        for (int j = 0; j < A.size; j++)
        {
            A.data[i][j] = interval(0.0);
            for (int k = 0; k < num_points; k++)
            {
                A.data[i][j] = interval_sum(A.data[i][j], interval_pow(interval(points->points[k].x), i + j));
            }
        }
    }

    return A;
}

//funcao que cria vetor B
Vector cria_vector_B(points_t *points, unsigned int order)
{
    int num_points = points->num_of_points;

    // Cria a matriz de coeficientes A e o vetor B
    Vector *b = (Vector *)malloc(sizeof(Vector));
    b->size = order + 1;
    b->data = (Interval *)malloc(b->size * sizeof(Interval));

    for (int i = 0; i < b->size; i++)
    {
        b->data[i] = interval(0.0);
        for (int k = 0; k < num_points; k++)
        {
            b->data[i] = interval_sum(b->data[i], interval_mul(interval_pow(interval(points->points[k].x), i), interval(points->points[k].y)));
        }
    }

    return *b;
}

//printa coeficientes
void print_coeficientes(Vector *b)
{
    for (int i = 0; i < b->size; i++)
    {
        printf("[%1.8e,%1.8e] ", b->data[i].lower, b->data[i].upper);
    }
    printf("\n");
}

//calcula e printa residuo
void print_residuo(points_t *points, Vector *b)
{
    int num_points = points->num_of_points;

    for (int i = 0; i < num_points; i++)
    {
        Interval sum = interval(0.0);
        for (int j = 0; j < b->size; j++)
        {
            sum = interval_sum(sum, interval_mul(b->data[j], interval_pow(interval(points->points[i].x), j)));
        }
        printf("[%1.8e,%1.8e] ", interval_sub(interval(points->points[i].y), sum).lower, interval_sub(interval(points->points[i].y), sum).upper);
    }
    printf("\n");
}
