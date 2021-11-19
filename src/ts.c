#include "ts.h"
#include "term.h"
#include "y.tab.h"
#include "math.h"
ts_s* ts;

sys_fun_t sysfun[]={
	{"exit",ap_exit},
	{"quit",ap_exit},
	{"ts",ap_ts},
	{"clear",ap_clear},
	{"workspace",ap_workspace},
	{"help",ap_help},
	{"load",ap_load},
	{"import",ap_import},
	{"cls",ap_cls},
	{"echo",ap_echo},
	{"outmode",ap_outmode},
	{"print",ap_print},
	{"libs",ap_libs}
};

const_t consts[]={
	{"pi",3.14159265358979323846},
	{"e",2.71828},
	{"aur",1.6180}
};

math_fun_t mathfun[]={
	{"sin",sin},
	{"cos",cos},
	{"tan",tan},
	{"floor",floor},
	{"ceil",ceil},
	{"sqrt",sqrt},
	{"log",log},
	{"log10",log10},
	{"exp",exp},
	{"abs",fabs},
	{"asin",asin},
	{"acos",acos},
	{"atan",atan},
	{"sinh",sinh},
	{"cosh",cosh},
	{"tanh",tanh},
};


ts_s* ts;

/*
	init_ts
		inicializa a táboa de símbolos
*/
int init_ts(){
	ts=malloc(sizeof(ts));
	(*ts)=init_hash_table(HASHTABLE_SIZE);
	load_symbols();
	return (ts==NULL);
}

/*
	load_keywords
		carga as palabras reservadas na táboa de símbolos
*/
void load_symbols(){
	uint i;
	record_t* record;
	for(i=0;i<sizeof(sysfun)/sizeof(sys_fun_t);i++){
		record=set_value(sysfun[i].keyword,SYSFUN,(*ts));
		record->fnctptr=sysfun[i].fnctptr;
	}

	for(i=0;i<sizeof(mathfun)/sizeof(math_fun_t);i++){
		record=set_value(mathfun[i].keyword,MATHFUN,(*ts));
		record->mfnctptr=mathfun[i].mfnctptr;
	}

	for(i=0;i<sizeof(consts)/sizeof(const_t);i++){
		record=set_value(consts[i].keyword,CONST,(*ts));
		record->attr_value=consts[i].value;
	}
}

/*
	add_ext_fun
		engade unha función dunha libreria a táboa de símbolos
	return:
		0 se engade
		-1 se xa existe un simbolos co mesmo nome
*/

int add_ext_fun(char* keyword, double (*mfnctptr)()){
	record_t* record;
	if(key_exists(keyword,(*ts)))return -1;
    record=set_value(keyword,MATHFUN,(*ts));
    record->mfnctptr=mfnctptr;
	return 0;
}


/*
	print_ts
		imprime a táboa de símbolos
*/
void print_ts(){
	print_hash_table(*ts);
}

/*
	delete_ts
		borra a táboa de símbolos
	return:
		se da erro -1
		se non da erro 0
*/
int delete_ts(){
	int v=delete_hash_table(ts);
	free(ts);
	return v;
}

/*
	clear_ts
		borra a táboa de símbolos
*/
int clear_ts(){
	delete_hash_table(ts);
	init_ts();
	return 0;
}

/*
	get_ts
		obten a táboa de símbolos
*/
ts_s get_ts(){
	return (*ts);
}


/*
	get_lexcomp
		obten un simbolo da tabla e gardao se non existe
*/
ts_record_t* get_lexcomp(char *lexcomp){
	ts_record_t *record=malloc(sizeof(record_t));
	record=get_record(lexcomp,*ts);
	if(!record){
		return set_value(lexcomp,VAR,*ts);
	}
	return record;
}

/*
	keyword_exist_ts
	param:  
		char* key: clave a buscar
	return: 
		se a clave existe devolve 1
		se a clave non existe 0
*/

int keyword_exist_ts(char* keyword){
	return key_exists(keyword,(*ts));
}