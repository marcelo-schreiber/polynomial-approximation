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

void gaussEliminationWithPivoting(Matrix *m, Vector *c);
Vector *printSolutionBySubstitution(Matrix m, Vector c);
int testeGauss(void);