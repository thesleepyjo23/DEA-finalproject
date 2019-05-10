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

/*função que verifica se as posições indicadas estão fora do mapa*/
int fora_do_mapa(int l, int c, int linhas, int colunas){

    /*se forem menores que 0 ou maiores (ou iguais, em c começamos em 0) que a dimensão da matriz estão claramente fora do mapa*/
    if( (l<0) || (l>=linhas) || (c<0) || (c>=colunas) )
        return 1;

    else
        return 0;

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

    if(list==NULL)
        return;

    else
        aux=aux->next;
    
    while (aux != NULL){
        printf("\n%d,%d - %d\n", aux->x, aux->y, aux->val);
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

node *explore(Matriz * M, int x, int y, int k, int (*valido)(Matriz*,int,int,int,int)){

    int nx, ny, l;
    int val = M->mapa[x][y];

    node *current_node = create_node(x,y,val);
    node *result;

    /*o comprimento do caminho foi satisfeito*/
    if (k == 0)
        return current_node;
 
    for (l=0; l<8; l++) {
        /*movimento para uma célula adjacente de posição (nx, ny) */
        nx = x + movimentos[l][0];
        ny = y + movimentos[l][1];


        if (fora_do_mapa(nx, ny, M->linhas, M->colunas)==1)
            continue;

        /*se a célula resultante do movimento anterior está fora do mapa, não satisfaz o critério ou já foi usada repete-se o ciclo*/
        if (valido(M,x,y,nx,ny)==0 || M->celulas[nx][ny]==1)
            continue; 


        M->celulas[nx][ny]=1;
        /*a nova célula satisfaz os critérios anteriores e então a função é chamada recursivamente com a sua nova posição*/
        result = explore(M,nx,ny,k-1, valido);
        
        if (result == NULL)
            continue;
        
        else{
            current_node->next=result;
            return current_node;
        }
    }
    return NULL;
        
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

/*função que realiza a variante A*/
void var_a(Matriz *M, Resultado *R){

    int l;
    int i, j;
    int max;  /*variável que vai conter o valor máximo*/
    int check=0; /*variável que vai contar quantas células adjacentes possuem um valor maior que a célula inicial do problema*/
    int cursor=0;
    int buffer_cursor=0;
    int buffer_x, buffer_y;
    int buffer_max;
    int x, y;
    int k;

    /*casos fora do mapa*/
    if( fora_do_mapa(M->li, M->ci, M->linhas, M->colunas)==1  ){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        R->resultado=-1;
        return;
    }

    for(i=0; i<M->linhas; i++){
        for(j=0; j<M->colunas; j++)
            M->celulas[i][j]=0;
    }

    /*o número máximo inicial é o da célula indicada pelo problema*/
    max=M->mapa[M->li][M->ci];
    x=M->li;
    y=M->ci; 
    k=M->k;


    /*ciclo que vai percorrer as posições adjacentes e usar o valor das válidas*/
    while(cursor < k){
        buffer_cursor=cursor;
        for (l=0; l<8; l++) {
            /*são somados aos índices os movimentos possíveis a seres feitos*/
            i = x + movimentos[l][0];
            j = y + movimentos[l][1];
            /*posições não válidas, ou seja, fora do mapa*/
            if (fora_do_mapa(i, j, M->linhas, M->colunas)==1) {
                R->resultado=-1;
                continue;
            }   
            
            /*se o número da célula actual for maior e esta ainda não tiver sido usada no caminho*/
            if ( (M->mapa[i][j]>max) && (M->celulas[i][j]!=1)){
                buffer_max=max;
                max=M->mapa[i][j];
                M->celulas[i][j]=1;
                M->caminho[cursor][0]=i;
                M->caminho[cursor][1]=j;
                M->caminho[cursor][2]=max;
                buffer_x=x;
                buffer_y=y;
                x=i;
                y=j;
                cursor++;
                break;
            }
        }
        /*não encontrou célula adjacente maior*/
        if(buffer_cursor==cursor){
            cursor--;
            x=buffer_x;
            y=buffer_y;
            max=buffer_max;
        }
        /*não encontrou caminho de dimensão possível*/
        if(cursor<0){
            printf("\n\nvariante A não satisfeita\n\n");
            break;
        }

    }

    for(i=0; i<k; i++){
      printf("\n");
        for(j=0; j<3; j++){

            printf("%d ", M->caminho[i][j]);

        }

    }
    /*caso em que não é encontrada nenhuma célula com valor maior*/
    if (check==0){

        /*escrever -1*/
        printf("\n\n-1\n\n");
          R->resultado=-1;
        return;
    }

    /*é escrito 1 e o valor máximo das células adjacentes*/
    printf("\n\nvalor maximo:%d\n\n", max);
      R->resultado=1;
        R->valor=max;

}


/*função que realiza a variante B*/
void var_b(Matriz *M, Resultado *R){


    int l;
    int i, j;
    int min=MAX; /*número que vai conter o valor mínimo par, é inicializado com o maior inteiro possível em C*/
    int num_pares=0;  /*variável que vai contar a quantidade de números pares adjacentes à célula inicial*/

    /*casos fora do mapa*/
    if( fora_do_mapa(M->li, M->ci, M->linhas, M->colunas)==1 ){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        R->resultado=-1;
        return;
    }

    /*ciclo que vai percorrer as posições adjacentes e usar o valor das válidas*/
    for (l=0; l<8; l++) {
        i = M->li + movimentos[l][0];
        j = M->ci + movimentos[l][1];
        if (fora_do_mapa(i, j, M->linhas, M->colunas)==1) {
          R->resultado=-1;
          continue;
        }

        /*o número contido na célula adjacente é par*/
        if ( (M->mapa[i][j]%2==0) )
            num_pares++;

        /*se o número for menor e par, este passa a ser o mínimo*/
        if( (M->mapa[i][j]%2==0) && (M->mapa[i][j]<min) ){
            min=M->mapa[i][j];
        }

    }

    /*nenhuma célula adjacente é par*/
    if(num_pares==0){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        R->resultado=-1;
        return;
    }

    /*escrever 1 e o mínimo*/
    printf("\n\nnumeros pares:%d  valor minimo:%d\n\n", num_pares, min);
    R->resultado=1;
      R->valor=min;



}

/*função que realiza a variante C*/
void var_c(Matriz *M,Resultado *R){

    int i, j;
    int c1, l1, c2, l2;   /*variáveis que vão guardar os índices da posição actual do caminho e da próxima*/
    int valor1, valor2;   /*variáveis que vão guardar os valores da posição actual do caminho e da próxima*/
    int count=0;   /*variável que vai contar a quantidade de vezes que o número seguinte foi crescente*/
    int num_pares=0;   /*variável que vai contar a quantidade de vezes que o número seguinte foi par*/



    /*é alocada uma matriz com a dimensão no mapa cuja função vai ser verificar quais das células foram usadas no caminho*/
    M->celulas=aloca_matriz(M->celulas, M->linhas, M->colunas);

    /*inicializada a 0's*/
    for(i=0; i<M->linhas; i++){
        for(j=0; j<M->colunas; j++)
            M->celulas[i][j]=0;
    }

    /*são guardados os valores e os índices das células */
    l1=M->li;
    c1=M->ci;
    valor1=M->mapa[l1][c1];
    l2=M->caminho[0][0];
    c2=M->caminho[0][1];
    valor2=M->caminho[0][2];

    /*verificação que a célula inicial e a primeira do caminho não são a mesma*/
    if( (l1=l2) && (c1=c2)){

        M->celulas=liberta_matriz(M->celulas, M->linhas, M->colunas);
            printf("\n\ncelula ja utilizada1 ");
            R->resultadoC=4;
            return;
    }

    /*as células já fizeram parte do caminho e como tal passam a ter o valor de 1*/
    M->celulas[l1][c1]=1;
    M->celulas[l2][c2]=1;


    /*verifica se as células fazem parte do mapa*/
    if( (fora_do_mapa(l1, c1, M->linhas, M->colunas)==1) || (fora_do_mapa(l2, c2, M->linhas, M->colunas)==1) ){

        printf("\n\ncelulas indicadas para o caminho não estão no mapa!\n\n");
        R->resultadoC=4;
        return;
    }


    /*verifica se os movimentos são válidos*/
    if( ( (c2-c1!=1) && (c2-c1)!=0 && (c2-c1)!=-1) || ( (l2-l1!=1) && (l2-l1)!=0 && (l2-l1)!=-1 ) ){

        printf("caminho de movimentos inválidos");
        R->resultadoC=4;
        return;
    }

    /*verifica se o valor do mapa coincide com o valor no caminho*/
    if(valor1 != M->mapa[l1][c1] || valor2 != M->mapa[l2][c2]){

        printf("\n\nvalor indicado para a celula do caminho nao corresponde ao valor indicado na matriz");
        R->resultadoC=4;
        return;
    }

    /*a contagem de números pares aumenta*/
    if(valor2%2==0)
        num_pares++;

    /*a contagem de números crescentes aumenta*/
    if(valor2>valor1)
        count++;


    /*ciclo que vai percorrer a matriz do caminho e os seus valores*/
    for(i=0; i<M->k-1; i++){

        l1=M->caminho[i][0];
        c1=M->caminho[i][1];
        l2=M->caminho[i+1][0];
        c2=M->caminho[i+1][1];
        valor1=M->caminho[i][2];
        valor2=M->caminho[i+1][2];


        /*células indicadas para o caminho não estão no mapa */
        if( (fora_do_mapa(l1, c1, M->linhas, M->colunas)==1) || (fora_do_mapa(l2, c2, M->linhas, M->colunas)==1) ){

            printf("\n\ncelulas indicadas para o caminho não estão no mapa!\n\n");
            R->resultadoC=4;
            return;
        }

        /*valor indicado para a célula do caminho não corresponde ao valor indicado na matriz*/

        if(valor1 != M->mapa[l1][c1] || valor2 != M->mapa[l2][c2]){

            printf("\n\nvalor indicado para a celula do caminho nao corresponde ao valor indicado na matriz");
            R->resultadoC=4;
            return;
        }

        /*caminho de movimentos inválidos*/
        if( ( (c2-c1!=1) && (c2-c1)!=0 && (c2-c1)!=-1) || ( (l2-l1!=1) && (l2-l1)!=0 && (l2-l1)!=-1 ) ){

            printf("\n\ncaminho de movimentos inválidos");
            R->resultadoC=4;
            return;
        }

        /*a célula já tinha sido parte do caminho e como tal este é inválido*/
        if(M->celulas[l2][c2]==1){

            M->celulas=liberta_matriz(M->celulas, M->linhas, M->colunas);
            printf("\n\ncelula ja utilizada ");
            R->resultadoC=4;
            return;
        }

        /*conta o número de vezes em que o valor seguinte do caminho é maior que o anterior*/
        if(valor2>valor1)
            count++;

        /*aumenta o numero de pares*/
        if(valor2%2==0)
            num_pares++;

        /*confirma que a célula já fez parte do caminho*/
        M->celulas[l2][c2]=1;
    }

    /*caminho válido para ambos os formatos*/
    if((count==M->k) && (num_pares==M->k)){
        printf("\n\n caminho válido para ambos os formatos");
        M->celulas=liberta_matriz(M->celulas, M->linhas, M->colunas);
        R->resultadoC=3;
        return;
    }
    else
    /*caminho válido para números pares*/
    if(num_pares==M->k){
        printf("\n\ncaminho apenas com numeros pares\n\n");
        M->celulas=liberta_matriz(M->celulas, M->linhas, M->colunas);
        R->resultadoC=2;
        return;
    }
    else
    /*caminho válido para números estritamente crescentes*/
    if(count==M->k){
        printf("\n\ncaminho estritamente crescente\n\n");
        M->celulas=liberta_matriz(M->celulas, M->linhas, M->colunas);
        R->resultadoC=1;
        return;
    }
    else{

        printf("\n\n Caminho não tem números pares nem é estritamente crescente");
        M->celulas=liberta_matriz(M->celulas, M->linhas, M->colunas);
        R->resultadoC=-1;
    }

}
