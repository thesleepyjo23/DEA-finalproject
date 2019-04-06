#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcs.h"
#define MAX 2147483647

/*variável global que contém os movimentos possíveis a serem feitos*/
int movimentos[8][2] = {{-1,0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};

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

    check = fscanf(fp, "%d %d %c %d %d %d", &linhas, &colunas, &var, &li, &ci, &k);

    if(check!=6){

        return 0;
    }

    M->colunas=colunas;
    M->linhas=linhas;
    M->var=var;
    M->li=li;
    M->ci=ci;
    M->k=k;

    printf("\n\n%d %d %c %d %d %d", linhas, colunas, var, li, ci, k);

    return 1;
 }

 void aloca_matriz(Matriz *M){

    int i;
    

    M->matriz = (int **) malloc( M->linhas*sizeof(int*) );
    
    for(i=0; i<M->linhas; i++)
        M->matriz[i]= (int*) malloc( M->colunas*sizeof(int));
    
 }

void aloca_caminho(Matriz *M){

    int i;


    M->caminho = (int **) malloc( M->k*sizeof(int*) );
        
    for(i=0; i<M->k; i++)
        M->caminho[i]= (int*) malloc( 3*sizeof(int));

 }



void preenche_matriz(FILE *fp, Matriz *M){

    int i, j;


    for(i=0; i<M->linhas; i++){

        for(j=0; j<M->colunas; j++){

            fscanf(fp, "%d", &M->matriz[i][j]);
                
            }
        }

    for(i=0; i<M->linhas; i++){
        printf("\n");
        for(j=0; j<M->colunas; j++){

            printf( "%d ", M->matriz[i][j]);
                
        }
    }
        printf("\n");

}

void preenche_caminho(FILE *fp, Matriz *M){

    int i, j;

   
    for(i=0; i<M->k; i++){

        for(j=0; j<3; j++)
            fscanf(fp, "%d", &M->caminho[i][j]);
    }

    for(i=0; i<M->k; i++){
        printf("\n");
        for(j=0; j<3; j++){

            printf( "%d ", M->caminho[i][j]);
                
        }
    }
}

void liberta_matriz(Matriz *M){

    int i;

    for(i=0; i<M->linhas; i++)
        free(M->matriz[i]);

    free(M->matriz);

}
void liberta_caminho(Matriz *M){

    int i;


     for(i=0; i<M->k; i++)
        free(M->caminho[i]);

    free(M->caminho);
}

int fora_do_mapa(int l, int c, int linhas, int colunas){

    if( (l<0) || (l>=linhas) || (c<0) || (c>=colunas) )      
        return 1;
    
    else 
        return -1;

}


void var_a(Matriz *M){

    int l;
    int i, j;
    int max;
    int check=0;

    /*casos fora do mapa*/
    if( fora_do_mapa(M->li, M->ci, M->linhas, M->colunas)==1  ){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        return;
    }

    max=M->matriz[M->li][M->ci];

    for (l=0; l<8; l++) {
        i = M->li + movimentos[l][0];
        j = M->ci + movimentos[l][1];
        if (fora_do_mapa(i, j, M->linhas, M->colunas)==1) {
          continue;
        }
            
        if (M->matriz[i][j]>max){
            max=M->matriz[i][j];
            check++;
        }
            
    }

    if (check==0){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        return;
    }

    /*escrever 1 e o máximo*/
    printf("\n\nvalor maximo:%d\n\n", max);


}

void var_b(Matriz *M){

    
    int l;
    int i, j;
    int min=MAX; 
    int num_pares=0;

    /*casos fora do mapa*/
    if( fora_do_mapa(M->li, M->ci, M->linhas, M->colunas)==1 ){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        return;
    }

    for (l=0; l<8; l++) {
        i = M->li + movimentos[l][0];
        j = M->ci + movimentos[l][1];
        if (fora_do_mapa(i, j, M->linhas, M->colunas)==1) {
          continue;
        }
        
        if ( (M->matriz[i][j]%2==0) )
            num_pares++;

            
        if( (M->matriz[i][j]%2==0) && (M->matriz[i][j]<min) ){
            min=M->matriz[i][j];
        }
            
    }

    if(num_pares==0){

        /*escrever -1*/
        printf("\n\n-1\n\n");
        return;
    }

    /*escrever 1 e o mínimo*/
    printf("\n\nnumeros pares:%d  valor minimo:%d\n\n", num_pares, min);
    

}


void var_c(Matriz *M){

    int i;
    int c1, l1, c2, l2;
    int valor1, valor2;
    int count=0, num_pares=0; 
  
    l1=M->li;
    c1=M->ci;
    valor1=M->matriz[l1][c1];
    l2=M->caminho[0][0];
    c2=M->caminho[0][1];
    valor2=M->caminho[0][2];

    if( (fora_do_mapa(l1, c1, M->linhas, M->colunas)==1) || (fora_do_mapa(l2, c2, M->linhas, M->colunas)==1) ){

            printf("\n\ncelulas indicadas para o caminho não estão no mapa!\n\n");
            return;
    }

    if( ( (c2-c1!=1) && (c2-c1)!=0 && (c2-c1)!=-1) || ( (l2-l1!=1) && (l2-l1)!=0 && (l2-l1)!=-1 ) ){

        printf("caminho de movimentos inválidos");
        return;
    }

    if(valor1 != M->matriz[l1][c1] || valor2 != M->matriz[l2][c2]){

            printf("\n\nvalor indicado para a celula do caminho nao corresponde ao valor indicado na matriz");
            return;
    }

    if(valor2%2==0)
        num_pares++;

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


        printf("\n\nl1:%d c1:%d valor1:%d\n", l1, c1, valor1);
        printf("l2:%d c2:%d valor2:%d\n", l2, c2, valor2);

        /*células indicadas para o caminho não estão no mapa */
        if( (fora_do_mapa(l1, c1, M->linhas, M->colunas)==1) || (fora_do_mapa(l2, c2, M->linhas, M->colunas)==1) ){

            printf("\n\ncelulas indicadas para o caminho não estão no mapa!\n\n");
            return;
        }

            
        /*valor indicado para a célula do caminho não corresponde ao valor indicado na matriz*/
        if(valor1 != M->matriz[l1][c1] || valor2 != M->matriz[l2][c2]){

            printf("\n\nvalor indicado para a celula do caminho nao corresponde ao valor indicado na matriz");
            return;
        }

        /*caminho de movimentos inválidos*/
        if( ( (c2-c1!=1) && (c2-c1)!=0 && (c2-c1)!=-1) || ( (l2-l1!=1) && (l2-l1)!=0 && (l2-l1)!=-1 ) ){

            printf("caminho de movimentos inválidos");
            return;
        }

        /*conta o número de vezes em que o valor seguinte do caminho é maior que o anterior*/
        if(valor2>valor1)
            count++;

        /*aumenta o numero de pares*/
        if(valor2%2==0)
            num_pares++;                           
    }    

    /*caminho válido para ambos os formatos*/
    if((count==M->k) && (num_pares==M->k)){
        printf("\n\n caminho válido para ambos os formatos");
        return;
    }
    else
    /*caminho válido para números pares*/
    if(num_pares==M->k){
        printf("\n\ncaminho apenas com numeros pares\n\n");
        return;
    }
    else
    /*caminho válido para números estritamente crescentes*/
    if(count==M->k){
        printf("\n\ncaminho estritamente crescente\n\n");
        return;
    }
    else{

        printf("\n\n Caminho não tem números pares nem é estritamente crescente");
    }



}
