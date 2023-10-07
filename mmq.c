#include "mmq.h"
#include <stdio.h>

void print_residue(points_t *points, Vector *b)
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

void aproximate_function_by_points_using_least_square(points_t *points, unsigned int order)
{
    int num_points = points->num_of_points;

    // Create the coefficient matrix (A) and the right-hand side vector (b)
    Matrix *A = initialize_matrix(order);
    Vector *b = initialize_vector(order); 

    for (int i = 0; i < A->size; i++)
    {
        for (int j = 0; j < A->size; j++)
        {
            A->data[i][j] = interval(0.0);
            for (int k = 0; k < num_points; k++)
            {
                // A->data[i][j] = interval_sum(A->data[i][j], interval(pow(points->points[k].x, i + j)));
                A->data[i][j] = interval_sum(A->data[i][j], interval_pow(interval(points->points[k].x), i + j));
            }
        }
    }

    for (int i = 0; i < b->size; i++)
    {
        b->data[i] = interval(0.0);
        for (int k = 0; k < num_points; k++)
        {
            // b->data[i] = interval_sum(b->data[i], interval_mul(interval(pow(points->points[k].x, i)), interval(points->points[k].y)));
            b->data[i] = interval_sum(b->data[i], interval_mul(interval_pow(interval(points->points[k].x), i), interval(points->points[k].y)));
        }
    }

    triangulate_matrix_by_gauss(A, b);
    b = get_solution_by_substitution(*A, *b);

    print_vector(*b);

    print_residue(points, b);

    // Clean up memory
    free_matrix(A);
    free_vector(b);
}