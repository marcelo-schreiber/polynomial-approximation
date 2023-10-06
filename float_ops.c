/*

Autores:
Marcelo Augusto Rissette Schreiber GRR20220063
Felipe Quaresma Vieira GRR20215516

*/

#include "float_operations.h"
#include <math.h>

/* Converte um valor double em um valor uint64_t */
uint64_t convert_double_to_int64(double dbl)
{
  DoubleIntUnion unionValue;
  unionValue.f = dbl;

  return unionValue.u;
}

/* Retorna parte inferior do intervalo */
double m(double x){
    return nextafter(x, DBL_MIN);
}

/* Retorna parte superior do intervalo */
double M(double x){
    return x;
}

/* Retorna um intervalo */
Interval interval(double x){

    Interval result;

    result.lower = m(x);
    result.upper = M(x);

    return result;

}

/* Retorna a soma de dois intervalos */
Interval interval_sum(Interval a, Interval b){

    Interval result;

    result.lower = m(a.lower + b.lower);
    result.upper = M(a.upper + b.upper);

    return result;

}

/* Retorna a subtração de dois intervalos */
Interval interval_sub(Interval a, Interval b){

    Interval result;

    result.lower = m(a.lower - b.upper);
    result.upper = M(a.upper - b.lower);

    return result;

}

/* Retorna a multiplicação de dois intervalos */
Interval interval_mul(Interval a, Interval b){

    Interval result;

    double products[4] = {a.lower * b.lower, a.lower * b.upper, a.upper * b.lower, a.upper * b.upper};

    result.lower = m(fmin(fmin(products[0], products[1]), fmin(products[2], products[3])));
    result.upper = M(fmax(fmax(products[0], products[1]), fmax(products[2], products[3])));

    return result;

}

/* Retorna a divisão de dois intervalos */
Interval interval_div(Interval a, Interval b){

    Interval inverse;

    if (b.lower <= 0 && b.upper >= 0) // b contém 0
    {
        inverse.lower = DBL_MIN;
        inverse.upper = DBL_MAX;
    }
    else
    {
        inverse.lower = 1 / b.upper;
        inverse.upper = 1 / b.lower;
    }

    return interval_mul(a, inverse);

}

/* Retorna a potenciacao de um intervalo */
Interval interval_pow(Interval i, int p){

    Interval result;
    double a = i.lower;
    double b = i.upper;

    if (p == 0){
        result = interval(1);
        return result;
    }

    if (p % 2 != 0){
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
