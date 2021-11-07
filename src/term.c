#include "term.h"
#include "ts.h"


void prompt(){
    printf("\033[0;32mapmi> \033[0m");
}

void ap_exit(){
    printf("Mi voy\n");
    printf("Que lastima pero adios\n");
    exit(0);
}
void ap_ts(){
    print_ts();
}
