#include <stdio.h> /* printf */
#include <math.h>  /* nextafter e INFINITY */
#include <float.h> /* DBL_MIN, DBL_MAX e DBL_EPSILON */
#include <fenv.h>
#include <stdint.h>

typedef union
{
  double f;
  uint64_t u;
} DoubleIntUnion;

typedef struct
{
  double lower;
  double upper;
} Interval;

uint64_t convert_double_to_int64(double dbl);

double m(double x);
double M(double x);

Interval interval(double x);

Interval interval_sum(Interval a, Interval b);
Interval interval_sub(Interval a, Interval b);
Interval interval_mul(Interval a, Interval b);
Interval interval_div(Interval a, Interval b);
Interval apply_op(Interval a, Interval b, char op);
Interval interval_pow(Interval i, int p);
