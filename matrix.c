/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */

#include "matrix.h"

size_t findMax(Matrix m, size_t i)
{
  size_t max = i;

  for (size_t j = i + 1; j < m.size; j++)
  {
    if (fabs(m.data[j][i].upper) > fabs(m.data[max][i].upper)) // get just the upper
    {
      max = j;
    }
  }

  return max;
}

void switchLine(Matrix *m, Vector *c, size_t i, size_t max)
{
  Interval *temp = m->data[i];
  m->data[i] = m->data[max];
  m->data[max] = temp;

  Interval t = c->data[i];
  c->data[i] = c->data[max];
  c->data[max] = t;
}

void gaussEliminationWithPivoting(Matrix *m, Vector *c)
{
  for (size_t i = 0; i < m->size; i++)
  {
    size_t max = findMax(*m, i);

    if (max != i)
    { // switch line
      switchLine(m, c, i, max);
    }

    for (size_t j = i + 1; j < m->size; j++)
    {
      // Interval mult = m->data[j][i] / m->data[i][i];
      Interval mult = interval_div(m->data[j][i], m->data[i][i]);

      m->data[j][i].lower = 0.0; // [j][i] = 0
      m->data[j][i].upper = 0.0;

      for (size_t k = i + 1; k < m->size; k++)
      {
        // m->data[j][k] -= mult * m->data[i][k];
        m->data[j][k] = interval_sub(m->data[j][k], interval_mul(mult, m->data[i][k]));
      }

      // c->data[j] -= mult * c->data[i];
      c->data[j] = interval_sub(c->data[j], interval_mul(mult, c->data[i]));
    }
  }
}

void printVector(Vector v)
{
  for (size_t i = 0; i < v.size; i++)
  {
    printf("[%lf, %lf]", v.data[i].upper, v.data[i].lower);
  }
  printf("\n");
}

Vector *printSolutionBySubstitution(Matrix m, Vector c)
{
  Vector *solution = (Vector *)malloc(sizeof(Vector));
  solution->size = m.size;
  solution->data = (Interval *)malloc(solution->size * sizeof(Interval));

  for (int i = m.size - 1; i >= 0; i--)
  {

    Interval sum = interval(0.0);

    for (size_t j = i + 1; j < m.size; j++)
      sum = interval_sum(sum, interval_mul(m.data[i][j], solution->data[j]));

    solution->data[i] = interval_div(interval_sub(c.data[i], sum), m.data[i][i]);
  }

  return solution;
}

int testeGauss(void)
{
  Matrix m;
  Vector c;

  m.size = 3;
  m.data = malloc(m.size * sizeof(Interval *));
  for (size_t i = 0; i < m.size; i++)
  {
    m.data[i] = malloc(m.size * sizeof(Interval));
  }

  c.size = 3;
  c.data = malloc(c.size * sizeof(Interval));

  // x + 2y - 2z = -15
  // 2x + y - 5z = -21
  // x - 4y + z = 18

  m.data[0][0] = interval(1.0);
  m.data[0][1] = interval(2.0);
  m.data[0][2] = interval(-2.0);

  printf("%.24f\n", m.data[0][0].upper);
  printf("%.24f\n", m.data[0][0].lower);

  m.data[1][0] = interval(2.0);
  m.data[1][1] = interval(1.0);
  m.data[1][2] = interval(-5.0);

  m.data[2][0] = interval(1.0);
  m.data[2][1] = interval(-4.0);
  m.data[2][2] = interval(1.0);

  c.data[0] = interval(-15.0);
  c.data[1] = interval(-21.0);
  c.data[2] = interval(18.0);

  gaussEliminationWithPivoting(&m, &c);
  printSolutionBySubstitution(m, c);

  return 0;
}
