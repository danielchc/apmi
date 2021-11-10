%{
    #include "ts.h"
    #include "term.h"
    #include "error_handler.h"
    #include <stdio.h>
    #include <math.h>
    #include <stdlib.h>
    void yyerror(char *);
    int yylex(void);
    int echo=1;
%}

%right '='
%left '-' '+'
%left '*' '/'
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

%token ADDEQ SUBEQ MULEQ DIVEQ POWEQ;
%type <num> expression

%%

program:
        program statement
        |
        ;

statement:
        expression  '\n'                    { 
            if(echo) printf(">>> %.4f\n", $1);
            prompt();
        }
        | function '\n'  {
            prompt();
        } 
        | error '\n' {yyerrok; prompt();}
        ;
function:
        | CONST '=' expression       { 
            yyerror("Non se pode asignar un valor a unha constante");
        }        
        | SYSFUN '=' expression       { 
            yyerror("Non se pode asignar un valor a unha función");
        }        
        | MATHFUN '=' expression       { 
            yyerror("Non se pode asignar un valor a unha función");
        }
        | VAR ADDEQ expression       { 
            ($1)->attr_value+=$3;
        }        
        | VAR SUBEQ expression       { 
            ($1)->attr_value-=$3;
        }        
        | VAR MULEQ expression       { 
            ($1)->attr_value*=$3;
        }        
        | VAR DIVEQ expression       { 
            ($1)->attr_value/=$3;
        }
        | VAR POWEQ expression       { 
            ($1)->attr_value=pow(($1)->attr_value,$3);
        }
        /* Variable sen inicializada, diferencios para poder mostrar unha mensaxe se a variable está sen inicializar */
        | VAR '=' expression       { 
            ($1)->attr_value=$3;
        }
        | SYSFUN '(' STRING ')'       {
            (($1)->fnctptr)($3);
        }
        | SYSFUN '('')'       {
            (($1)->fnctptr)();
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

void yyset_echo(int value){
    echo=value;
}

