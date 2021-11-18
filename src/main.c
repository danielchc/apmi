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
    yyset_in(stdin);
    if(argc > 1){
        FILE *f=fopen(argv[1],"r");
        if(!f){
            handle_generic_error("No se puido abrir o arquivo %s\n",argv[1]);
            return 1;
        }
        yyset_in(f);
    }
    printf("APMI - Interpete Matemático\nEscribe help() para obter axuda para obter axuda\n\n");
    if(yyget_in()==stdin) prompt();
    yyparse();
	return 0;
}
