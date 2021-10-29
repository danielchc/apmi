#include "syntactic_analyzer.h"

/*
	init_analyze
		inicia o análise léxico
*/
void init_analyze(){
	lexcomp_t* current_lex=malloc(sizeof(lexcomp_t));
	char *lex=malloc(KEYWORDSIZE);
	do{
		next_lexcomp(current_lex);
		//Mostro en claro os valores dos lexema
		if(current_lex->value==_EOF)strcpy(lex,"<EOF>");
		else if(current_lex->value==_NEWLINE)strcpy(lex,"<NEWLINE>");
		else if(current_lex->value==_TERROR)continue;
		
		else strcpy(lex,current_lex->keyword);
		printf("LINEA %d ->\t<%d,%s>\n",get_current_line(),current_lex->value,lex);
	}while(current_lex->value!=_EOF);
	free(lex);
}