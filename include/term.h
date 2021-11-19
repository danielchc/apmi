#ifndef TERM_H
#define TERM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include "ts.h"
#include "y.tab.h"
#include "error_handler.h"

typedef enum {
	DECIMAL,
	SCIENTIFIC
} term_out_t;

//Estructura onde se gardan os datos das librerías
struct linked_lib_s;
typedef struct linked_lib_s{
	void* current;
	char* name;
	struct linked_lib_s *next;
}linked_lib_t;

void prompt();
void ap_exit();
void ap_ts();
void ap_clear();
void ap_cls();
void ap_workspace();
void ap_help();
void ap_load(char* filename);
void ap_echo(char* mode);
void ap_import(char* filename);
void ap_print(char* msg);
void ap_outmode(char* mode);
void ap_libs();
void ap_getwd();
void ap_setwd(char * path);
int get_echo();
void clear_libs();
term_out_t get_outmode();
linked_lib_t* get_linked_libs();
int yy_swap_buffer(char* filename);
#endif