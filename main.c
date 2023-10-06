/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */

#include "mmq.h"
#include "auxiliares.h"
#include <stdio.h>

int main(void)
{

  int n, k, i;
  read_n_k(&n, &k);

  points_t *points = read_points(n);

  aproximate_function_by_points_using_least_square(points, n - 1);

  return 0;
}
