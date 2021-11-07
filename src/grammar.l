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
addeq						"+="		
subeq						"-="		
muleq						"*="		
diveq						"/="
poweq						"^="

%%


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
