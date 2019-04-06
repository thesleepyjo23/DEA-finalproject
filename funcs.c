#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcs.h"
#define MAX 2147483647

/*variável global que contém os movimentos possíveis a serem feitos*/
int movimentos[8][2] = {{-1,0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};

/*função que abre os ficheiros*/
 FILE* abre_ficheiro(int argc, char *argv){

    FILE *fp;
    int x=0;


    /*verifica se o utilizador está a executar o programa com 2 inputs*/
    if (argc != 2) {
        fprintf(stderr, "Modo de utilização: ./<nomedoexecutavel> <nomedoficheiro.puz0>\n");
        exit(1);
    }

    fp = fopen ( argv, "r" );
    if ( fp == NULL ) {
        fprintf ( stderr, "Erro ao abrir o ficheiro .puz0 '%s'\n", argv);
        exit ( 1 );
    }


    /*verifica se o nome do ficheiro a ser aberto acaba em .puz0*/
    x=strlen(argv);

    if( (argv[x-5]!='.') || (argv[x-4]!='p') || (argv[x-3]!='u') || (argv[x-2]!='z') || (argv[x-1]!='0') ){

        fprintf(stderr, "Modo de utilização: ./<nomedoexecutavel> <nomedoficheiro.puz0>\n");
        exit (2);
    } 

    return fp;

 }

 int le_problema(FILE *fp, Matriz *M){

    int colunas;
    int linhas;
    int li, ci;
    int k;
    int check;
    char var;

    /*leitura dos 6 parametros que definem o problema*/
    check = fscanf(fp, "%d %d %c %d %d %d", &linhas, &colunas, &var, &li, &ci, &k);

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


/*função que aloca memória para uma matriz de dimensão "linhas" x "colunas"*/
 int **aloca_matriz(int **matriz, int linhas, int colunas){

    int i;
    
    matriz = (int **) malloc( linhas*sizeof(int*) );
    
    for(i=0; i<linhas; i++)
        matriz[i]= (int*) malloc( colunas*sizeof(int));
    

    return matriz;
 }

/*função que preenche a matriz tendo em conta o que é lido no ficheiro*/
int **preenche_matriz(FILE *fp, int **matriz, int linhas, int colunas){

    int i, j;

    for(i=0; i<linhas; i++){

        for(j=0; j<colunas; j++){

            fscanf(fp, "%d", &matriz[i][j]);
                
        }
    }

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

/*função que verifica se as posições indicadas estão fora do mapa*/
int fora_do_mapa(int l, int c, int linhas, int colunas){

    /*se forem menores que 0 ou maiores (ou iguais, em c começamos em 0) que a dimensão da matriz estão claramente fora do mapa*/
    if( (l<0) || (l>=linhas) || (c<0) || (c>=colunas) )      
        return 1;
    
    else 
        return -1;

}

/*função que realiza a variante A*/
void var_a(Matriz *M){

    int l;
    int i, j;
    int max;  /*variável que vai conter o valor máximo*/
    int check=0; /*variável que vai contar quantas células adjacentes possuem um valor maior que a célula inicial do problema*/

    /*casos fora do mapa*/
    if( fora_do_mapa(M->li, M->ci, M->linhas, M->colunas)==1  ){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        return;
    }

    /*o número máximo inicial é o da célula indicada pelo problema*/
    max=M->mapa[M->li][M->ci];

    /*ciclo que vai percorrer as posições adjacentes e usar o valor das válidas*/
    for (l=0; l<8; l++) {
        /*são somados aos índices os movimentos possíveis a seres feitos*/
        i = M->li + movimentos[l][0];
        j = M->ci + movimentos[l][1];
        /*posições não válidas, ou seja, fora do mapa*/
        if (fora_do_mapa(i, j, M->linhas, M->colunas)==1) {
          continue;
        }
        
        /*se o número da célula actual for maior este passa a ser o maior*/
        if (M->mapa[i][j]>max){
            max=M->mapa[i][j];
            check++;
        }
            
    }

    /*caso em que não é encontrada nenhuma célula com valor maior*/
    if (check==0){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        return;
    }

    /*é escrito 1 e o valor máximo das células adjacentes*/
    printf("\n\nvalor maximo:%d\n\n", max);


}


/*função que realiza a variante B*/
void var_b(Matriz *M){

    
    int l;
    int i, j;
    int min=MAX; /*número que vai conter o valor mínimo par, é inicializado com o maior inteiro possível em C*/
    int num_pares=0;  /*variável que vai contar a quantidade de números pares adjacentes à célula inicial*/

    /*casos fora do mapa*/
    if( fora_do_mapa(M->li, M->ci, M->linhas, M->colunas)==1 ){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        return;
    }

    /*ciclo que vai percorrer as posições adjacentes e usar o valor das válidas*/
    for (l=0; l<8; l++) {
        i = M->li + movimentos[l][0];
        j = M->ci + movimentos[l][1];
        if (fora_do_mapa(i, j, M->linhas, M->colunas)==1) {
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
        return;
    }

    /*escrever 1 e o mínimo*/
    printf("\n\nnumeros pares:%d  valor minimo:%d\n\n", num_pares, min);
    

}

/*função que realiza a variante C*/
void var_c(Matriz *M){

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
            printf("\n\ncelula ja utilizada ");
            return;
    }
   
    /*as células já fizeram parte do caminho e como tal passam a ter o valor de 1*/
    M->celulas[l1][c1]=1;
    M->celulas[l2][c2]=1;

    
    /*verifica se as células fazem parte do mapa*/
    if( (fora_do_mapa(l1, c1, M->linhas, M->colunas)==1) || (fora_do_mapa(l2, c2, M->linhas, M->colunas)==1) ){

        printf("\n\ncelulas indicadas para o caminho não estão no mapa!\n\n");
        return;
    }


    /*verifica se os movimentos são válidos*/
    if( ( (c2-c1!=1) && (c2-c1)!=0 && (c2-c1)!=-1) || ( (l2-l1!=1) && (l2-l1)!=0 && (l2-l1)!=-1 ) ){

        printf("caminho de movimentos inválidos");
        return;
    }

    /*verifica se o valor do mapa coincide com o valor no caminho*/
    if(valor1 != M->mapa[l1][c1] || valor2 != M->mapa[l2][c2]){

        printf("\n\nvalor indicado para a celula do caminho nao corresponde ao valor indicado na matriz");
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
            return;
        }

            
        /*valor indicado para a célula do caminho não corresponde ao valor indicado na matriz*/
        if(valor1 != M->mapa[l1][c1] || valor2 != M->mapa[l2][c2]){

            printf("\n\nvalor indicado para a celula do caminho nao corresponde ao valor indicado na matriz");
            return;
        }

        /*caminho de movimentos inválidos*/
        if( ( (c2-c1!=1) && (c2-c1)!=0 && (c2-c1)!=-1) || ( (l2-l1!=1) && (l2-l1)!=0 && (l2-l1)!=-1 ) ){

            printf("\n\ncaminho de movimentos inválidos");
            return;
        }

        /*a célula já tinha sido parte do caminho e como tal este é inválido*/
        if(M->celulas[l2][c2]==1){

            M->celulas=liberta_matriz(M->celulas, M->linhas, M->colunas);
            printf("\n\ncelula ja utilizada ");
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
        return;
    }
    else
    /*caminho válido para números pares*/
    if(num_pares==M->k){
        printf("\n\ncaminho apenas com numeros pares\n\n");
        M->celulas=liberta_matriz(M->celulas, M->linhas, M->colunas);
        return;
    }
    else
    /*caminho válido para números estritamente crescentes*/
    if(count==M->k){
        printf("\n\ncaminho estritamente crescente\n\n");
        M->celulas=liberta_matriz(M->celulas, M->linhas, M->colunas);
        return;
    }
    else{

        printf("\n\n Caminho não tem números pares nem é estritamente crescente");
        M->celulas=liberta_matriz(M->celulas, M->linhas, M->colunas);
    }

}
