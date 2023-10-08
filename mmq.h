#include "matrix.h"

Vector* solve_system(Matrix *A, Vector *b);
void generate_matrix(Matrix *A, Vector *b, points_t *points, unsigned int order);
void print_residue(points_t *points, Vector *b);