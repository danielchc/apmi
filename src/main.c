#include "ts.h"
#include "lex.yy.h"
#include "y.tab.h"
#include "term.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>

int main(int argc, char* argv[]){
    init_ts();
    // Establezco a entrada a entrada estándar
    yyset_in(stdin);
    //Se existe un argumento pasado por parámetro abro establezco como entrada o ficheiro, se paso máis de un mostro un erro
    if(argc == 2){
        FILE *f=fopen(argv[1],"r");
        if(!f){
            handle_generic_error("No se puido abrir o arquivo %s\n",argv[1]);
            return 1;
        }
        yyset_in(f);
    }else if (argc>2){
        handle_generic_error("Número de párametros incorrecto");
        printf("Uso correcto %s <ficheiro>\n",argv[0]);
        return 1;
    }
    printf("APMI - Interpete Matemático\nEscribe help() para obter axuda para obter axuda\n\n");
    if(yyget_in()==stdin) prompt();
    //Inicio o analizador léxico
    yyparse();
	return 0;
}
