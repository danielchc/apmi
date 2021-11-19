#ifndef TS_S
#define TS_S

#ifndef HASHTABLE_H
#include "hashtable.h"
#endif


#define KEYWORDSIZE 200

//Estructura dun compoñente léxico
typedef struct{
	char	keyword[KEYWORDSIZE];
	void	(*fnctptr)();
}sys_fun_t;

typedef struct{
	char	keyword[KEYWORDSIZE];
	double (*mfnctptr)();
}math_fun_t;


typedef struct{
	char	keyword[KEYWORDSIZE];
	float 	value;
}const_t;



typedef record_t ts_record_t;

/*
	 Establezco o tamaño incial do hashmap, idealmente un hashmap 
	 funciona mellor con números primos, como nun inicio hai 35 palabras reservadas, o tamaño 
	 minimo vai ser 35, ainda que esto é irrelevante xa que na primeira execución vaise ter que 
	 redimensionar para evitar as colisións
*/

#define HASHTABLE_SIZE 37

// Defino o tipo táboa de símbolos como un hashmap
typedef hash_table_t* ts_s;

int init_ts();
void load_symbols();
int find_lexcomp(char* lexcomp);
void print_ts();
int delete_ts();
int clear_ts();
ts_s get_ts();
int keyword_exist_ts(char* keyword);
int add_ext_fun(char* keyword, double (*mfnctptr)());
ts_record_t* get_lexcomp(char *lexcomp);

#endif
