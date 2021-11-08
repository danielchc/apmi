#include "term.h"



void prompt(){
    if(yyget_in()==stdin)
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

void ap_cls(){
    printf("\e[1;1H\e[2J");
}

void ap_clear(){
    clear_ts();
    printf("Táboa de símbolos limpia\n");
}

void ap_workspace(){
    ts_s ts=get_ts();
    int sym_count=0;
	ht_size_t i = 0;
	size_t size = ts->table_size;
	for(; i < size; ++i){
		if(ts->lists[i]){
			record_t* head=ts->lists[i];
			while(head){   
                if(head->value==VAR){
				    printf("%s=%f\n", head->key, head->attr_value);
                    sym_count++;
                }
				head = head->next_link; 
			}
		}
	}
    if(sym_count==0)printf("Non hai variables almacenadas no workspace\n");
}

void ap_help(){
    printf("AIUDA\n");
}

void ap_load(char* filename){
    FILE *f=fopen(filename,"r");
    if(f==NULL){
        handle_generic_error("Non se puido cargar o ficheiro %s",filename);
        return;
    }
    printf("Cargando ficheiro %s\n",filename);
    yyset_in(f);
}

void ap_import(char* filename){
    printf("Librería %s\n",filename);
    void *plugin;
    plugin = dlopen(filename, RTLD_NOW);
    if (!plugin){
        handle_generic_error("Non se puido cargar a librería %s", dlerror());
    }
    

}

void ap_echo(char* mode){
    if(strcmp(mode,"on")==0){
        printf("Echo activado\n");
        yyset_echo(1);
    }else if(strcmp(mode,"off")==0){
        printf("Echo desactivado\n");
        yyset_echo(0);
    }else{
        handle_generic_error("Modo de echo incorrecto");
    }
}