#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//funcao para calcular os coeficientes do polinomio de grau N
void ajusteMinimosQuadrados(int n, double x[], double y[], int degree, double coefficients[]){

    int i, j, k;

    //aloca matriz A
    double **A = (double **)malloc((degree+1) * sizeof(double *));
    for(i = 0; i <= degree; i++){
        A[i] = (double *)malloc((degree+2) * sizeof(double));
    }

    //inicializa matriz A
    for(i = 0; i <= degree; i++){
        for(j = 0; j <= degree+1; j++){
            A[i][j] = 0;
        }
    }

    for(i = 0; i < degree; i++){
        for(j = 0; j < degree; ++j){
            for(k = 0; k < n; ++k){
                A[i][j] += pow(x[k], i+j);
                printf("\n A[%d][%d] = %lf \n", i, j, A[i][j]);
            }
        }

        for(k = 0; k < n; ++k){
            A[i][degree] += pow(x[k], i) * y[k];
            printf("\n A[%d][%d] = %lf \n", i, degree, A[i][degree]);
        }
    }

    printf("\n");

    //printa matriz A
    for(i = 0; i <= degree; i++){
        for(j = 0; j <= degree+1; j++){
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    //eliminacao de gauss com pivoteamento
    for(int i = 0; i < degree; i++){
        double max = A[i][i];
        int maxIndex = i;
        for(int j = i+1; j < degree; j++){
            if(A[j][i] > max){
                max = A[j][i];
                maxIndex = j;
            }
        }
        if(maxIndex != i){
            for(int k = 0; k <= degree+1; k++){
                double aux = A[i][k];
                A[i][k] = A[maxIndex][k];
                A[maxIndex][k] = aux;
            }
        }
        for(int j = i+1; j < degree; j++){
            double m = A[j][i]/A[i][i];
            for(int k = 0; k <= degree+1; k++){
                A[j][k] -= m * A[i][k];
                printf("\n A[%d][%d] = %lf \n", j, k, A[j][k]);
            }
        }

    }

    //printa matriz A
    for(i = 0; i <= degree; i++){
        for(j = 0; j <= degree+1; j++){
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    //retrosubstituicao

    for(int i = degree-1; i >= 0; i--){
        double sum = 0;
        for(int j = i+1; j <= degree; j++){
            sum += A[i][j] * coefficients[j];
            printf("\n sum = %lf \n", sum);
        }
        
        coefficients[i] = (A[i][degree] - sum)/A[i][i];
        printf("\n coefficients[%d] = %lf \n", i, coefficients[i]);
        
    }
    

    printf("\n");

    //printa coeficientes
    for(i = 0; i <= degree; i++){
        printf("%lf ", coefficients[i]);
    }

    printf("\n");
    
    //libera memoria
    for(i = 0; i <= degree; i++){
        free(A[i]);
    }
    
}

//funcao teste para testar ajusteminimoquadrado
void testeAjusteMinimosQuadrados(){
    int n = 5;
    double x[] = {1, 2, 3, 4, 5};
    double y[] = {1, 2, 3, 4, 5};
    int degree = 2;
    double coefficients[degree+1];
    ajusteMinimosQuadrados(n, x, y, degree, coefficients);
    printf("\n");
}

int main(){
    testeAjusteMinimosQuadrados();
    return 0;
}

