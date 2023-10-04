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
