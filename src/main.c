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
    prompt();
    while(1) yyparse();
	return 0;
}
