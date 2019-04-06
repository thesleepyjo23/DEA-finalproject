#ifndef funcs
#define funcs


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

extern int movimentos[8][2];

 FILE* abre_ficheiro(int argc, char *argv);
 
 int le_problema(FILE *fp, Matriz *M);

 int **aloca_matriz(int **matriz, int linhas, int colunas);

 int **preenche_matriz(FILE *fp, int **matriz, int linhas, int colunas);

 int **liberta_matriz (int **matriz, int linhas, int colunas);

 int fora_do_mapa(int l, int c, int linhas, int colunas);
 
 void var_a(Matriz *M);

 void var_b(Matriz *M);

 void var_c(Matriz *M);

 #endif