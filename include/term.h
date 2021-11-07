#include <stdio.h>
#include <stdlib.h>
#include "ts.h"
#include "y.tab.h"
#include "lex.yy.h"

void prompt();
void ap_exit();
void ap_ts();
void ap_clear();
void ap_workspace();
void ap_help();
void ap_load(char* filename);
void ap_import(char* filename);