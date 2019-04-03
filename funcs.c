#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcs.h"

#define MAX 2147483647

 FILE* abre_ficheiro(int argc, char *argv){

    FILE *fp;
    int x=0;

    if (argc != 2) {
        fprintf(stderr, "Modo de utilização: ./<nomedoexecutavel> <nomedoficheiro.puz0>\n");
        exit(1);
    }

    fp = fopen ( argv, "r" );
    if ( fp == NULL ) {
        fprintf ( stderr, "Erro ao abrir o ficheiro .puz0 '%s'\n", argv);
        exit ( 1 );
    }

    x=strlen(argv);

    printf("\n\n%d\n\n", x);

    if( (argv[x-5]!='.') || (argv[x-4]!='p') || (argv[x-3]!='u') || (argv[x-2]!='z') || (argv[x-1]!='0') ){

        fprintf(stderr, "Modo de utilização: ./<nomedoexecutavel> <nomedoficheiro.puz0>\n");
        exit (2);
    } 

    return fp;

 }

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

    printf("\n\n%d %d %c %d %d %d", linhas, colunas, var, li, ci, k);

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


void var_b(Matriz *M){

    static int movimentos[8][2] = {{-1,0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
    int l;
    int i, j;
    int min=MAX;
    int num_pares=0;

    /*casos fora do mapa*/
    if( (M->li<0) || (M->li>M->linhas) || (M->ci<0) || (M->ci>M->colunas) ){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        return;
    }

    for (l=0; l<8; l++) {
        i = M->li + movimentos[l][0];
        j = M->ci + movimentos[l][1];
        if (i < 0 || i >= M->linhas || j < 0 || j >= M->colunas) {
          continue;
        }
        
        if ( (M->matriz[i][j]%2==0) )
            num_pares++;

            
        if( (M->matriz[i][j]%2==0) && (M->matriz[i][j]<min) ){
            min=M->matriz[i][j];
        }
            
    }

    if(num_pares==0){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        return;
    }

    /*escrever 1 e o mínimo*/
    printf("\n\nnumeros pares:%d  valor minimo:%d\n\n", num_pares, min);
    

}


