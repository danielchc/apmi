#include "term.h"

void run_term(){
    char* input;
    input=malloc(sizeof(char)*200);
    while(1){
        printf("apmi> ");
        scanf("%s", input);
        printf(">>>18\n");
        printf("apmi> ");
        scanf("%s", input);
        printf("apmi> ");
        scanf("%s", input);
        printf(">>>10\n");
    }   
}