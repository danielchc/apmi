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
    prompt();
    yyparse();
	return 0;
}
