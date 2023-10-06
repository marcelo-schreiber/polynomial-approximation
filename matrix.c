/*

Autores:
Marcelo Augusto Rissette Schreiber GRR20220063
Felipe Quaresma Vieira GRR20215516

*/

#include "matrix.h"

/* Encontra o maior elemento da coluna */
size_t findMax(Matrix m, size_t i){

    size_t max = i;

    for(size_t j = i + 1; j < m.size; j++){
        if (fabs(m.data[j][i].upper) > fabs(m.data[max][i].upper))
            max = j;
    }

    return max;
}

/* Troca linha da matriz */
void switchLine(Matrix *m, Vector *c, size_t i, size_t max)
{
  Interval *temp = m->data[i];
  m->data[i] = m->data[max];
  m->data[max] = temp;

  Interval t = c->data[i];
  c->data[i] = c->data[max];
  c->data[max] = t;
}

/* Eliminação de Gauss com Pivoteamento */
void gaussEliminationWithPivoting(Matrix *m, Vector *c)
{
  for (size_t i = 0; i < m->size; i++)
  {

    // Encontra o maior elemento da coluna
    size_t max = findMax(*m, i);

    if (max != i)
    { // troca as linhas
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

/* Imprime um vetor */
void printVector(Vector v)
{
  for (size_t i = 0; i < v.size; i++)
  {
    printf("[%lf, %lf]", v.data[i].upper, v.data[i].lower);
  }
  printf("\n");
}

/* Imprime a solução por substituição */
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
