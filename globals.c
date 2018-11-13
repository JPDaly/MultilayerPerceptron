#include "header.h"

double 
sigmoid(double in){
	return 1.0/(1.0 + exp(-in));
}

int
*get_factors(int num) {
	int i,*factors, n_factors=0;
	
	factors = malloc(sizeof(int)*num);
	if(factors == NULL) {
		printf("Error while allocating space.\n");
		exit(EXIT_FAILURE);
	}
	
	for(i=1;i<=num;i++) {
		if(num%i==0) {
			factors[n_factors++] = i;
		}
	}
	//Just so that I can find the end of this array later
	factors[n_factors] = -1;
	return factors;
}