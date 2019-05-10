#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcs.h"


 /*
 *  Function:
 *    main()
 *
 */
int main(int argc, char *argv[]) {

    Matriz MAT;
    Resultado RES;
    FILE *fpIn, *fpOut;
    int aux=0;
    char *nome_ficheiro_saida={NULL};
    int check;

    fpIn = abre_ficheiro( argc, argv[1]);

    nome_ficheiro_saida = Muda_extensao(argv[1], Extensao_fpOut);
    fpOut = fopen(nome_ficheiro_saida, "w");
    if (fpOut ==NULL) {
      printf("ERRO1\n");
      exit(1);
}

    /*enquanto há problemas a serem lidos*/
    while((check=le_problema(fpIn, &MAT))!=0){

        switch(MAT.var) {
            case 'A' :
                printf("\n\nFunção A(Problema:%d)\n\n",check);
                /*alocar e preencher uma matriz para o mapa, com as suas dimensões lidas*/
                MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.mapa = preenche_matriz(fpIn, MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.celulas = aloca_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
                MAT.celulas = preenche_mat_celulas(MAT.celulas, MAT.linhas, MAT.colunas);
                print_list( explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente));
                free_list( explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente) );
                /*escreve_Ficheiro_Saida(fpOut, &MAT, &RES);*/
                /*libertar a matriz alocada*/
                MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.celulas = liberta_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
                aux=0;
            break;
            case 'B' :
                printf("\n\nFunção B(Problema:%d)\n\n",check);
                /*alocar e preencher uma matriz para o mapa, com as suas dimensões lidas*/
                MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.mapa = preenche_matriz(fpIn, MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.celulas = aloca_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
                MAT.celulas = preenche_mat_celulas(MAT.celulas, MAT.linhas, MAT.colunas);
                print_list(explore(&MAT, MAT.li, MAT.ci, MAT.k, par));
                free_list( explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente));
                MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.celulas = liberta_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
                aux=0;
            break;
            case 'C' :

            break;
            default :
                /* Probelma mal definido*/
                escreve_Ficheiro_Saida(fpOut, &MAT, &RES);
                
        	    
                

        }


    }

    fclose(fpIn);
    fclose(fpOut);
    free(nome_ficheiro_saida);
        return 0;

}
