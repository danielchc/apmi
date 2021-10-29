#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H
#include <ctype.h> 
#include <stdlib.h>
#include <stdarg.h>
#include "definitions.h"
#include "error_handler.h"
#include "ts.h"




#define KEYWORDSIZE 200

//Estructura dun compoñente léxico
typedef struct{
	char	keyword[KEYWORDSIZE];
	uint   	value;
}lexcomp_t;


void next_lexcomp(lexcomp_t* lexcomp);

void load_file(char * nombreFichero);

void detroy_la();

int get_current_line();

#endif