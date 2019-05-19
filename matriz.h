#ifndef MATRIZ_H
#define MATRIZ_H


typedef struct _matriz {
    int linhas;
    int colunas;
    char var;
    int li;
    int ci;
    int k;
    int **mapa;
    int **caminho;
    int **celulas;
} Matriz;


int **aloca_matriz(int **matriz, int linhas, int colunas);

int **preenche_matriz(FILE *fpIn, int **matriz, int linhas, int colunas);

int **preenche_mat_zeros(int **matriz, int linhas, int colunas);

int **liberta_matriz (int **matriz, int linhas, int colunas);

int max_matriz(int **matriz, int *x, int *y);


#endif
