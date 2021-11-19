#include "term.h"

linked_lib_t* linked_libs;

int echo=1;
term_out_t out_mode=DECIMAL;


/*
	prompt
		mostra o texto antes do comando
*/

void prompt(){
	printf("\033[0;32mapmi> \033[0m");
}

/*
	ap_exit
		- corresponde ao comando exit()/quit() da terminal
		- borra a táboa de simbolos cerra e libera memoria das librerías cargadas
*/

void ap_exit(){
	clear_libs();
	delete_ts();
	printf("Saíndo...\n");
	exit(0);
}

/*
	ap_ts
		- corresponde ao comando ts() da terminal
		- mostra a táboa de simbolos
*/
void ap_ts(){
	print_ts();
}


/*
	ap_cls
		- corresponde ao comando cls() da terminal
		- limpia o terminal
*/
void ap_cls(){
	printf("\e[1;1H\e[2J");
}

/*
	ap_clear
		- corresponde ao comando clear() da terminal
		- borra a táboa de símbolos cerra as liberias abertas
*/

void ap_clear(){
	clear_libs();
	clear_ts();
	if(echo) handle_generic_success("Táboa de símbolos limpia");
}

/*
	ap_workspace
		- corresponde ao comando workspace() da terminal
		- mostra as variables gardadas no entorno
*/

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
					printf("%s\t=\t%f\n", head->key, head->attr_value);
					sym_count++;
				}
				head = head->next_link; 
			}
		}
	}
	if(sym_count==0)handle_generic_info("Non hai variables almacenadas no workspace");
}

/*
	ap_load
		- corresponde ao comando load() da terminal
		- carga un script matemático e executase todos os seus comandos
*/

void ap_load(char* filename){
	int result=yy_swap_buffer(filename);
	if(result==-1){
		handle_generic_error("Non se pode cargar recursivamente tantos ficheiros");
	}else if (result==-2){
		handle_generic_error("Non se atopou o ficheiro %s",filename);
	}
	else{
		if(echo) handle_generic_success("Ficheiro %s cargado",filename);
	}
}

/*
	ap_import
		- corresponde ao comando import() da terminal
		- carga un script matemático e executase todos os seus comandos
*/

void ap_import(char* filename){
	char cwd[PATH_MAX];
	if(echo) handle_generic_info("Intentando cargar librería %s",filename);

	//Intenta usar unha ruta relativa o argumento pasado non comeza por "/"
	if(filename[0]!='/'){
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			strcat(cwd,"/");
			filename=strcat(cwd,filename);
		}
	}

	//Carga a libería se da erro mostroo por pantalla
	void* current_lib=dlopen(filename, RTLD_NOW);
	if (!current_lib){
		handle_generic_error("Non se puido cargar a librería %s", dlerror());
		return;
	}

	/*
		Engade a libreria ao lista enlazada de librerías
		-Se non existe a lista creaa
		-Se existe engadea o final
	*/
	if(linked_libs==NULL){
		linked_libs=malloc(sizeof(linked_lib_t));
		linked_libs->next=NULL;
		linked_libs->current=current_lib;
		linked_libs->name=strdup(filename);
	}else{
		linked_lib_t* aux=linked_libs;
		while(aux->next!=NULL){
			aux=aux->next;
		}
		aux->next=malloc(sizeof(linked_lib_t));
		aux=aux->next;
		aux->current=current_lib;
		aux->name=strdup(filename);
		aux->next=NULL;
	}
	if(echo) handle_generic_success("Librería cargada correctamente");
}

/*
	ap_echo
		- corresponde ao comando echo() da terminal
		- permite evitar que se mostre por pantalla os resultados das operacións
	params:
		- char* mode: modo de echo seleccionado, permitidos "on"/"off"
*/

void ap_echo(char* mode){
	if(strcmp(mode,"on")==0){
		printf("Echo activado\n");
		echo=1;
	}else if(strcmp(mode,"off")==0){
		echo=0;
	}else{
		handle_generic_error("Modo de echo incorrecto");
	}
}

/*
	ap_echo
		- corresponde ao comando outmode() da terminal
		- permite establecer o formato da salida do intérprete
	params:
		- char* mode: modo de echo seleccionado, permitidos "sci"/"dec"
*/
void ap_outmode(char* mode){
	if(strcmp(mode,"dec")==0){
		if(echo) printf("Modo decimal\n");
		out_mode=DECIMAL;
	}else if(strcmp(mode,"sci")==0){
		if(echo) printf("Modo cientifico\n");
		out_mode=SCIENTIFIC;
	}else{
		handle_generic_error("Modo decimal incorrecto");
	}
}

/*
	ap_print
		- corresponde ao comando print() da terminal
		- imprime un texto por pantalla en azul
	params:
		- char* msg: texto a imprimir por pantalla
*/

void ap_print(char* msg){
	printf("\033[0;36m%s\033[0m\n",msg);
}

/*
	ap_libs
		- corresponde ao comando libs() da terminal
		- mostra a lista de librerías cargadas
*/
void ap_libs(){
	linked_lib_t* aux=linked_libs;
	if(aux==NULL){
		handle_generic_info("Non hai librerías cargadas");
		return;
	}
	printf("Liberias cargadas:\n");
	do{
		printf("\t-%s\n",aux->name);
		aux=aux->next;
	}while(aux!=NULL);
}

/*
	ap_getwd
		- corresponde ao comando getwd() da terminal
		- mostra o directorio de traballo actual
*/
void ap_getwd(){
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		handle_generic_info("Directorio actual de traballo %s",cwd);
	}
}

/*
	ap_setwd
		- corresponde ao comando setwd() da terminal
		- permite establecer o directorio actual 
	params:
		char* path: directorio o que queremos cambiar o directorio de traballo
*/

void ap_setwd(char* path){
	if(chdir(path)!=0){
		handle_generic_error("Non foi posible de cambiar o directorio %s",path);
		return;
	}
	ap_getwd();
}

/*
	ap_help
		- corresponde ao comando help() da terminal
		- mostra o texto de axuda por pantalla
*/
void ap_help(){
	printf("APMI - Interpete Matemático Axuda\n");
	printf("Comandos dispoñibles:\n");
	printf("\tclear()\t\t\tBorra as variables do espazo de traballo\n");
	printf("\tcls()\t\t\tLimpia a pantalla\n");
	printf("\techo(\"on\"/\"off\")\tActiva ou desactiva o imprimir por pantalla\n");
	printf("\texit()\t\t\tCerra a terminal (alias quit())\n");
	printf("\tgetwd()\t\t\tObter o directorio de traballo actual\n");
	printf("\thelp()\t\t\tMostra esta axuda\n");
	printf("\timport(\"libreria\")\tCarga unha liberia externa, recibe como argumento a ruta da libreria\n");
	printf("\tlibs()\t\t\tMostra as librerías cargadas\n");
	printf("\tload(\"script\")\t\tCarga unha script matemático\n");
	printf("\tsetwd(\"dir\")\t\tCambiar directorio de traballo actual\n");
	printf("\toutmode(\"sci\"/\"dec\")\tFormato da salida: sci->formato cientifico;dec-> formato decimal\n");
	printf("\tprint()\t\t\tImprime un string\n");
	printf("\tquit()\t\t\tCerra a terminal (alias exit())\n");
	printf("\tworkspace()\t\tMostra as variables do espazo de traballo\n");
	printf("Funcións matemáticas dispoñibles:\n");
	printf("\tacos(x)\t\t\tArco coseno\n");
	printf("\tasin(x)\t\t\tArco seno\n");
	printf("\tatan(x)\t\t\tArco tanxente\n");
	printf("\tsin(x)\t\t\tSeno\n");
	printf("\tsinh(x)\t\t\tSeno hiperbólico\n");
	printf("\tcos(x)\t\t\tCoseno\n");
	printf("\tcosh(x)\t\t\tCoseno hiperbólico\n");
	printf("\ttan(x)\t\t\tTanxente\n");
	printf("\ttanh(x)\t\t\tTanxente hiperbólica\n");
	printf("\tlog(x)\t\t\tLogaritmo\n");
	printf("\tlog10(x)\t\tLogaritmo en base 10\n");
	printf("\texp(x)\t\t\te^x\n");
	printf("\tabs(x)\t\t\tValor absoluto\n");
	printf("\tfloor(x)\t\tRedondear hacia abaixo\n");
	printf("\tceil(x)\t\t\tRedondear hacia arriba\n");
	printf("\tsqrt(x)\t\t\tRaiz cuadrada\n");
	printf("Constantes dispoñibles:\n");
	printf("\tpi\t\t\tNúmero PI:3.14159\n");
	printf("\te\t\t\tNúmero e:2.7182\n");
	printf("\taur\t\t\tNúmero aureo:1.6180\n");
	printf("Operacións matemáticas dispoñibles:\n");
	printf("\ta+b\t\t\tSuma\n");
	printf("\ta-b\t\t\tResta\n");
	printf("\ta*b\t\t\tMultiplicación\n");
	printf("\ta/b\t\t\tDivisión\n");
	printf("\ta%%b\t\t\tMódulo\n");
	printf("\ta^b\t\t\tPotencia\n");
	printf("\t(a)\t\t\tParentesis\n");
	printf("\ta=b\t\t\tAsignación\n");
	printf("\ta[+ - * / %%]=b\t\tAsignación con operador\n\n");
	handle_generic_warning("As variables non inicializadas asumese que teñen de valor 0.0");

}
/*
	clear_libs
		borra a lista enlazada de liberías
*/
void clear_libs(){
	if(linked_libs!=NULL){
		linked_lib_t* aux=linked_libs;
		while(aux!=NULL){
			dlclose(aux->current);
			aux=aux->next;
			free(linked_libs);
			linked_libs=aux;
		}
	}
}

/*
	get_echo
		devolve se está activado o echo
*/

int get_echo(){
	return echo;
}

/*
	get_outmode
		devolve o tipo de salida establecido
*/
term_out_t get_outmode(){
	return out_mode;
}

/*
	get_linked_libs
		devolve a lista de librerías enlazadas
*/
linked_lib_t* get_linked_libs(){
	return linked_libs;
}

