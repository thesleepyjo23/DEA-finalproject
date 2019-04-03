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

        switch(MAT.var) {
            case 'A' :
                /*fazer variável a*/
                printf("\n\nfunção a\n\n");
            break;
            case 'B' :
                printf("\n\nfunção b\n\n");
                var_b(&MAT);
            break;
            case 'C' :
                /*fazer função c*/
                printf("\n\nfunção c\n\n");
            break;
            default :
            /*escrever -1*/
            printf("\n\nmau comando\n\n");
        }
        
        liberta_matriz(&MAT);
    }
        

}
