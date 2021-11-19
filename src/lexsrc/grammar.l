%option noyywrap
%option nounput
%option noinput
%{
    #include "term.h"
    #include "y.tab.h"
    #include "error_handler.h"
    #include <stdlib.h>
	#define MAX_INCLUDE_DEPTH 10
	YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
	int include_stack_ptr = 0;
    void yyerror(char *);
	int yy_swap_buffer(char* filename);
%}
%x STRINGSIMPLE
%x STRINGDOUBLE
digit                       ([0-9]_?)+
exp                         [eE][+-]?{digit}+
integer                     {digit}{exp}?
decimal                     ({digit})*\.({digit}){exp}?
addeq						"+="		
subeq						"-="		
muleq						"*="		
diveq						"/="
poweq						"^="
modeq						"%="
simplequote                 "\'"
doublequote                  "\""
comment                     "#"[^\n]*
%%


{simplequote}     {
	/* Inicia un string */
	BEGIN( STRINGSIMPLE ); 
}
<STRINGSIMPLE>{simplequote} {
	/* Devolve que é un string, final de cadea*/
    yytext[strlen(yytext)-1]='\0';
    yylval.str=strdup(yytext);
	BEGIN(INITIAL);
	return STRING;
}

<STRINGSIMPLE>.   { 
	/* Calquer outro caracter */
	yymore(); 
}

<STRINGSIMPLE>\n {
	/*Da erro porque atopa o fin de ficheiro*/
	BEGIN(INITIAL);
	yyerror("String sen cerrar");
}


{doublequote}     { 
	/* Inicia un string */
	BEGIN( STRINGDOUBLE ); 
}
<STRINGDOUBLE>{doublequote} {
	/* Devolve que é un string, final de cadea*/
    yytext[strlen(yytext)-1]='\0';
    yylval.str=strdup(yytext);
	BEGIN(INITIAL);
	return STRING;
}
<STRINGDOUBLE>.   { 
	/* Calquer outro caracter */
	yymore(); 
}
<STRINGDOUBLE>\n {
	/*Da erro porque atopa o fin de ficheiro*/
	BEGIN(INITIAL);
	yyerror("String sen cerrar");
}


{decimal}|{integer}   { 
	/* Converte calquer número a un flotante */
	yylval.num = atof(yytext);
	return NUMBER;
};

[a-zA-Z]+[a-zA-Z0-9_]*      {
	//Se non existe o identificador na táboa de simbolos, buscase primeiro se existe nunha libreria
	if(!keyword_exist_ts(yytext)){
		double (*fptr)();
		//Obteño a librerías que están cargadas
		linked_lib_t* aux=get_linked_libs();
		//Recorro as librerias e busco se existe algunha función co nome do símbolo introducido
		while(aux!=NULL){
			fptr=dlsym(aux->current, yytext);
			if(fptr && (add_ext_fun(yytext,fptr)!=-1)){
				break;
			}
			aux=aux->next;
		};
	}
	
	/*
		Gardo a cadea de texto que vou empregar, e busco na táboa de símbolos o símbolo
		se non existe creará un novo símbolo e asignaralle o valor 0.0
	*/
	yylval.str=strdup(yytext);
	yylval.record=get_lexcomp(yytext);
	return (yylval.record->value);
};


{comment}    	;     
{addeq}           { return ADDEQ; }
{subeq}           { return SUBEQ; }
{muleq}           { return MULEQ; }
{diveq}           { return DIVEQ; }
{poweq}           { return POWEQ; }
{modeq}           { return MODEQ; }

[-+()=/*^%]        { return *yytext; }


[\n]     		  { return *yytext;  }


[ \t]   		;      /* Ignoro os saltos os retorno de carro, tabulacións e espacios */
[\r]   			;      
 

.   { 
		return *yytext;
}


<<EOF>> {
	//Cando chego o final dun ficheiro cerro a ficheiro
	fclose(yyin);
	//Se non hai máis ficheiros que leer establezco a entrada a entrada estándar
	if ( --include_stack_ptr < 0) {
		yyin=stdin;
		yyrestart(yyin);
	//Se existe outro ficheiro cambio o buffer a dito ficheiro
	} else {
		yy_delete_buffer(YY_CURRENT_BUFFER);
		yy_switch_to_buffer(include_stack[include_stack_ptr]);
	}
	return '\n';
	
}

%%

int yy_swap_buffer(char* filename){
	//Se excedo o nivel de profundidad de carga de ficheiros devolvo erro
	if (include_stack_ptr >= MAX_INCLUDE_DEPTH) 
		return -1;
	//Establezco o buffer siguiente co buffer actual para escribir o novo buffer no actual
    include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
    FILE* f = fopen(filename, "r");
	//Se non existe o ficheiro devolvo erro
	if (!f) 
		return -2;
	//Establezco o ficheiro como nova entrada
	yyset_in(f);
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
    BEGIN(INITIAL);
	return 0;
}


