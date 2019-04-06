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
    FILE *fp1, *fp2;
    int aux=0;
    
    fp1 = abre_ficheiro( argc, argv[1]);
 
    /*enquanto há problemas a serem lidos*/
    while(le_problema(fp, &MAT)!=0){
    
        switch(MAT.var) {
            case 'A' :
                printf("\n\nfunção a\n\n");
                /*alocar e preencher uma matriz para o mapa, com as suas dimensões lidas*/
                MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.mapa = preenche_matriz(fp, MAT.mapa, MAT.linhas, MAT.colunas);
                /*fazer a função a*/
                var_a(&MAT);
                /*libertar a matriz alocada*/
                MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                aux=0;
            break;
            case 'B' :
                printf("\n\nfunção b\n\n");
                /*alocar e preencher uma matriz para o mapa, com as suas dimensões lidas*/
                MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.mapa = preenche_matriz(fp, MAT.mapa, MAT.linhas, MAT.colunas);
                /*fazer a função b*/
                var_b(&MAT);
                MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                aux=0;
            break;
            case 'C' :
                /*fazer função c*/
                printf("\n\nfunção c\n\n");
                /*alocar e preencher uma matriz para o caminho a ser percorrido, com k linhas e 3 colunas*/
                MAT.caminho = aloca_matriz(MAT.caminho, MAT.k, 3);
                MAT.caminho = preenche_matriz(fp, MAT.caminho, MAT.k, 3);
                MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                MAT.mapa = preenche_matriz(fp, MAT.mapa, MAT.linhas, MAT.colunas);
                var_c(&MAT);
                /*libertar as matrizes alocadas*/
                MAT.caminho = liberta_matriz(MAT.caminho, MAT.k, 3);
                MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
                aux=0;

            break;
            default :
                /* O comando da variante é inválido*/
                if(aux==0)
                    printf("\n\nmau comando\n\n");

        	    aux++;
         
        }

    }

    fclose(fp);
        
        return 0;

}
