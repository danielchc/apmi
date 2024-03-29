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
/* Establezco so simbolos permitidos */
%token <num> NUMBER          
%token <record> VAR CONST SYSFUN MATHFUN 
%token <str> STRING

%token ADDEQ SUBEQ MULEQ DIVEQ POWEQ MODEQ;
%type <num> expression

%%

program:
        |
        program statement{
            if(yyget_in()==stdin) prompt();
        }
        ;

statement:
        '\n'{
        }
        | expression  '\n'                  { 
            if(get_echo()) {
                if(get_outmode()==DECIMAL) printf(">>> %.4f\n", $1);
                else if (get_outmode()==SCIENTIFIC) printf(">>> %.4g\n", $1);
            }
        }
        /* Non se permite intentar asignar un valor a unha constante */
        | CONST '=' expression '\n'     { 
            yyerror("Non se pode asignar un valor a unha constante");
        }        
        /* Non se permite intentar asignar un valor a unha función do sistema */
        | SYSFUN '=' expression  '\n'     { 
            yyerror("Non se pode asignar un valor a unha función");
        }        
        /* Non se permite intentar asignar un valor a unha función matemática */
        | MATHFUN '=' expression  '\n'     { 
            yyerror("Non se pode asignar un valor a unha función");
        }
        /* Non se permite usar unha expresión nunha función do sistema */
        | SYSFUN '(' expression ')' '\n'      {
            yyerror("Non se pode usar unha variable nunha función do sistema");
        }
        /* Operadores +=, *=, -=, /=, e %=  */
        | VAR ADDEQ expression   '\n'    { 
            ($1)->attr_value+=$3;
        }        
        | VAR SUBEQ expression   '\n'    { 
            ($1)->attr_value-=$3;
        }        
        | VAR MULEQ expression   '\n'    { 
            ($1)->attr_value*=$3;
        }        
        | VAR DIVEQ expression   '\n'    { 
            ($1)->attr_value/=$3;
        }
        | VAR POWEQ expression    '\n'   { 
            ($1)->attr_value=pow(($1)->attr_value,$3);
        }        
        | VAR MODEQ expression    '\n'   { 
            ($1)->attr_value=fmod(($1)->attr_value,$3);
        }
        /* Operación de asignación,gardase na táboa de símbolos */
        | VAR '=' expression      '\n' { 
            ($1)->attr_value=$3;
        }
        /* Función do sistema que permite o paso de strings */
        | SYSFUN '(' STRING ')'  '\n'    {
            (($1)->fnctptr)($3);
        }
        /* Función do sistema sin parámetros */
        | SYSFUN '('')'   '\n'    {
            (($1)->fnctptr)();
        }
        | error '\n'{
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

