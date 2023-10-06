#include "matrix.h"
#include "mmq.h"

void aproximate_function_by_points_using_least_square(points_t *points, unsigned int order)
{
    int num_points = points->num_of_points;

    // Create the coefficient matrix (A) and the right-hand side vector (b)
    Matrix A;
    Vector *b = (Vector *)malloc(sizeof(Vector));
    A.size = order + 1;
    A.data = (Interval **)malloc(A.size * sizeof(Interval *));
    b->size = order + 1;
    b->data = (Interval *)malloc(b->size * sizeof(Interval));

    for (int i = 0; i < A.size; i++)
    {
        A.data[i] = (Interval *)malloc(A.size * sizeof(Interval));
        for (int j = 0; j < A.size; j++)
        {
            A.data[i][j] = interval(0.0);
            for (int k = 0; k < num_points; k++)
            {
                // A.data[i][j] = interval_sum(A.data[i][j], interval(pow(points->points[k].x, i + j)));
                A.data[i][j] = interval_sum(A.data[i][j], interval_pow(interval(points->points[k].x), i + j));
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

    // Solve the linear system using Gauss elimination with pivoting
    gaussEliminationWithPivoting(&A, b);
    b = printSolutionBySubstitution(A, *b);
    // The solution in the 'b' vector now contains the coefficients of the polynomial
    // You can use these coefficients to construct the polynomial function

    // print the solution
    printf("Final solution:\n");
    for (int i = 0; i < b->size; i++)
    {
        printf("b[%d] = [%1.16e, %1.16e]\n", i, b->data[i].lower, b->data[i].upper);
    }

    printf("residuals:\n");

    for (int i = 0; i < num_points; i++)
    {
        Interval sum = interval(0.0);
        for (int j = 0; j < b->size; j++)
        {
            sum = interval_sum(sum, interval_mul(b->data[j], interval_pow(interval(points->points[i].x), j)));
        }
        printf("r[%d] = [%f, %f]\n", i, interval_sub(interval(points->points[i].y), sum).lower, interval_sub(interval(points->points[i].y), sum).upper);
    }

    // Clean up memory
    for (int i = 0; i < A.size; i++)
    {
        free(A.data[i]);
    }
    free(A.data);
    free(b->data);
}