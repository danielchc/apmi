#include "term.h"

void *plugin;
int echo=1;
term_out_t out_mode=DECIMAL;

void prompt(){
    printf("\033[0;32mapmi> \033[0m");
}

void ap_exit(){
    printf("Adiós!\n");
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
    handle_generic_success("Táboa de símbolos limpia");
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
    printf("APMI - Interpete Matemático Axuda\n");
    printf("Nota: As variables non inicializadas asumese que teñen de valor 0.0\n");
    printf("Comandos dispoñibles:\n");
    printf("\tclear()\t\t\tBorra as variables do espazo de traballo\n");
    printf("\tcls()\t\t\tLimpia a pantalla\n");
    printf("\techo(\"on\"/\"off\")\tActiva ou desactiva o imprimir por pantalla\n");
    printf("\tprint()\t\t\tImprime un string\n");
    printf("\texit()\t\t\tCerra a terminal (alias quit())\n");
    printf("\thelp()\t\t\tMostra esta axuda\n");
    printf("\timport(\"libreria\")\tCarga unha liberia externa\n");
    printf("\tload(\"arquivo\")\t\tCarga unha script matemático\n");
    printf("\toutmode(\"sci\"/\"dec\")\t\t\tFormato da salida: sci->formato cientifico;dec-> formato decimal\n");
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
    printf("\ta^b\t\t\tPotencia\n");
    printf("\t(a)\t\t\tParentesis\n");
    printf("\ta=b\t\t\tAsignación\n");
    printf("\ta[+ - * /]=b\t\tAsignación con operador\n\n");
}

void ap_load(char* filename){
    int result=yy_swap_buffer(filename);
    if(result==-1){
        handle_generic_error("Non se pode cargar recursivamente tantos ficheiros");
    }else if (result==-2){
        handle_generic_error("Non se atopou o ficheiro %s",filename);
    }
}

void ap_import(char* filename){
    handle_generic_info("Intentando cargar librería %s",filename);
   
    plugin = dlopen(filename, RTLD_NOW);
    if (!plugin){
        handle_generic_error("Non se puido cargar a librería %s", dlerror());
    }else{
        handle_generic_success("Librería cargada correctamente");
    }
}


void ap_echo(char* mode){
    if(strcmp(mode,"on")==0){
        printf("Echo activado\n");
        echo=1;
    }else if(strcmp(mode,"off")==0){
        printf("Echo desactivado\n");
        echo=0;
    }else{
        handle_generic_error("Modo de echo incorrecto");
    }
}

void ap_outmode(char* mode){
    if(strcmp(mode,"dec")==0){
        printf("Modo decimal\n");
        out_mode=DECIMAL;
    }else if(strcmp(mode,"sci")==0){
        printf("Modo cientifico\n");
        out_mode=SCIENTIFIC;
    }else{
        handle_generic_error("Modo decimal incorrecto");
    }
}

void ap_print(char* msg){
    printf("%s\n",msg);
}

int get_echo(){
    return echo;
}

term_out_t get_outmode(){
    return out_mode;
}

void* get_plugin(){
    return plugin;
}

