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
    int **caminho;
} Matriz;

extern int movimentos[8][2];

 FILE* abre_ficheiro(int argc, char *argv);
 
 int le_problema(FILE *fp, Matriz *M);

 void aloca_matriz(Matriz *M);

 void aloca_caminho(Matriz *M);

 void preenche_matriz(FILE *fp, Matriz *M);

 void preenche_caminho(FILE *fp, Matriz *M);

 void liberta_matriz (Matriz *M);

 void liberta_caminho(Matriz *M);

 int fora_do_mapa(int l, int c, int linhas, int colunas);
 
 void var_a(Matriz *M);

 void var_b(Matriz *M);

 void var_c(Matriz *M);

 #endif