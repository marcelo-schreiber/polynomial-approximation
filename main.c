/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */

int main(void)
{

  int n, k, i;
  scanf("%d", &n);
  scanf("%d", &k);

  double x[k], y[k];

  for(i = 0; i < k; i++){
    scanf("%lf %lf", &x[i], &y[i]);
  }

  double coefficients[n+1];

  ajusteMinimosQuadrados(k, x, y, n, coefficients);


  for(i = 0; i <= n; i++){
    printf("%.10lf\n", coefficients[i]);
  }

  double res[k];

  for(i = 0; i < k; i++){
    res[i] = y[i] - f(x[i], coefficients, n);
  }

  for(i = 0; i < k; i++){
    printf("%.10lf\n", res[i]);
  }

  return 0;
}
