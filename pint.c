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
    node *caminho;

    fpIn = abre_ficheiro( argc, argv[1]);

    nome_ficheiro_saida = Muda_extensao(argv[1], Extensao_fpOut);
    fpOut = fopen(nome_ficheiro_saida, "w");
    if (fpOut ==NULL) {
      printf("ERRO1\n");
      exit(1);
}

    /*enquanto há problemas a serem lidos*/
    while((check=le_problema(fpIn, &MAT))!=0){

        /*alocar e preencher uma matriz para o mapa, com as suas dimensões lidas*/              
        MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.mapa = preenche_matriz(fpIn, MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.celulas = aloca_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
        MAT.celulas = preenche_mat_celulas(MAT.celulas, MAT.linhas, MAT.colunas);
        
        if(MAT.var == 'A'){
            printf("\n\nFunção A(Problema:%d)\n\n",check);     
            caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente);
        }      

        if(MAT.var == 'B'){
            printf("\n\nFunção B(Problema:%d)\n\n",check); 
            caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, par);
        }     
                

        if(MAT.var == 'C'){
            printf("\n\nFunção C(Problema:%d)\n\n",check);
            MAT.li=0;
            MAT.ci=0;
            caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente);
            caminho = percorre_mapa(&MAT, caminho, CRESCENTE); 
        }
        if(MAT.var == 'D'){
            printf("\n\nFunção D(Problema:%d)\n\n",check);
            MAT.li=0;
            MAT.ci=0;
            caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, par);
            caminho = percorre_mapa(&MAT, caminho, PAR);
        }
        else{
            /* Probelma mal definido*/
            escreve_Ficheiro_Saida(fpOut, &MAT, &RES);
        }                   
                
        print_list(caminho);
        free_list(caminho);
        /*escreve_Ficheiro_Saida(fpOut, &MAT, &RES);*/
        /*libertar a matriz alocada*/
        MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.celulas = liberta_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
        aux=0;                
    }
       
    fclose(fpIn);
    fclose(fpOut);
    free(nome_ficheiro_saida);
    return 0;
}
