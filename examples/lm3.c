#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14156

double area_esfera(double radio){
	return 4*PI*pow(radio,2);
}

double volumen_esfera(double radio){
	return 4/3*PI*pow(radio,2);
}