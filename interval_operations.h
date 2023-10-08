#include <stdio.h> /* printf */
#include <math.h>  /* nextafter e INFINITY */
#include <float.h> /* DBL_MIN, DBL_MAX e DBL_EPSILON */
#include <fenv.h>
#include <stdint.h>

/* Estrutura que auxilia na conversão double->float */
typedef union
{
  double f;
  uint64_t u;
} DoubleIntUnion;

/* estrutura do intervalo de um double */
typedef struct
{
  double lower;
  double upper;
} Interval;

/* função da conversão double->float */
uint64_t convert_double_to_int64(double dbl);

/* intervalo inferior */
double m(double x);
/* intervalo superior */
double M(double x);

/* função que cria o intervalo de um double */
Interval interval(double x);

/* operação de soma de intervalos */
Interval interval_sum(Interval a, Interval b);

/* operação de subtração de intervalos */
Interval interval_sub(Interval a, Interval b);

/* operação de multiplicação */
Interval interval_mul(Interval a, Interval b);

/* operação de divisão de intervalos */
Interval interval_div(Interval a, Interval b);

/* operação de potenciação de um intervalo */
Interval interval_pow(Interval i, int p);
