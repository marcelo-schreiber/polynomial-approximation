#include <stdio.h>
#include <stdlib.h>

//funcao para calcular os coeficientes do polinomio de grau N
void ajusteMinimosQuadrados(int n, double x[], double y[], int degree, double coefficients[]){

    double A[degree+1][degree+2];
    memset(A, 0, sizeof(A));
    
    int i, j, k;

    //Preenche a matriz A com os somatórios necessários
    for(i = 0; i <= degree; i++){
        for(j = 0; j <= degree; j++){
            for(k = 0; k < n; k++){
                A[i][j] += pow(x[k], i+j);
            }
        }
    }

    //Preenche a última coluna de A com os somatórios necessários
    for(i = 0; i <= degree; i++){
        for(k = 0; k < n; k++){
            A[i][degree+1] += y[k] * pow(x[k], i);
        }
    }

    //Eliminação de Gauss
    for(i = 0; i < degree; i++){
        for(j = i+1; j <= degree; j++){
            double m = A[j][i]/A[i][i];
            for(k = 0; k <= degree+1; k++){
                A[j][k] -= m * A[i][k];
            }
        }
    }

    //Substituição retroativa
    for(i = degree; i >= 0; i--){
        coefficients[i] = A[i][degree+1];
        for(j = i+1; j <= degree; j++){
            coefficients[i] -= A[i][j] * coefficients[j];
        }
        coefficients[i] /= A[i][i];
    }

    //Os coeficientes do polinomio são armazenados no vetor coefficients
    for(i = 0; i <= degree; i++){
        coefficients[i] = A[i][degree+1];
    }

}
