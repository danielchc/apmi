%{
    #include "ts.h"
    #include "error_handler.h"
    #include <stdio.h>
    #include <math.h>
    #include <stdlib.h>
    #include "term.h"
    #include "lex.yy.h"
    void yyerror(char *);
    int yylex(void);
%}

%right '='
%left '-' '+'
%left '*' '/' '%'
%right '^'
%nonassoc UMINUS

%union{
    char* str;
    double num;
    ts_record_t* record;
}

%token <num> NUMBER          
%token <record> VAR CONST SYSFUN MATHFUN 
%token <str> STRING

%token ADDEQ SUBEQ MULEQ DIVEQ POWEQ MODEQ;
%type <num> expression

%%

program:
        |
        program statement
        ;

statement:
        '\n'{
           if(yyget_in()==stdin) prompt();
        }
        | expression  '\n'                  { 
            if(get_echo()) {
                if(get_outmode()==DECIMAL) printf(">>> %.4f\n", $1);
                else if (get_outmode()==SCIENTIFIC) printf(">>> %.4g\n", $1);
            }
            if(yyget_in()==stdin) prompt();
        }
        | CONST '=' expression '\n'     { 
            yyerror("Non se pode asignar un valor a unha constante");
            if(yyget_in()==stdin) prompt();

        }        
        | SYSFUN '=' expression  '\n'     { 
            yyerror("Non se pode asignar un valor a unha función");
            if(yyget_in()==stdin) prompt();
            
        }        
        | MATHFUN '=' expression  '\n'     { 
            yyerror("Non se pode asignar un valor a unha función");
            if(yyget_in()==stdin) prompt();
        }
        | SYSFUN '(' expression ')' '\n'      {
            yyerror("Non se pode usar unha variable nunha función do sistema");
            if(yyget_in()==stdin) prompt();
        }
        | VAR ADDEQ expression   '\n'    { 
            ($1)->attr_value+=$3;
            if(yyget_in()==stdin) prompt();
        }        
        | VAR SUBEQ expression   '\n'    { 
            ($1)->attr_value-=$3;
            if(yyget_in()==stdin) prompt();
        }        
        | VAR MULEQ expression   '\n'    { 
            ($1)->attr_value*=$3;
            if(yyget_in()==stdin) prompt();
        }        
        | VAR DIVEQ expression   '\n'    { 
            ($1)->attr_value/=$3;
            if(yyget_in()==stdin) prompt();
        }
        | VAR POWEQ expression    '\n'   { 
            ($1)->attr_value=pow(($1)->attr_value,$3);
            if(yyget_in()==stdin) prompt();
        }        
        | VAR MODEQ expression    '\n'   { 
            ($1)->attr_value=fmod(($1)->attr_value,$3);
            if(yyget_in()==stdin) prompt();
        }
        | VAR '=' expression      '\n' { 
            ($1)->attr_value=$3;
            if(yyget_in()==stdin) prompt();
        }
        | SYSFUN '(' STRING ')'  '\n'    {
            (($1)->fnctptr)($3);
            if(yyget_in()==stdin) prompt();
        }
        | SYSFUN '('')'   '\n'    {
            (($1)->fnctptr)();
            if(yyget_in()==stdin) prompt();
        }
        | error '\n'{
            if(yyget_in()==stdin) prompt();
        }
        ;
expression:
        NUMBER
        | CONST                         { $$=($1)->attr_value; }
        | VAR                           { $$=($1)->attr_value; }
        | MATHFUN  '(' expression ')'   {  $$ = ($1->mfnctptr)($3); }
        | expression '+' expression     { $$ = $1 + $3; }
        | expression '-' expression     { $$ = $1 - $3; }
        | expression '*' expression     { $$ = $1 * $3; }
        | expression '^' expression     { $$ = pow($1,$3); }
        | expression '%' expression     { $$ = fmod($1,$3); }
        | expression '/' expression     {
            if ($3 == 0) {
                yyerror("Non se pode dividir entre 0");
                YYERROR;
            } else{
                $$ = $1 / $3; 
            }
                
        }
        | '-' expression %prec UMINUS   { $$ = -$2;}
        | '(' expression ')'            { $$ = $2; }
        ;

%%

void yyerror(char *s) {
    handle_generic_error("Error sintaxis inválida: %s",s);
}

