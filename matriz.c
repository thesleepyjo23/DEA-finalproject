
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "matriz.h"
#include "funcs.h"



/*função que aloca memória para uma matriz de dimensão "linhas" x "colunas"*/
 int **aloca_matriz(int **matriz, int linhas, int colunas){

    int i;

    matriz = (int **) malloc( linhas*sizeof(int*) );

    for(i=0; i<linhas; i++)
        matriz[i]= (int*) malloc( colunas*sizeof(int));


    return matriz;
 }

/*função que preenche a matriz tendo em conta o que é lido no ficheiro*/
int **preenche_matriz(FILE *fpIn, int **matriz, int linhas, int colunas){

    int i=0, j=0;
    int check;

    for(i=0; i<linhas; i++){

        for(j=0; j<colunas; j++){

            check=fscanf(fpIn, "%d", &matriz[i][j]);
            if (check==0) {
              exit(0);
              }

        }
    }

    return matriz;

}

int **preenche_mat_zeros(int **matriz, int linhas, int colunas){

    int i, j;

    for (i=0; i<linhas; i++){

        for(j=0; j<colunas; j++){
            matriz[i][j]=0;
        }
    }

    return matriz;
}

/*função que liberta a memória alocada anteriormente da matriz*/
 int **liberta_matriz (int **matriz, int linhas, int colunas){

    int i;

    for(i=0; i<linhas; i++)
        free(matriz[i]);

    free(matriz);

    return matriz;

}

int max_matriz(int **matriz, int *x, int *y){

    int i, j;
    int max=INT_MIN;
    int linhas=*x, colunas=*y;

    for (i=0; i<linhas; i++){

        for(j=0;j<colunas; j++){

            if(matriz[i][j]>max){
                max=matriz[i][j];
                *x=i;
                *y=j;
            }
        }
    }

    return max;
}
