#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcs.h"
#include "matriz.h"

 /*
 *  Function:
 *    main()
 *
 */

int main(int argc, char *argv[]) {

    Matriz MAT;
    Resultado RES;
    FILE *fpIn, *fpOut;
    char *nome_ficheiro_saida = NULL;
    int check=0;
    node *caminho = NULL;
    int **lp = NULL;
    int i=0, j=0;
    int x=0, y=0;
    int max=0;
    int aux1=0, aux2=0;



    fpIn = abre_ficheiro( argc, argv[1]);

    nome_ficheiro_saida = Muda_extensao(argv[1], Extensao_fpOut);
    fpOut = fopen(nome_ficheiro_saida, "w");
    if (fpOut ==NULL) {
      exit(0);
}

    /*enquanto há problemas a serem lidos*/
    while((check=le_problema(fpIn, &MAT,&RES))!=0){
        caminho = NULL;
        /*alocar e preencher uma matriz para o mapa, com as suas dimensões lidas*/
        MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.mapa = preenche_matriz(fpIn, MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.celulas = aloca_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
        MAT.celulas = preenche_mat_zeros(MAT.celulas, MAT.linhas, MAT.colunas);

        if(MAT.var == 'A'){

            caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente);
        }
        else{
            if(MAT.var == 'B'){

                caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, par);
            }
            else{

                if(MAT.var == 'C'){

                    aux1=MAT.li;
                    aux2=MAT.ci;
                    MAT.li=0;
                    MAT.ci=0;
                    caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente);
                    caminho = muda_partida(&MAT, caminho, CRESCENTE);
                    if ((MAT.k<1)|| (caminho==NULL)){
                      MAT.li=aux1;
                      MAT.ci=aux2;
                    }

                }
                else
                {
                    if(MAT.var == 'D'){

                        aux1=MAT.li;
                        aux2=MAT.ci;
                        MAT.li=0;
                        MAT.ci=0;
                        caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, par);
                        caminho = muda_partida(&MAT, caminho, PAR);
                        if ((MAT.k<1)|| (caminho==NULL)) {
                          MAT.li=aux1;
                          MAT.ci=aux2;
                        }
                    }
                    else{
                        if(MAT.var == 'E' || MAT.var == 'F'){

                            lp=aloca_matriz(lp, MAT.linhas, MAT.colunas);
                            lp=preenche_mat_zeros(lp, MAT.linhas, MAT.colunas);

                           

                            for(i=0; i<MAT.linhas; i++){
                                for(j=0; j<MAT.colunas; j++){
                                    
                                    /*MAT.celulas = preenche_mat_zeros(MAT.celulas, MAT.linhas, MAT.colunas);
*/
                                    if(lp[i][j]==0){
                                        if(MAT.var == 'E')
                                            preenche_lp(&lp, &MAT, i, j, crescente);

                                        if(MAT.var == 'F')
                                            preenche_lp(&lp, &MAT, i, j, Atual_par);

                                    }

                                    

                                }
                            }
                            printf("\n");
                            for(i=0; i<MAT.linhas; i++){
                              printf("\n");
                                for(j=0; j<MAT.colunas; j++){

                                    printf("%d ", lp[i][j]);
                                    fflush(stdout);
                                }
                            }



                            x = MAT.linhas;
                            y = MAT.colunas;

                            max=max_matriz(lp, &x, &y);

                            if(MAT.var == 'E')
                                caminho = longest_path(&MAT, lp, x, y, max, crescente);

                            if(MAT.var == 'F')
                                caminho = longest_path(&MAT, lp, x, y, max, Atual_par);

                            

                            lp=liberta_matriz(lp, MAT.linhas, MAT.colunas);


                        }

                    }
                }

            }
        }


        Ficheiro_Saida(fpOut,&MAT, caminho, max);



        /*print_list(caminho);*/
        free_list(caminho);
        /*libertar a matriz alocada*/
        MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.celulas = liberta_matriz(MAT.celulas, MAT.linhas, MAT.colunas);

    }

    fclose(fpIn);
    fclose(fpOut);
    free(nome_ficheiro_saida);
    return 0;
}
