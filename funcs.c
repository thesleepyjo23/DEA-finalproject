#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcs.h"
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
        fprintf(stderr, "Modo de utilização: ./<nomedoexecutavel> <nomedoficheiro.puz0>\n");
        exit(1);
    }

    fpIn = fopen ( argv, "r" );
    if ( fpIn == NULL ) {
        fprintf ( stderr, "Erro ao abrir o ficheiro .puz0 '%s'\n", argv);
        exit (1);
    }


    /*verifica se o nome do ficheiro a ser aberto acaba em .puz0*/
    x=strlen(argv);

    if( (argv[x-5]!='.') || (argv[x-4]!='p') || (argv[x-3]!='u') || (argv[x-2]!='z') || (argv[x-1]!='0') ){

        fprintf(stderr, "Modo de utilização: ./<nomedoexecutavel> <nomedoficheiro.puz0>\n");
        exit (2);
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


/*função que verifica se as posições indicadas estão fora do mapa*/
int fora_do_mapa(int l, int c, int linhas, int colunas){

    /*se forem menores que 0 ou maiores (ou iguais, em c começamos em 0) que a dimensão da matriz estão claramente fora do mapa*/
    if( (l<0) || (l>=linhas) || (c<0) || (c>=colunas) )
        return 1;

    else
        return 0;

}


 int le_problema(FILE *fpIn, Matriz *M){

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

    /*APAGAR*/
    printf("\n\n%d %d %c %d %d %d", linhas, colunas, var, li, ci, k );

    /*celula inicial está fora do mapa*/
    if( (var=='A'||var=='B') && fora_do_mapa(li,ci,linhas,colunas)==1)
        return -1;

    /*o caminho quando é relevante tem menos de 1 passo*/
    if( (var=='A'||var=='B'||var=='C'||var=='D') && k<1 )
        return -1;


    return 1;
 }


/*função que aloca memória para uma matriz de dimensão "linhas" x "colunas"*/
 int **aloca_matriz(int **matriz, int linhas, int colunas){

    int i;

    matriz = (int **) malloc( linhas*sizeof(int*) );

    for(i=0; i<linhas; i++)
        matriz[i]= (int*) malloc( colunas*sizeof(int));


    return matriz;
 }

/*função que preenche a matriz tendo em conta o que é lido no ficheiro*/
int **preenche_matriz(FILE *fpIn, int **matriz, int linhas, int colunas){

    int i, j;

    for(i=0; i<linhas; i++){

        for(j=0; j<colunas; j++){

            fscanf(fpIn, "%d", &matriz[i][j]);

        }
    }
/*APAGAR*/
    for(i=0; i<linhas; i++){
      printf("\n");
        for(j=0; j<colunas; j++){

            printf("%d ", matriz[i][j]);

        }

    }
  printf("\n");

    return matriz;

}


/*função que liberta a memória alocada anteriormente da matriz*/
 int **liberta_matriz (int **matriz, int linhas, int colunas){

    int i;

    for(i=0; i<linhas; i++)
        free(matriz[i]);

    free(matriz);

    return matriz;

}


int **preenche_mat_celulas(int **matriz, int linhas, int colunas){

    int i, j;

    for (i=0; i<linhas; i++){

        for(j=0; j<colunas; j++){
            matriz[i][j]=0;
        }
    }

    return matriz;
}

void escreve_Ficheiro_Saida(FILE *fp, Matriz *M, Resultado *R){

    int aux=0;

    if (M->var == 'C') {
    aux=1;
    }

    /*escreve ficheiro nas condiçoes de A ou B*/
    if((M->var == 'A'|| M->var == 'B') && aux==0){

        if(R->resultado != -1){

        fprintf(fp, "%d %d %c %d %d %d %d %d\n\n",M->linhas, M->colunas, M->var, M->li, M->ci, M->k, R->resultado, R->valor );

        }
        else
        {
        fprintf(fp, "%d %d %c %d %d %d %d\n\n",M->linhas, M->colunas, M->var, M->li, M->ci, M->k, R->resultado);

        }

    }
    /*escreve ficheiro nas condiçoes de C
    Var C não passa nos testes, a rever*/
    if (M->var == 'C' && aux==1) {
        if(R->resultadoC!=4){

            fprintf(fp, "%d %d %c %d %d %d %d\n\n",M->linhas, M->colunas, M->var, M->li, M->ci, M->k, R->resultadoC);
        }
    }

    /*escreve ficheiro caso o problema esteja mal definido*/
    /*Caso || (fora_do_mapa(M->li, M->ci, M->linhas,  M->colunas)==1)||(M->k<1) a ter em conta*/
    if ((M->var != 'A' && M->var != 'B' && M->var != 'C'))
    {
        R->resultado=-1;
        fprintf(fp, "%d %d %c %d %d %d %d\n\n",M->linhas, M->colunas, M->var, M->li, M->ci, M->k, R->resultado);
    }

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

void print_list(node * list){

    node * aux = list;

    if(list==NULL){
        printf("\n\n-1\n\n");
        return;
    }
    else
        aux=aux->next;
    
    while (aux != NULL){
        printf("\n%d,%d: %d\n", aux->x, aux->y, aux->val);
        aux=aux->next;
    }
    return;
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

/*Função Explore:
    Insere no fim da lista um nó que satisfaz as condições da variante em causa.

    Recebe como parâmetros a estrutura que define o problema - M, a posição do elemento a inserir

*/
node *explore(Matriz * M, int x, int y, int k, int (*valido)(Matriz*,int,int,int,int)){

    int nx, ny, l;
    int val = M->mapa[x][y];

    node *current_node = create_node(x,y,val);
    node *result;

    /*O comprimento do caminho foi satisfeito*/
    if (k == 0)
        return current_node;
 
    for (l=0; l<8; l++) {
        /*movimento para uma célula adjacente de posição (nx, ny) */
        nx = x + movimentos[l][0];
        ny = y + movimentos[l][1];

        /*a célula resultante do movimento anterior está fora do mapa, repete-se o ciclo*/
        if (fora_do_mapa(nx, ny, M->linhas, M->colunas)==1)
            continue;

        /*a célula resultante não satisfaz o critério ou já foi percorrida, repete-se o ciclo*/
        if (valido(M,x,y,nx,ny)==0 || M->celulas[nx][ny]==1)
            continue; 

        /*a nova célula satisfaz os critérios anteriores e então a função é chamada
        recursivamente com a sua nova posição, e a sua posição é dada como percorrida*/
        M->celulas[nx][ny]=1;    
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
    return NULL;
        
}

node *percorre_mapa (Matriz *M, node *caminho, int criterio){

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
        printf("\n%d %d", M->li, M->ci);

        M->celulas = preenche_mat_celulas(M->celulas, M->linhas, M->colunas);
        
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

    return;
}
