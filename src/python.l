%option nounput
%option noinput
%option noyywrap
%{
	#include "error_handler.h"
	#include "definitions.h"
	int lines=1;
%}

%x DOCSTRING
%x STRINGSIMPLE
%x STRINGDOUBLE


/* Dixitos */
digit                       ([0-9]_?)+
/*Exponentes e10/e-10/e+15*/
exp                         "e"[+-]?{digit}+
/*Numeros enteiros 10/10e10/10e-10*/
number                      {digit}{exp}?
/*Números decimais 3.14/3.14e10/3.14e-10  */
decimal                     ({digit})*\.({digit}){exp}?
/*Binario octal e hexadecimal*/

binstart					"0"[bB]
hexstart					"0"[xX]
octstart 					"0"[oO]

bin                         {binstart}[01]+
hex                         {hexstart}[0-9a-fA-F]+
oct                         {octstart}[0-7]+

/*Simbolos compostos*/
shiftl						"<<"			
shiftr						">>"		
pow							"**"		
fdiv						"\/\/"		
leq							"<="		
geq							">="		
eq							"=="			
neq							"!="		
funa						"->"		
addeq						"+="		
subeq						"-="		
muleq						"*="		
diveq						"/="		
pereq						"%="		
iand						"&="		
ior							"|="		
ixor						"^="		
shtleq						">>="		
shtreq						"<<="		
poweq						"**="		
fdiveq						"\/\/="

/*Simbolos simples*/
simpletokens                "+"|"-"|"*"|"\/"|"%"|"@"|"&"|"|"|"^"|"~"|"("|")"|"["|"]"|"{"|"}"|","|":"|"."|";"|"="|">"|"<"	

/* Cadea simple */
simplequote                 "\'"
/*Cadea con doble comilla */
doublequote                  "\""
/*Comentario #*/
comment                     "#"[^\n]*
/*Identificador*/
alphanumeric                [a-zA-Z0-9_]

alpha                		[a-zA-Z_]

/*Inicio e fin dun docstring*/
docstringse                  \"\"\"


%%
"False"	 	 		{return _FALSE;}
"await"	 	 		{return _AWAIT;}
"else"	 	 		{return _ELSE;}
"import"	 		{return _IMPORT;}
"pass"	 	 		{return _PASS;}
"None"	 	 		{return _NONE;}
"break"	 	 		{return _BREAK;}
"except"	 		{return _EXCEPT;}
"in"	 	 		{return _IN;}
"raise"	 	 		{return _RAISE;}
"True"	 	 		{return _TRUE;}
"class"	 	 		{return _CLASS;}
"finally"	 		{return _FINALLY;}
"is"	 	 		{return _IS;}
"return"	 		{return _RETURN;}
"and"	 	 		{return _AND;}
"continue"	 		{return _CONTINUE;}
"for"	 	 		{return _FOR;}
"lambda"	 		{return _LAMBDA;}
"try"	 	 		{return _TRY;}
"as"	 	 		{return _AS;}
"def"	 	 		{return _DEF;}
"from"	 	 		{return _FROM;}
"nonlocal"	 		{return _NONLOCAL;}
"while"	 	 		{return _WHILE;}
"assert"	 		{return _ASSERT;}
"del"	 	 		{return _DEL;}
"global"	 		{return _GLOBAL;}
"not"	 	 		{return _NOT;}
"with"	 	 		{return _WITH;}
"async"	 	 		{return _ASYNC;}
"elif"	 	 		{return _ELIF;}
"if"	 	 		{return _IF;}
"or"	 	 		{return _OR;}
"yield"	 	 		{return _YIELD;}


{bin}               {return _INTEGER;}
{hex}               {return _INTEGER;}
{oct}               {return _INTEGER;}

{binstart}.?		{
	/*Empeza por 0b pero non continua con números binarios */
	handle_lexical_error(ERR_NUMERIC,yytext);
	return _TERROR;
}
{hexstart}.?		{
	/*Empeza por 0x pero non continua con números hexadecimais */
	handle_lexical_error(ERR_NUMERIC,yytext);
	return _TERROR;
} 
{octstart}.?		{
	/*Empeza por 0o pero non continua con números octais */
	handle_lexical_error(ERR_NUMERIC,yytext);
	return _TERROR;
} 

{decimal}           {return _DECIMAL;}
{number}            {return _INTEGER;}





{shiftl}			{return _SHIFTL;}
{shiftr}			{return _SHIFTR;}
{pow}				{return _POW;}
{fdiv}				{return _FDIV;}
{leq}				{return _LEQ;}
{geq}				{return _GEQ;}
{eq}				{return _EQ;}
{neq}				{return _NEQ;}
{funa}				{return _FUNA;}
{addeq}				{return _ADDEQ;}
{subeq}				{return _SUBEQ;}
{muleq}				{return _MULEQ;}
{diveq}				{return _DIVEQ;}
{pereq}				{return _PEREQ;}
{iand}				{return _IAND;}
{ior}				{return _IOR;}
{ixor}				{return _IXOR;}
{shtleq}			{return _SHTLEQ;}
{shtreq}			{return _SHTREQ;}
{poweq}				{return _POWEQ;}
{fdiveq}			{return _FDIVEQ;}





{simplequote}     {
	/* Inicia un string */
	BEGIN( STRINGSIMPLE ); 
	yymore(); 
}
<STRINGSIMPLE>{simplequote} {
	/* Devolve que é un string, final de cadea*/
	BEGIN(INITIAL);
	return _STRING;
}

<STRINGSIMPLE>.   { 
	/* Calquer outro caracter */
	yymore(); 
}

<STRINGSIMPLE><<EOF>> {
	/*Da erro porque atopa o fin de ficheiro*/
	BEGIN(INITIAL);
	handle_lexical_error(ERR_QUOTE,"String sen cerrar");
	return _EOF;
}


{doublequote}     { 
	/* Inicia un string */
	BEGIN( STRINGDOUBLE ); 
	yymore(); 
}
<STRINGDOUBLE>{doublequote} {
	/* Devolve que é un string, final de cadea*/
	BEGIN(INITIAL);
	return _STRING;
}
<STRINGDOUBLE>.   { 
	/* Calquer outro caracter */
	yymore(); 
}
<STRINGDOUBLE><<EOF>> {
	/*Da erro porque atopa o fin de ficheiro*/
	BEGIN(INITIAL);
	handle_lexical_error(ERR_QUOTE,"String sen cerrar");
	return _EOF;
}





{docstringse}     {
	/* Inicia un docstring */
	BEGIN( DOCSTRING ); 
	yymore(); 
}
<DOCSTRING>.      { 
	/* Calquer outro caracter */
	yymore(); 
}
<DOCSTRING>\n     {
	/*Detecta o salto de linea, engade o número de liñas*/
	yymore(); 
	lines++;
}
<DOCSTRING>{docstringse} {
	/*Termina a docstring */
	BEGIN(INITIAL);
	return _DOCSTRING;
}
<DOCSTRING><<EOF>> {
	/*Da erro porque atopa o fin de ficheiro*/
	handle_lexical_error(ERR_QUOTE,"Docstring sen cerrar");
	return _EOF;
}


{simpletokens}        	{return yytext[0];}
{comment}             	{ /*Ignoro os comentarios */}

{alpha}{alphanumeric}+ 	{
	/*Gardo na táboa de simbolos o Identificador*/
	save_lexcomp(yytext,_ID);
	return _ID;     
}


[\n\r]                   {
	/* Aumento o número de liñas*/ 
	lines++;
	return _NEWLINE;
}

[ \t]+               { }
.                    { }
<<EOF>>              { return _EOF;}
%%



/*
	get_current_line
		devolve o número liña actual a analizar
	return:
		devolve o número liña actual a analizar
*/

int get_current_line(){
    return lines;
}