#include "error_handler.h"

int error_count;

/*
	init_error_handler
		inicializa o contador de erros
*/
void init_error_handler(){
	error_count=0;
}


/*
	handle_lexical_error
		imprime un erro léxico e aumenta o contador de erros
	param:
		error_t error: Tipo de erro que ocorreu
		char * info: Mensaxe adiccional
*/
void handle_lexical_error(error_t error,char * info){
	char msg[200];
	
	switch (error){
		//Dependendo do erro mostra unha mensaxe ou outra 
		case ERR_NUMERIC:
			strcpy(msg,"Error: cadea númerica mal formada: ");
			break;		
		case ERR_QUOTE:
			strcpy(msg,"Error: cadea de texto mal formada: ");
			break;
		case ERR_LEXCOMP_MAX:
			strcpy(msg,"O compoñente léxico é demasiado grande");
			break;
		default:
			break;
	}
	if(info)strcat(msg,info);
	printf("\033[1;31m\t%s\033[0m\n",msg);
	error_count++;
}


/*
	handle_generic_error
		imprime un erro xenerico
	param:
		char* format: mensaxe a mostrar
*/
void handle_generic_error(char* error,...){
	char msg[200];
	strcpy(msg,"\033[1;31m[ERROR]\t");
	strcat(msg,error);
	strcat(msg,"\033[0m\n");
	va_list args;
	va_start(args, error);
	vprintf (msg, args);
	va_end (args);
}

/*
	handle_generic_warning
		imprime un erro xenerico
	param:
		char* format: mensaxe a mostrar
*/
void handle_generic_warning(char* warning,...){
	char msg[200];
	strcpy(msg,"\033[1;33m[ADVERTENCIA]\t");
	strcat(msg,warning);
	strcat(msg,"\033[0m\n");
	va_list args;
	va_start(args, warning);
	vprintf (msg, args);
	va_end (args);
}

/*
	handle_generic_success
		imprime mensaxe de execucion correcta
	param:
		char* format: mensaxe a mostrar
*/
void handle_generic_success(char* success,...){
	char msg[200];
	strcpy(msg,"\033[1;32m[OK]\t");
	strcat(msg,success);
	strcat(msg,"\033[0m\n");
	va_list args;
	va_start(args, success);
	vprintf (msg, args);
	va_end (args);
}

void handle_generic_info(char* info,...){
	char msg[200];
	strcpy(msg,"[INFO]\t");
	strcat(msg,info);
	strcat(msg,"\n");
	va_list args;
	va_start(args, info);
	vprintf (msg, args);
	va_end (args);
}


/*
	print_error_stats
		imprime cantos erros ocorreron durante o análise
*/
void print_error_stats(){
	if(error_count>0){
		printf("\033[1;31mO análise léxico rematou con %d erros \033[0m\n",error_count);
	}else{
		printf("\033[0;32mNon se produceu ningún erro a analizar o ficheiro\033[0m\n");
	}
}