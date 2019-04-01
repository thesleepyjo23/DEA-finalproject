#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcs.h"

 void le_problema(FILE *fp, Matriz *M){

    int colunas;
    int linhas;
    int li, ci;
    int k;
    char var;
    int i;

    fscanf(fp, "%d %d %c %d %d %d", &colunas, &linhas, &var, &li, &ci, &k);

    M->colunas=colunas;
    M->linhas=linhas;
    M->var=var;
    M->li=li;
    M->ci=ci;
    M->k=k;

    printf("\n\n%d %d %c %d %d %d", colunas, linhas, var, li, ci, k);
 }

 void aloca_matriz(Matriz *M){

     int i;

    MAT->matriz = (int **) malloc( MAT->linhas*sizeof(int*) );
    for(i=0; i<MAT->linhas; i++)
        MAT->matriz[i]= (int*) malloc( MAT->colunas*sizeof(int));

 }


void liberta_matriz(){

    int i;

    for(i=0; i<MAT->linhas; i++)
        free(MAT->matriz[i]);

    free(MAT->matriz);
}