/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */

#include "main_io.h"

int main(void)
{
  int n, k;

  read_n_k(&n, &k);

  points_t *points = read_points(k);

  get_coeficients_by_least_square(points, n);

  free_points(points);

  return EXIT_SUCCESS;
}