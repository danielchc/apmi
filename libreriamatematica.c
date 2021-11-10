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

double is_prime(double n) {
	int number=(int)n;
	if (number <= 3 && number > 1){
		return 1;
	}else if (number%2==0 || number%3==0){
		return 0;
	}else{
		int i;
		for (i=5; i*i<=number; i+=6) {
			if ((number % i == 0) || (number%(i + 2) == 0))
				return 0;
		}
	}
	return 1; 
}

double get_next_prime(double n){
	double i;
	for (i = n; i < 2 * n; ++i){
		if(is_prime(i))return i;
	}
	return 0;
}