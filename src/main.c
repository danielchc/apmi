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
    printf("APMI - Interpete Matemático\nEscribe help() para obter axuda para obter axuda\n");
    init_ts();
    yyset_in(stdin);
    if(argc > 1){
        FILE *f=fopen(argv[1],"r");
        if(!f){
            printf("Error: No se puido abrir o arquivo %s\n",argv[1]);
            return 1;
        }
        yyset_in(f);
    }
    prompt();
    yyparse();
	return 0;
}
