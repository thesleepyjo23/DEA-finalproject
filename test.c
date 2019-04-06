#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void aloca_matriz(int **matriz, int linhas, int colunas){

    int i;
    
    matriz = (int **) malloc( linhas*sizeof(int*) );
    
    for(i=0; i<linhas; i++)
        matriz[i]= (int*) malloc( colunas*sizeof(int));

 }

void preenche_matriz(int **matriz, int linhas, int colunas){

    int i, j;
    int num=1;

    for(i=0; i<linhas; i++){

        for(j=0; j<colunas; j++){
            matriz[i][j]=num;
            num++;
        }
                     
    }

}

void liberta_matriz (int **matriz, int linhas, int colunas){

    int i;

    for(i=0; i<linhas; i++)
        free(matriz[i]);

    free(matriz);

}


int main(void){

    int **matriz=NULL;
    int i, j;

  
    aloca_matriz(matriz, 3, 3);

    preenche_matriz(matriz, 3, 3);

    for(i=0; i<3; i++){

        for(j=0; j<3; j++)
            printf("\ni=%d, j=%d e valor=%d\n", i, j, matriz[i][j]);
            
                     
    }

    liberta_matriz(matriz, 3, 3);

}