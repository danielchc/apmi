#include "ts.h"
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

/*
	find_lexcomp
		busca un compoñente léxico na táboa de simbolos
	param:
		char* lexcomp compoñente léxico a buscar
	return:
		se a clave existe devolve 0
		se a clave non existe -1
		se a hashtable non existe -2
*/
int find_lexcomp(char* lexcomp){
	unsigned int value;
	unsigned int attr_value;
	return get_value(lexcomp,*ts,&value,&attr_value);
}


/*
	save_lexcomp
		comproba se existe un compoñente léxico na táboa de simbolos, senon gardao
	param:
		char* 	lexcomp: 	compoñente léxico a gardar
		unsigned  value:	tipo de compoñente léxico
	return:
		se todo vai ben devolve 0
*/
int save_lexcomp(char * lexcomp, unsigned int value,float attr_value){
	if(find_lexcomp(lexcomp)==-1){
		set_value(lexcomp,value,attr_value,*ts);
	}
	return 0;
}