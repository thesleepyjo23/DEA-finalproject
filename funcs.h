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

 FILE* abre_ficheiro(int argc, char *argv);
 
 int le_problema(FILE *fp, Matriz *M);

 void aloca_matriz(Matriz *M);

 void liberta_matriz (Matriz *M);

 void preenche_matriz(FILE *fp, Matriz *M);
 
void var_a(Matriz *M);

 void var_b(Matriz *M);

 #endif