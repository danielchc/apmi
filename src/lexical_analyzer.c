#include "lexical_analyzer.h"
#include "lex.yy.h"


FILE *f;
/*
	init_la
		inicializa o analizar léxico
    param:
        char * file ficheiro a analizar
    return:
        0 se hai erro
        1 se todo vai ben 
*/
int init_la(char * file){
    f=fopen(file,"r");
    yyset_in(f);
    return (f != NULL);
}

/*
	destroy_la
		destrue o analizar léxico
*/
void destroy_la(){
    fclose(f);
    yylex_destroy();
}


/*
	next_lexcomp
		devolve o seguinte compoñente léxico por referencia
    param:
        lexcomp_t* lexcomp: punteiro onde gardar o compoñente léxico
*/
void next_lexcomp(lexcomp_t* lexcomp){
    lexcomp->value=yylex();
    strcpy(lexcomp->keyword,yyget_text());
}

