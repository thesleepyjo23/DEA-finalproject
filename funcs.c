#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "funcs.h"
#include "matriz.h"
#define MAX 2147483647






/*variável global que contém os movimentos possíveis a serem feitos
{-1,0}-N
{-1, -1}-NO
{0, -1}-O
{1, -1}-SO
{1, 0}-S
{1, 1}-SE
{0, 1}-E
{-1, 1}-NE
*/
int movimentos[8][2] = {{-1,0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};

/*função que abre os ficheiros*/
 FILE* abre_ficheiro(int argc, char *argv){

    FILE *fpIn;
    int x=0;


    /*verifica se o utilizador está a executar o programa com 2 inputs*/
    if (argc != 2) {
        exit(0);
    }

    fpIn = fopen ( argv, "r" );
    if ( fpIn == NULL ) {
        exit (0);
    }


    /*verifica se o nome do ficheiro a ser aberto acaba em .puz0*/
    x=strlen(argv);

    if( (argv[x-4]!='.') || (argv[x-3]!='p') || (argv[x-2]!='u') || (argv[x-1]!='z') ){
        exit (0);
    }

    return fpIn;

 }
/*Muda extensao do ficheiro de saída mantendo o nome do ficheiro de entrada
nova extensao definida no funcs.h
Usei calloc pq tava a dar erro no valgrind por alocar com malloc sem inicializar a 0.*/
 char *Muda_extensao(const char *nome_ficheiro,const char *nova_extensao) {

 	size_t tamanho_nome_ficheiro=0;
  char *novo_nome_ficheiro = NULL;
  char *extensao = NULL;

 	extensao = strrchr(nome_ficheiro, '.');

 	if(extensao == NULL) {
      return NULL;
  }

 	tamanho_nome_ficheiro = strlen(nome_ficheiro) - strlen(extensao);

 	novo_nome_ficheiro = calloc(tamanho_nome_ficheiro+strlen(nova_extensao) + 1, sizeof(char));
  if (novo_nome_ficheiro==NULL) {
    exit(0);
  }
  strncpy(novo_nome_ficheiro, nome_ficheiro, tamanho_nome_ficheiro);
  strcat(novo_nome_ficheiro, nova_extensao);


 	return novo_nome_ficheiro;
 }

 void Ficheiro_Saida(FILE *fpO, Matriz *M, node * list, int k_real)

 {
   int check=0;

   node * aux = list;


   if( (M->var=='A'||M->var=='B') && fora_do_mapa(M->li,M->ci,M->linhas,M->colunas) == 1)
   {
     fprintf(fpO, "%d %d %c %d %d %d -1\n",M->linhas, M->colunas, M->var, M->li, M->ci, M->k);
     return;
   }

   /*o caminho quando é relevante tem menos de 1 passo*/
   if( (M->var!='A' && M->var!='B' && M->var!='C' && M->var!='D' && M->var!='E' && M->var!='F') || M->k<1)
   {

     fprintf(fpO, "%d %d %c %d %d %d -1\n\n",M->linhas, M->colunas, M->var, M->li, M->ci, M->k);
     return;
   }

   if((M->var == 'A'|| M->var == 'B'||M->var=='C'||M->var=='D'))

       {
           /*print_list(list, fpO, R);*/
           if (list == NULL) {
             fprintf(fpO, "%d %d %c %d %d %d -1\n",M->linhas, M->colunas, M->var, M->li, M->ci, M->k);
             fprintf(fpO, "\n");
             check =-1;
            }

           else
           {
               aux=aux->next;
               check = 1;

             }

           if (check==1) {
                 fprintf(fpO, "%d %d %c %d %d %d %d\n",M->linhas, M->colunas, M->var, M->li, M->ci, M->k, M->k);
                 while (aux != NULL){
                     fprintf(fpO,"%d %d %d\n", aux->x, aux->y, aux->val);
                     fflush(fpO);
                     aux=aux->next;

                   }
                   fprintf(fpO, "\n");
               }

       }

    if (M->var=='E'||M->var=='F') {
        /*print_list(list, fpO, R);*/
        if (list == NULL) {
          fprintf(fpO, "%d %d %c %d %d %d -1\n",M->linhas, M->colunas, M->var, M->li, M->ci, M->k);
          fprintf(fpO, "\n");
          check =-1;
         }

          else
            {
                if (aux->next==NULL) {
                  fprintf(fpO, "%d %d %c %d %d %d -1\n",M->linhas, M->colunas, M->var, M->li, M->ci, M->k);
                }
                else
                {

                  fprintf(fpO, "%d %d %c %d %d %d %d\n",M->linhas, M->colunas, M->var, aux->x,aux->y, M->k, k_real-1);
                    aux=aux->next;
                    check = 1;
                }

            }

          if (check==1) {
                while (aux != NULL){
                    fprintf(fpO,"%d %d %d\n", aux->x, aux->y, aux->val);
                    fflush(fpO);
                    aux=aux->next;

                  }
                  fprintf(fpO, "\n");
              }

    }

       return;
 }


/*função que verifica se as posições indicadas estão fora do mapa*/
int fora_do_mapa(int l, int c, int linhas, int colunas){

    /*se forem menores que 0 ou maiores (ou iguais, em c começamos em 0) que a dimensão da matriz estão claramente fora do mapa*/
    if( (l<0) || (l>=linhas) || (c<0) || (c>=colunas) )
        return 1;

    else
        return 0;

}


 int le_problema(FILE *fpIn, Matriz *M, Resultado *R){

    int colunas;
    int linhas;
    int li, ci;
    int k;
    int check;
    char var;


    /*leitura dos 6 parametros que definem o problema*/
    check = fscanf(fpIn, "%d %d %c %d %d %d", &linhas, &colunas, &var, &li, &ci, &k);

    /*se o fscanf não ler os 6 parametros que definem o problema devolve 0 (maneira de ver se o ficheiro chega ao fim)*/
    if(check!=6){

        return 0;
    }


    /*atribui cada um dos parametros ao seu devido lugar na estrutura*/
    M->colunas=colunas;
    M->linhas=linhas;
    M->var=var;
    M->li=li;
    M->ci=ci;
    M->k=k;


    return 1;
 }

/*Função create_node:

    Recebe a posição no mapa do nó a ser creado assim como o seu valor.
    Retorna o nó criado.
*/
node * create_node(int x, int y, int val){
    node *no;

    /*alocação da memória do nó a ser criado*/
    no =(node*) malloc(sizeof(node));

    /*erro na alocação de memória*/
    if(no==NULL)
        exit(0);

    /*é fornecida ao nó a sua posição e o seu valor*/
    no->x = x;
    no->y = y;
    no->val = val;

    no->next=NULL;

    return no;
}

/*Função par:

    Recebe a estrutura que contêm os dados do problema bem como o mapa,
as posições da célula actual (irrelevantes para esta função) e a da próxima à qual nos vamos movimentar.
    Retorna 1 caso a próxima célula for par, 0 caso contrário (seja ímpar).

*/
int par(Matriz * M, int x, int y, int nx, int ny){
    /*current position (x,y) is irrelevant*/
    if(M->mapa[nx][ny]%2==0)
        return 1;

    else
        return 0;
}

int Atual_par(Matriz * M, int x, int y, int nx, int ny){
    /*current position (x,y) is irrelevant*/
    if((M->mapa[x][y]%2==0) && (M->mapa[nx][ny]%2==0))
        return 1;

    else
        return 0;
}



/*Função crescente:

    Recebe a estrutura que contêm os dados do problema bem como o mapa,
as posições da célula actual e a da próxima à qual nos vamos movimentar.
    Retorna 1 caso a próxima célula maior que a actual, 0 caso contrário (seja menor).

*/
int crescente(Matriz * M, int x, int y, int nx, int ny){
    return (M->mapa[x][y] < M->mapa[nx][ny]);
}

int decrescente(Matriz * M, int x, int y, int nx, int ny){
    return (M->mapa[x][y] > M->mapa[nx][ny]);
}

void preenche_lp(int ***lp, Matriz * M, int x, int y, int (*valido)(Matriz*,int,int,int,int)){

    int nx, ny, l;
    int max_length = 1;



    M->celulas[x][y]=1;

    for (l=0; l<8; l++) {
        /*movimento para uma célula adjacente de posição (nx, ny) */
        nx = x + movimentos[l][0];
        ny = y + movimentos[l][1];

        /*a célula resultante do movimento anterior está fora do mapa, repete-se o ciclo*/
        if (fora_do_mapa(nx, ny, M->linhas, M->colunas) == 1 || valido(M,x,y,nx,ny)==0 || M->celulas[nx][ny]==1)
            continue;



        if ((*lp)[nx][ny] == 0)
            preenche_lp(lp, M, nx, ny, valido);

        if (max_length < (*lp)[nx][ny] + 1)
            max_length = (*lp)[nx][ny] + 1;


    }

    /*não encontra nenhuma célula adjacente que satisfaz os requisitos da variante*/
    M->celulas[x][y]=0;

    (*lp)[x][y] = max_length;

    return;
}


/*Função Explore:
    Insere no fim da lista um nó que satisfaz as condições da variante em causa.

    Recebe como parâmetros a estrutura que define o problema - M, a posição do elemento a inserir

*/
node *explore(Matriz * M, int x, int y, int k, int (*valido)(Matriz*,int,int,int,int)){

    int nx, ny, l;
    int val = M->mapa[x][y];

    node *current_node = create_node(x,y,val);
    node *result;

      M->celulas[x][y]=1;

    /*O comprimento do caminho foi satisfeito*/
    if (k == 0)
        return current_node;

    for (l=0; l<8; l++) {
        /*movimento para uma célula adjacente de posição (nx, ny) */
        nx = x + movimentos[l][0];
        ny = y + movimentos[l][1];

        /*a célula resultante do movimento anterior está fora do mapa, repete-se o ciclo*/
        if (fora_do_mapa(nx, ny, M->linhas, M->colunas) == 1 || valido(M,x,y,nx,ny)==0 || M->celulas[nx][ny]==1)
            continue;

        /*a nova célula satisfaz os critérios anteriores e então a função é chamada
        recursivamente com a sua nova posição, e a sua posição é dada como percorrida*/

        result = explore(M,nx,ny,k-1, valido);

        /*insere-se o nó no final da lista se este não for NULL,
        ou seja, se a célula é valida para ser adicionada ao caminho */
        if (result == NULL)
            continue;

        else{
            current_node->next=result;
            return current_node;
        }
    }
    /*não encontra nenhuma célula adjacente que satisfaz os requisitos da variante*/
    M->celulas[x][y]=0;
    free(current_node);
    return NULL;

}

node *longest_path(Matriz * M, int **lp, int x, int y, int prev_max){

    int l=0, i=0, j=0, nx=0, ny=0;
    int max=0;
    int val=M->mapa[x][y];
    node *current_node = create_node(x, y, val);
    node *next_node;

    M->celulas[x][y]=1;

    if(lp[x][y]==1)
        return current_node;

    for(l=0; l<8; l++){

        i = x + movimentos[l][0];
        j = y + movimentos[l][1];

        if ( fora_do_mapa(i, j, M->linhas, M->colunas)==1 || M->celulas[i][j]==1 || lp[i][j]>=prev_max)
            continue;

        if (lp[i][j]>max){
            max=lp[i][j];
            nx=i;
            ny=j;

        }
    }


    next_node = longest_path(M, lp, nx, ny, max);

    current_node->next=next_node;
    return current_node;

}



node *muda_partida (Matriz *M, node *caminho, int criterio){

    while(caminho==NULL){

        if(M->ci < M->colunas-1){
            M->ci++;
        }
        else{
            if(M->li < M->linhas-1)
                M->li++;
            else
                break;
            M->ci=0;
        }

        M->celulas = preenche_mat_zeros(M->celulas, M->linhas, M->colunas);

        if(criterio==CRESCENTE)
            caminho=explore(M, M->li, M->ci, M->k, crescente);

        if(criterio==PAR)
            caminho=explore(M, M->li, M->ci, M->k, par);

    }
    return caminho;

}

void free_list(node *no){

    node *aux;

    while (no != NULL){

        aux=no;
        no=no->next;
        free(aux);
    }

    no=NULL;
    free(no);

    return;
}
