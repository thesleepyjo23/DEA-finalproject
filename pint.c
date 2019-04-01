#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcs.h"


 /*
 *  Function:
 *    main()
 *
 */
int main(int argc, char *argv[]) {

    Matriz MAT;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "Modo de utilização: %s <nomedoficheiro.puz0>\n", argv[0]);
        exit(1);
    }

    fp = fopen ( argv[1], "r" );
    if ( fp == NULL ) {
        fprintf ( stderr, "Erro ao abrir o ficheiro .puz0 '%s'\n", argv[1]);
        exit ( 1 );
    }

    le_problema(fp, &MAT);

    aloca_matriz(&MAT);

    /*preenche_matriz();*/

    liberta_matriz(&MAT);
    



}
