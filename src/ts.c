#include "ts.h"
#include "term.h"
#include "y.tab.h"
#include "math.h"
ts_s* ts;

sys_fun_t sysfun[]={
	{"exit",ap_exit},
	{"quit",ap_exit},
	{"ts",ap_ts}
};

const_t consts[]={
	{"pi",3.14159265358979323846},
	{"e",2.71828}
};

math_fun_t mathfun[]={
	{"sin",sin},
	{"cos",cos},
	{"tan",tan},
	{"floor",floor},
	{"sqrt",sqrt},
	{"log",log},
	{"log10",log10},
	{"exp",exp},
	{"abs",fabs},
	{"asin",asin},
	{"acos",acos},
	{"atan",atan},
	{"sinh",sinh},
};


ts_s* ts;

/*
	init_ts
		inicializa a táboa de símbolos
*/
int init_ts(){
	ts=malloc(sizeof(ts));
	(*ts)=init_hash_table(HASHTABLE_SIZE);
	return (ts==NULL);
}

/*
	load_keywords
		carga as palabras reservadas na táboa de simbolos
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
	print_ts
		imprime a táboa de simbolos
*/
void print_ts(){
	print_hash_table(*ts);
}

/*
	delete_ts
		borra a táboa de simbolos
	return:
		se da erro -1
		se non da erro 0
*/
int delete_ts(){
	int v=delete_hash_table(ts);
	free(ts);
	return v;
}


ts_record_t* get_lexcomp(char *lexcomp){
	ts_record_t *record=malloc(sizeof(record_t));
	record=get_record(lexcomp,*ts);
	if(!record){
		return set_value(lexcomp,VAR,*ts);
	}
	return record;
}