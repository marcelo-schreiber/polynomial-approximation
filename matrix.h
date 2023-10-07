#include "float_operations.h"
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
  size_t size;
  Interval **data;
} Matrix;

typedef struct
{
  size_t size;
  Interval *data;
} Vector;

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

void triangulate_matrix_by_gauss(Matrix *m, Vector *c);
Vector *get_solution_by_substitution(Matrix m, Vector c);

Matrix* initialize_matrix(unsigned int order);
Vector* initialize_vector(unsigned int order);

void print_vector(Vector v);

void free_matrix(Matrix *A);
void free_vector(Vector *b);