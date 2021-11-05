%{
    #include "ts.h"
    #include <stdio.h>
    #include <stdlib.h>
    void yyerror(char *);
    int yylex(void);
%}

%token ID
%token NUMBER
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS




%union{
    char* str;
    double num;
}

%type <num> expression  
%type <str> statement  

%%

program:
        program statement '\n'
        | /* NULL */
        ;

statement:
        expression                      { printf("%f\n", $1); }
        | ID '=' expression       { 
            //save_lexcomp($1.str,ID,$3);
             //printf("COSA: %s\n",$1);
        };

expression:
        NUMBER                         /* default action { $$ = $1; }*/
        | ID                           {
            $$=3.0f;
        }
        | expression '+' expression     { $$ = $1 + $3; }
        | expression '-' expression     { $$ = $1 - $3; }
        | expression '*' expression     { $$ = $1 * $3; }
        | expression '/' expression     {
            if ($3 == 0) {
                yyerror ("Non se pode dividir entre 0"); exit(0);
            }
            else{
                $$ = $1 / $3; 
            }
                
        }
        | '-' expression %prec UMINUS   { $$ = -$2;}
        | '(' expression ')'            { $$ = $2; }
        ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Pocho %s\n", s);
}