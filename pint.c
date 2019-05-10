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

    fpIn = abre_ficheiro( argc, argv[1]);

    nome_ficheiro_saida = Muda_extensao(argv[1], Extensao_fpOut);
    fpOut = fopen(nome_ficheiro_saida, "w");
    if (fpOut ==NULL) {
      printf("ERRO1\n");
      exit(1);
}

    /*enquanto há problemas a serem lidos*/
    while(le_problema(fpIn, &MAT)!=0){

        switch(MAT.var) {
            case 'A' :
                printf("\n\nfunção a\n\n");
                /*alocar e preencher uma matriz para o mapa, com as suas dimensões lidas*/
                MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.mapa = preenche_matriz(fpIn, MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.celulas = aloca_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
                MAT.celulas = preenche_mat_celulas(MAT.celulas, MAT.linhas, MAT.colunas);
                MAT.caminho = aloca_matriz(MAT.caminho, MAT.k, 3);

                /*fazer a função a*/
                /*var_a(&MAT,&RES);*/
                print_list( explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente) );
                free_list( explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente) );
                escreve_Ficheiro_Saida(fpOut, &MAT, &RES);
                /*libertar a matriz alocada*/
                MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.celulas = liberta_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
                MAT.caminho = liberta_matriz(MAT.caminho, MAT.k, 3);
                aux=0;
            break;
            case 'B' :
                printf("\n\nfunção b\n\n");
                /*alocar e preencher uma matriz para o mapa, com as suas dimensões lidas*/
                MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.mapa = preenche_matriz(fpIn, MAT.mapa, MAT.linhas, MAT.colunas);
                /*fazer a função b*/
                /*var_b(&MAT,&RES);*/
                print_list(explore(&MAT, MAT.li, MAT.ci, MAT.k, par));
                free_list( explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente) );
                escreve_Ficheiro_Saida(fpOut, &MAT, &RES);
                MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                aux=0;
            break;
            case 'C' :
                /*fazer função c*/
                printf("\n\nfunção c\n\n");
                /*alocar e preencher uma matriz para o caminho a ser percorrido, com k linhas e 3 colunas*/
                MAT.caminho = aloca_matriz(MAT.caminho, MAT.k, 3);
                MAT.caminho = preenche_matriz(fpIn, MAT.caminho, MAT.k, 3);
                MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.mapa = preenche_matriz(fpIn, MAT.mapa, MAT.linhas, MAT.colunas);
                var_c(&MAT,&RES);
                escreve_Ficheiro_Saida(fpOut, &MAT, &RES);
                /*libertar as matrizes alocadas*/
                MAT.caminho = liberta_matriz(MAT.caminho, MAT.k, 3);
                MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                aux=0;

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
