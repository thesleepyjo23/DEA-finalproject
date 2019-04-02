#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    fp = abre_ficheiro( argc, argv[1]);
 
    while(le_problema(fp, &MAT)!=0){
        
        aloca_matriz(&MAT);

        preenche_matriz(fp, &MAT);

        funcionamento(&MAT);

        liberta_matriz(&MAT);
    }
        

}
