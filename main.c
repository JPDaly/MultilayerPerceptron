#include "init_funcs.h"
#include <math.h>

double sigmoid(double in);
double sig_derivative(double in);
void print_weights_biases(network_t *net);

int
main(int argc, char *argv[]){
	network_t *net;
	
	//inititalising
	net = init_network();
	print_weights_biases(net);
	
	
	
	return 0;
}


/*
To compile all the files together use the following:
	gcc -Wall -o main main.c init_funcs.c
You don't need to include the header files.
You can also continue to add more .c files to the end of this as you need/use them.
*/

//This is here because I don't think it has anything to do with initialising
void 
print_weights_biases(network_t *net){
	int k,j,i;
	
	printf("\n\n----Weights----\n\n");
	for(i=0; i<net->n_layers-1; i++){
		printf("\nLink #%d\n", i+1);
		for(j=0; j<net->neurons_per_layer[i]; j++){
			for(k=0; k<net->neurons_per_layer[i+1]; k++){
				printf("%.2f,", net->weights[i][j][k]);
			}
			printf("\n");
		}
	}
	
	printf("\n\n----Biases----\n\n");
	for(i=0; i<net->n_layers; i++){
		printf("\nLayer #%d\n", i+1);
		for(j=0; j<net->neurons_per_layer[i]; j++){
			printf("%.2f,", net->biases[i][j]);
		}
	}
	return;
}

//This following two are here because I haven't worked out where I will put them yet

double 
sigmoid(double in){
	return 1.0/(1.0 + exp(-in));
}

double 
sig_derivative(double in){
	double sig = sigmoid(in);
	return sig*(1.0-sig);
}
