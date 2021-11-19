#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14156

double area_circulo(double radio){
	return PI*pow(radio,2);
}

double diametro_circulo(double radio){
	return 2*PI*radio;
}