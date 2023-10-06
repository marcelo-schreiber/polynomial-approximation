/*

Autores:
Marcelo Augusto Rissette Schreiber GRR20220063
Felipe Quaresma Vieira GRR20215516

*/

#include "matrix.h"
#include "mmq.h"
#include "auxliares.h"

/* Aproximação polinomial usando o metodo dos minimos quadrados */
void aproximacao_polinomial_usando_mmq(points_t *points, unsigned int order)
{
    int num_points = points->num_of_points;

    // Cria a matriz de coeficientes A e o vetor B
    Matrix A = cria_matrix_A(points, order);
    Vector *b = cria_vector_B(points, order);

    // Resolução do sistema linear usando a eliminação de Gauss com pivoteamento
    gaussEliminationWithPivoting(&A, b);
    b = printSolutionBySubstitution(A, *b);

    /* Printa os coeficientes em formato de intervalo */
    print_coeficientes(Vector *b);
    
    /* Calcula e printa residuo */
    print_residuo(points, Vector *b);

    // Limpa memoria
    for (int i = 0; i < A.size; i++)
    {
        free(A.data[i]);
    }
    free(A.data);
    free(b->data);
}
