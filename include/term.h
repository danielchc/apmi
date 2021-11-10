#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "ts.h"
#include "y.tab.h"
#include "lex.yy.h"
#include "error_handler.h"

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
void ap_external(char *name);
void ap_print(char* msg);
void yyset_echo(int value);
int yy_swap_buffer(char* filename);
