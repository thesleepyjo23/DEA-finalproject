#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcs.h"
#include "matriz.h"

 /*Função main:
    Recebe os parâmetros:
    - argc - número de argumentos na invocação do programa;
    - argv - tabela de strings que contém os argumentos da invocação do programa.

    Retorna 0 se o programa é bem sucedido.

 */

int main(int argc, char *argv[]) {

    Matriz MAT; /*variável que vai conter os dados do problema 
    assim como as matrizes de representação do mapa*/
    Resultado RES;
    FILE *fpIn, *fpOut; /*ponteiros dos ficheiros de leitura (fpIn) e de escrita (fpOut) */
    char *nome_ficheiro_saida = NULL;  /*string que vai conter o nome do ficheiro de saída*/
    int check=0; /*variável que verifica o número de parâmetros retornados pela função fscanf
    na leitura do ficheiro*/
    node *caminho = NULL; /*lista que vai conter o caminho a ser impresso no ficheiro de saída*/
    int **lp = NULL; /*tabela que vai guardar o maior caminho possível a ser feito a partir
    de cada posição do mapa*/
    int i=0, j=0;  /*variáveis de contagem*/
    int x=0, y=0;  /*posição do valor máximo da matriz lp*/
    int max=0;  /*valor máximo da matriz lp*/
    int aux1=0, aux2=0;  /*variáveis que vão guardar o valor da posição da célula inicial lida do problema*/



    fpIn = abre_ficheiro( argc, argv[1]);

    nome_ficheiro_saida = Muda_extensao(argv[1], Extensao_fpOut);
    fpOut = fopen(nome_ficheiro_saida, "w");

    /*verificação se o ficheiro é bem aberto*/
    if (fpOut ==NULL) {
      exit(0);
    }

    /*enquanto há problemas a serem lidos*/
    while((check=le_problema(fpIn, &MAT,&RES))!=0){

        /*é necessário inicializar o caminho novamente a NULL para cada iteração do ciclo*/
        caminho = NULL;

        /*alocar e preencher as matrizes para representar o mapa
        tendo em conta as suas dimensões*/
        MAT.mapa = aloca_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.mapa = preenche_matriz(fpIn, MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.celulas = aloca_matriz(MAT.celulas, MAT.linhas, MAT.colunas);
        MAT.celulas = preenche_mat_zeros(MAT.celulas, MAT.linhas, MAT.colunas);

        /*Variante A*/
        if(MAT.var == 'A'){

            caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente);
        }
        else{
            /*Variante B*/
            if(MAT.var == 'B'){

                caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, par);
            }
            else{

                /*Variante C*/
                if(MAT.var == 'C'){

                    aux1=MAT.li;
                    aux2=MAT.ci;
                    
                    MAT.li=0;
                    MAT.ci=0;
                    caminho = explore(&MAT, MAT.li, MAT.ci, MAT.k, crescente);
                    caminho = muda_partida(&MAT, caminho, CRESCENTE);
                    
                    /*caso o problema esteja definifo com um k inválido
                    ou não se consegue encontrar um caminho, a posição inicial
                    a ser escrita não deve ser alterada */
                    if ((MAT.k<1)|| (caminho==NULL)){
                      MAT.li=aux1;
                      MAT.ci=aux2;
                    }

                }
                else
                {
                    /*Variante D, em tudo semelhante à C excepto a condição de caminhos pares*/
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
                        /*Variantes E e F*/
                        if(MAT.var == 'E' || MAT.var == 'F'){

                            /*alocar e preencher a matriz lp com zeros*/
                            lp=aloca_matriz(lp, MAT.linhas, MAT.colunas);
                            lp=preenche_mat_zeros(lp, MAT.linhas, MAT.colunas);

                            /*ciclo para percorrer todas as posições da matriz lp*/
                            for(i=0; i<MAT.linhas; i++){
                                for(j=0; j<MAT.colunas; j++){

                                    /*apenas faz sentido preencher a matriz se o valor 
                                    estiver por preencher, ou seja, igual a 0, e naturalmente
                                    esta é preenchida consoante o critério de 
                                    estritamente crescente ou par*/
                                    if(lp[i][j]==0){
                                        if(MAT.var == 'E')
                                            preenche_lp(&lp, &MAT, i, j, crescente);

                                        if(MAT.var == 'F')
                                            preenche_lp(&lp, &MAT, i, j, par);

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

                            /*é de notar que as variáveis x e y são alteradas por referência*/
                            max=max_matriz(lp, &x, &y);

                            /*o maior caminho é realizado consoante o critério*/
                            if(MAT.var == 'E')
                                caminho = longest_path(&MAT, lp, x, y, max, crescente);

                            if(MAT.var == 'F')
                                caminho = longest_path(&MAT, lp, x, y, max, par);

                            
                            /*libertação da memória alocada para a matriz lp*/
                            lp=liberta_matriz(lp, MAT.linhas, MAT.colunas);


                        }

                    }
                }

            }
        }


        Ficheiro_Saida(fpOut,&MAT, caminho, max);

        /*print_list(caminho);*/
        free_list(caminho);
        /*libertar as matrizes alocadas para o mapa*/
        MAT.mapa = liberta_matriz(MAT.mapa, MAT.linhas, MAT.colunas);
        MAT.celulas = liberta_matriz(MAT.celulas, MAT.linhas, MAT.colunas);

    }

    /*fecho dos ficheiros, e libertação de memória do nome do ficheiro de sáida*/
    fclose(fpIn);
    fclose(fpOut);
    free(nome_ficheiro_saida);
    return 0;
}
