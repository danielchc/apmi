#include "ts.h"
#include "y.tab.h"
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


record_t* get_lexcomp(char *lexcomp){
	record_t *record=malloc(sizeof(record_t));
	record=get_record(lexcomp,*ts);
	if(!record){
		return set_value(lexcomp,ID,*ts);
	}
	return record;
}