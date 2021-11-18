#ifndef TERM_H
#define TERM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "ts.h"
#include "y.tab.h"
#include "error_handler.h"

typedef enum {
	DECIMAL,
	SCIENTIFIC
} term_out_t;

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
int get_echo();
term_out_t get_outmode();
void* get_plugin();
int yy_swap_buffer(char* filename);
#endif