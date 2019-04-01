#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcs.h"

 int le_problema(FILE *fp, Matriz *M){

    int colunas;
    int linhas;
    int li, ci;
    int k;
    int check;
    char var;

    check = fscanf(fp, "%d %d %c %d %d %d", &linhas, &colunas, &var, &li, &ci, &k);

    if(check!=6){

        return 0;
    }

    M->colunas=colunas;
    M->linhas=linhas;
    M->var=var;
    M->li=li;
    M->ci=ci;
    M->k=k;

    printf("\n\n%d %d %c %d %d %d", colunas, linhas, var, li, ci, k);

    return 1;
 }

 void aloca_matriz(Matriz *M){

    int i;

    M->matriz = (int **) malloc( M->linhas*sizeof(int*) );
    
    for(i=0; i<M->linhas; i++)
        M->matriz[i]= (int*) malloc( M->colunas*sizeof(int));

 }


void liberta_matriz(Matriz *M){

    int i;

    for(i=0; i<M->linhas; i++)
        free(M->matriz[i]);

    free(M->matriz);
}

void preenche_matriz(FILE *fp, Matriz *M){

    int i, j;

    for(i=0; i<M->linhas; i++){

        for(j=0; j<M->colunas; j++){

            fscanf(fp, "%d", &M->matriz[i][j]);
            
        }
    }

    for(i=0; i<M->linhas; i++){
        printf("\n");
        for(j=0; j<M->colunas; j++){

            printf( "%d ", M->matriz[i][j]);
            
        }
    }

}



