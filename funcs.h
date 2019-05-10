#ifndef funcs
#define funcs
#define Extensao_fpOut ".vrf"

typedef struct LinkedListStruct node;

struct LinkedListStruct
{
    int x;
    int y;
    int val;
    node *next;
};


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

typedef struct _resultado{
  int resultadoC;
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

int le_problema(FILE *fpIn, Matriz *M);

int **aloca_matriz(int **matriz, int linhas, int colunas);

int **preenche_matriz(FILE *fpIn, int **matriz, int linhas, int colunas);

int **preenche_mat_celulas(int **matriz, int linhas, int colunas);

int **liberta_matriz (int **matriz, int linhas, int colunas);

int fora_do_mapa(int l, int c, int linhas, int colunas);

char *Muda_extensao(const char *nome_ficheiro, const char *nova_extensao);

void escreve_Ficheiro_Saida(FILE *fp, Matriz *M, Resultado *R);

node *explore(Matriz * M, int x, int y, int k, int (*valido)(Matriz*,int,int,int,int));

int par(Matriz * M, int x, int y, int nx, int ny);

int crescente(Matriz * M, int x, int y, int nx, int ny);

int decrescente(Matriz * M, int x, int y, int nx, int ny);

void print_list(node * list);

void free_list(node *no);

 #endif
