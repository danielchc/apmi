#include "term.h"



void prompt(){
    printf("\033[0;32mapmi> \033[0m");
}

void ap_exit(){
    printf("Mi voy\n");
    printf("Que lastima pero adios\n");
    exit(0);
}
void ap_ts(){
    print_ts();
}

void ap_clear(){
    clear_ts();
    printf("Táboa de símbolos limpia\n");
}

void ap_workspace(){
    ts_s ts=get_ts();
	ht_size_t i = 0;
	size_t size = ts->table_size;
    printf("------------------------------------\n");
    printf("SIMBOLO\t\t\tVALOR\n");
	for(; i < size; ++i){
		if(ts->lists[i]){
			record_t* head=ts->lists[i];
			while(head){   
                if(head->value==VAR){
				    printf("%s\t\t\t%f\n", head->key, head->attr_value);
                }
				head = head->next_link; 
			}
		}
	}
    printf("------------------------------------\n");
}

void ap_help(){
    printf("AIUDA\n");
}

void ap_load(char* filename){
    printf("Cargando archivo %s\n",filename);
    FILE *f=fopen(filename,"r");
    yyset_in(f);
    fclose(f);
    yyset_in(stdin);
}

void ap_import(char* filename){
    printf("Liberia %s\n",filename);
}