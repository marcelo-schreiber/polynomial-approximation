#include "float_ops.h"
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdint.h>

/* Estrutura da matriz */
typedef struct
{
  size_t size;
  Interval **data;
} Matrix;

/* Estrutura do Vetor */
typedef struct
{
  size_t size;
  Interval *data;
} Vector;

void gaussEliminationWithPivoting(Matrix *m, Vector *c);
Vector *printSolutionBySubstitution(Matrix m, Vector c);
int testeGauss(void);
