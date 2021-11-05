
%option noyywrap
%{
    #include "y.tab.h"
    #include "ts.h"
    #include <stdlib.h>
    void yyerror(char *);
%}
digit                       ([0-9]_?)+
exp                         [eE][+-]?{digit}+
integer                     {digit}{exp}?
decimal                     ({digit})*\.({digit}){exp}?
%%

{decimal}|{integer}   {  
                yylval.num = atof(yytext);
                return NUMBER;
            }

[a-z]+      {
                yylval.str=strdup(yytext);
                return ID;
            };



[-+()=/*]     	{ return *yytext; }

[\n]     		{ return *yytext; }

[ \t]   ;       /* skip whitespace */

.               yyerror("Unknown character");

%%
