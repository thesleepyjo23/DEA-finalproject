#ifndef funcs
#define funcs

typedef struct _matriz {
    int linhas;
    int colunas;
    char var;
    int li;
    int ci;
    int k;
    int **matriz;
} Matriz;

 void le_problema(FILE *fp, Matriz *M);

 void aloca_matriz(Matriz *M);

 void liberta_matriz (Matriz *M);
 
 #endif