%option nounput
%option noinput
%option noyywrap
%{
    #include "ts.h"
    #include "y.tab.h"
    #include <stdlib.h>
    void yyerror(char *);
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
            }

[a-zA-Z]+      {
                yylval.str=strdup(yytext);
                yylval.record=get_lexcomp(yytext);
                //printf("Tipo:%d\n",yylval.record->value);
                return (yylval.record->value);
            };



{addeq}           { return ADDEQ; }
{subeq}           { return SUBEQ; }
{muleq}           { return MULEQ; }
{diveq}           { return DIVEQ; }
{poweq}           { return POWEQ; }

[-+()=/*^]     	{ return *yytext; }


[\n]     		{ return *yytext;  }

[ \t]   ;       /* skip whitespace */

.               {}

%%
