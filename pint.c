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
    int aux=0;
    
    fp = abre_ficheiro( argc, argv[1]);
 
    /*enquanto há problemas a serem lidos*/
    while(le_problema(fp, &MAT)!=0){
    
        switch(MAT.var) {
            case 'A' :
                /*fazer a função a*/
                printf("\n\nfunção a\n\n");
                aloca_matriz(&MAT);
                preenche_matriz(fp, &MAT);
                var_a(&MAT);
                liberta_matriz(&MAT);
                aux=0;
            break;
            case 'B' :
                /*fazer a função b*/
                printf("\n\nfunção b\n\n");
                aloca_matriz(&MAT);
                preenche_matriz(fp, &MAT);
                var_b(&MAT);
                liberta_matriz(&MAT);
                aux=0;
            break;
            case 'C' :
                /*fazer função c*/
                printf("\n\nfunção c\n\n");
                aloca_caminho(&MAT);
                preenche_caminho(fp,&MAT);
                aloca_matriz(&MAT);
                preenche_matriz(fp, &MAT);
                var_c(&MAT);
                liberta_caminho(&MAT);
                liberta_matriz(&MAT);
                aux=0;

            break;
            default :
                /* O comando da variante é inválido*/
                if(aux==0)
                    printf("\n\nmau comando\n\n");

        	    aux++;
         
        }

    }
        
        return 0;

}
