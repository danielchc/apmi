
%{
    #include "ts.h"
    #include "term.h"
    #include "error_handler.h"
    #include <stdio.h>
    #include <math.h>
    #include <stdlib.h>
    void yyerror(char *);
    int yylex(void);
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
%token ID
%token NUMBER
%token EXIT


%type <num> expression  
/* %type <record> statement   */

%%

program:
        program statement '\n'
        | /* NULL */
        ;

statement:
        expression                      { 
            printf(">>> %f\n", $1);
            prompt();
        }
        | ID '=' expression       { 
            //save_lexcomp($1.str,ID,$3);
             //printf("COSA: %s\n",$1);
            ($1)->attr_value=$3;
            prompt();
            YYERROR;
        };

expression:
        NUMBER                         /* default action { $$ = $1; }*/
        | ID                           {
            $$=3.0f;
        }
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
    handle_generic_error("Error sintaxis inválida: ",s);
    prompt();
}