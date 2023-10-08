/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */

#include "interval_operations.h"
#include <math.h>

uint64_t convert_double_to_int64(double dbl)
{
  DoubleIntUnion unionValue;
  unionValue.f = dbl;

  return unionValue.u;
}

double m(double x)
{
  return nextafter(x, DBL_MIN);
}

double M(double x)
{
  return x;
}

Interval interval(double x)
{
  Interval result;

  result.lower = m(x);
  result.upper = M(x);

  return result;
}

Interval interval_sum(Interval a, Interval b)
{
  Interval result;

  result.lower = m(a.lower + b.lower);
  result.upper = M(a.upper + b.upper);

  return result;
}

Interval interval_sub(Interval a, Interval b)
{
  Interval result;

  result.lower = m(a.lower - b.upper);
  result.upper = M(a.upper - b.lower);

  return result;
}

Interval interval_mul(Interval a, Interval b)
{
  Interval result;

  double products[4] = {a.lower * b.lower, a.lower * b.upper, a.upper * b.lower, a.upper * b.upper};

  result.lower = m(fmin(fmin(products[0], products[1]), fmin(products[2], products[3])));
  result.upper = M(fmax(fmax(products[0], products[1]), fmax(products[2], products[3])));

  return result;
}

Interval interval_div(Interval a, Interval b)
{
  Interval inverse;

  if (b.lower <= 0 && b.upper >= 0) // b contém 0
  {
    inverse.lower = -INFINITY;
    inverse.upper = INFINITY;
    return inverse;
  }

  inverse.lower = 1 / b.upper;
  inverse.upper = 1 / b.lower;

  return interval_mul(a, inverse);
}

// [a,b]p =    [1,1]                      se p = 0
//                  [ap,bp]                   se p é ímpar
//                  [ap,bp]                   se p é par e a ≥ 0
//                  [bp,ap]                   se p é par e b < 0
//                  [0,max{ap,bp}]     se p é par e a < 0 ≤ b
Interval interval_pow(Interval i, int p)
{
  Interval result;
  double a = i.lower;
  double b = i.upper;

  if (p == 0)
  {
    result = interval(1);
    return result;
  }

  if (p % 2 != 0)
  {
    result.lower = pow(a, p);
    result.upper = pow(b, p);
    return result;
  }

  if (a >= 0)
  {
    result.lower = pow(a, p);
    result.upper = pow(b, p);
    return result;
  }

  if (b < 0)
  {
    result.lower = pow(b, p);
    result.upper = pow(a, p);
    return result;
  }

  if (a < 0 && b >= 0)
  {
    result.lower = 0;
    result.upper = fmax(pow(a, p), pow(b, p));
    return result;
  }

  return result;
}

Interval apply_op(Interval a, Interval b, char op)
{
  printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] = \n", a.lower, a.upper, op, b.lower, b.upper);
  Interval res;

  if (op != '+' && op != '-' && op != '*' && op != '/')
  {
    printf("Operação inválida\n");
    return interval(0);
  }

  fesetround(FE_UPWARD);

  switch (op)
  {
  case '+':
    res = interval_sum(a, b);
    printf("[%1.8e,%1.8e]\n", res.lower, res.upper);
    break;
  case '-':
    res = interval_sub(a, b);
    printf("[%1.8e,%1.8e]\n", res.lower, res.upper);
    break;
  case '*':
    res = interval_mul(a, b);
    printf("[%1.8e,%1.8e]\n", res.lower, res.upper);
    break;
  case '/':
    res = interval_div(a, b);
    printf("[%1.8e,%1.8e]\n", res.lower, res.upper);
    break;
  }

  return res;
}

// int main(void)
// {
//   // 2.347e-40 * 0.001 + 1.1e+10 - 0.75e-39 / 0.0
//   double a, b, c, d, e;
//   char op1, op2, op3, op4;

//   scanf("%lf %c %lf %c %lf %c %lf %c %lf", &a, &op1, &b, &op2, &c, &op3, &d, &op4, &e);

//   printf("1: \n");
//   Interval first = interval(a);
//   Interval result = apply_op(first, interval(b), op1);
//   printf("2: \n");
//   result = apply_op(result, interval(c), op2);
//   printf("3: \n");
//   result = apply_op(result, interval(d), op3);
//   printf("4: \n");
//   result = apply_op(result, interval(e), op4);

//   return 0;
// }