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
    int **lp;
    int i=0, j=0;
    int x, y;
    int max;

    print_debug("%d\n", 77);

    fpIn = abre_ficheiro( argc, argv[1]);

    nome_ficheiro_saida = Muda_extensao(argv[1], Extensao_fpOut);
    fpOut = fopen(nome_ficheiro_saida, "w");
    if (fpOut ==NULL) {
      print_debug("ERRO1\n");
      exit(1);
}

    /*enquanto há problemas a serem lidos*/
    while((check=le_problema(fpIn, &MAT))!=0){

        /*alocar e preencher uma matriz para o mapa, com as suas dimensões lidas*/              
        MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.mapa = preenche_matriz(fpIn, MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.celulas = aloca_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
        MAT.celulas = preenche_mat_zeros(MAT.celulas, MAT.linhas, MAT.colunas);
        
        if(MAT.var == 'A'){
            print_debug("\n\nFunção A(Problema:%d)\n\n",check);     
            caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente);
        }      
        else{
            if(MAT.var == 'B'){
                print_debug("\n\nFunção B(Problema:%d)\n\n",check); 
                caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, par);
            }
            else{

                if(MAT.var == 'C'){
                    print_debug("\n\nFunção C(Problema:%d)\n\n",check);
                    MAT.li=0;
                    MAT.ci=0;
                    caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente);
                    caminho = muda_partida(&MAT, caminho, CRESCENTE); 
                }
                else
                {
                    if(MAT.var == 'D'){
                        print_debug("\n\nFunção D(Problema:%d)\n\n",check);
                        MAT.li=0;
                        MAT.ci=0;
                        caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, par);
                        caminho = muda_partida(&MAT, caminho, PAR);
                    }
                    else{
                        if(MAT.var == 'E' || MAT.var == 'F'){

                            caminho=NULL;
                            print_debug("\n\nlinhas:%d colunas:%d\n\n", MAT.linhas, MAT.colunas);
                            
                            lp=aloca_matriz(lp, MAT.linhas, MAT.colunas);
                            lp=preenche_mat_zeros(lp, MAT.linhas, MAT.colunas);
                           
                            for(i=0; i<MAT.linhas; i++){
                                for(j=0; j<MAT.colunas; j++){
                                    
                                    if(lp[i][j]==0){
                                        if(MAT.var == 'E') 
                                            preenche_lp(&lp, &MAT, i, j, crescente);
                                        
                                        if(MAT.var == 'F')
                                            preenche_lp(&lp, &MAT, i, j, par);      

                                    }

                                }
                            }
                          
                            print_debug("-----MATRIZ LP-----:\n");
                            for(i=0; i<MAT.linhas; i++){
                                print_debug("\n");

                                for(j=0; j<MAT.colunas; j++)
                                    print_debug("%d  ", lp[i][j]);
                        
                            }

                            x = MAT.linhas;
                            y = MAT.colunas;

                            max=max_matriz(lp, &x, &y);

                            printf("\n\nMÁXIMO DA MATRIZ LP, pos[x][y]: %d %d %d\n\n", max, x, y);


                            caminho = longest_path(&MAT, lp, x, y, max);
                            


                            
                        }
                        else{
                          
                            /* Probelma mal definido*/
                            /* escreve_Ficheiro_Saida(fpOut, &MAT, &RES);*/
                        }
                        
                    }
                }
                
            }     
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
