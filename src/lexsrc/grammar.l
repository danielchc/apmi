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
simplequote                 "\'"
doublequote                  "\""
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
	yylval.num = atof(yytext);
	return NUMBER;
};

[a-zA-Z]+[a-zA-Z0-9_]*      {
	yylval.str=strdup(yytext);
	yylval.record=get_lexcomp(yytext);
	return (yylval.record->value);
};



{addeq}           { return ADDEQ; }
{subeq}           { return SUBEQ; }
{muleq}           { return MULEQ; }
{diveq}           { return DIVEQ; }
{poweq}           { return POWEQ; }

[-+()=/*^]        { return *yytext; }


[\n]     		  { return *yytext;  }

[ \t]   ;       /* skip whitespace */
[\r]   	;       /* skip whitespace */

.   { 
		return *yytext;
}


<<EOF>> {
	fclose(yyin);
	if ( --include_stack_ptr < 0) {
		yyin=stdin;
		yyrestart(yyin);
		return '\n';
	} else {
		yy_delete_buffer(YY_CURRENT_BUFFER);
		yy_switch_to_buffer(include_stack[include_stack_ptr]);
	}
	
}

%%

int yy_swap_buffer(char* filename){
	if (include_stack_ptr >= MAX_INCLUDE_DEPTH) return -1;
    include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
    FILE* f = fopen(filename, "r");
	if (!f) return -2;
    yyin=f;
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
    BEGIN(INITIAL);
	return 0;
}


