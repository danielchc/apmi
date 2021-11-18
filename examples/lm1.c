#include <stdio.h>
#include <stdlib.h>
double fibonacci(double num){
    double fibo1, fibo2, fibor;
    if (num <= 0)
        return 0;
    if (num == 1)
        return 1;
    fibo1 = 0;
    fibo2 = 1;
    for (int i=2; i <= num; i++){
        fibor = fibo1 + fibo2;
        fibo1 = fibo2;
        fibo2 = fibor;
    }

    return fibor;
}

double a(double n) {
	return n*1;
}
double b(double n) {
	return n*2;
}