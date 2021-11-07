%option nounput
%option noinput
%option noyywrap
%{
    #include "ts.h"
    #include "y.tab.h"
    #include <stdlib.h>
    void yyerror(char *);
%}
digit                       ([0-9]_?)+
exp                         [eE][+-]?{digit}+
integer                     {digit}{exp}?
decimal                     ({digit})*\.({digit}){exp}?

LOAD                "load "|"LOAD "
HELP                "HELP"|"help"
EXIT                "exit"|"EXIT"|"quit"|"QUIT"
WORKSPACE           "vars"|"VARS"


%%


{decimal}|{integer}   {  
                yylval.num = atof(yytext);
                return NUMBER;
            }

[a-z]+      {
                yylval.str=strdup(yytext);
                yylval.record=get_lexcomp(yytext);
                printf("Tipo:%d\n",yylval.record->value);
                return (yylval.record->value);
            };



[-+()=/*^]     	{ return *yytext; }

[\n]     		{ return *yytext;  }

[ \t]   ;       /* skip whitespace */

.               yyerror("Unknown character");

%%
