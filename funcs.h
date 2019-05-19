#ifndef FUNCS_H
#define FUNCS_H

#include <stdint.h>
#include "matriz.h"
#define Extensao_fpOut ".path"
#define PAR 1
#define CRESCENTE -1

typedef struct LinkedListStruct node;

struct LinkedListStruct
{
    int x;
    int y;
    int val;
    node *next;
};

typedef struct _resultado{
  int resultado;
  int valor;

}Resultado;

typedef struct _lista{

  int l;
  int c;
  int valor;

} Caminho;

extern int movimentos[8][2];

FILE* abre_ficheiro(int argc, char *argv);

int le_problema(FILE *fpIn,Matriz *M, Resultado *R);

int fora_do_mapa(int l, int c, int linhas, int colunas);

char *Muda_extensao(const char *nome_ficheiro, const char *nova_extensao);

void Ficheiro_Saida(FILE *fpO, Matriz *M, node * list,int k_real);

node *explore(Matriz * M, int x, int y, int k, int (*valido)(Matriz*,int,int,int,int));

node *longest_path(Matriz * M, int **lp, int x, int y, int prev_max);

void preenche_lp(int ***lp, Matriz * M, int x, int y, int (*valido)(Matriz*,int,int,int,int));

int par(Matriz * M, int x, int y, int nx, int ny);

int Atual_par(Matriz * M, int x, int y, int nx, int ny);

int crescente(Matriz * M, int x, int y, int nx, int ny);

int decrescente(Matriz * M, int x, int y, int nx, int ny);

int print_list(node * list, FILE *fpO,Resultado *R);

node* muda_partida (Matriz *MAT, node* caminho, int criterio);

void free_list(node *no);

 #endif
