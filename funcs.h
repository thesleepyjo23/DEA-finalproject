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

 int le_problema(FILE *fp, Matriz *M);

 void aloca_matriz(Matriz *M);

 void liberta_matriz (Matriz *M);

 void preenche_matriz(FILE *fp, Matriz *M);
 
 #endif