#include "header.h"

//Simply returns the output of sigmoid given an input
double 
sigmoid(double in){
	return 1.0/(1.0 + exp(-0.5*(in)));
}

//Returns the binary of num (a base 10 integer) in a int array.
double
*num_to_binary(int num, int max_digits) {
	double *binary;
	max_digits += (max_digits == 0)*num;
	
	binary = calloc(sizeof(double),(max_digits+1));
	if(binary == NULL){
		printf("Error. No space for binary.\n");
		exit(EXIT_FAILURE);
	}
	binary[num] = 1;
	binary[max_digits] = -1;
	
	return binary;
}

void 
print_network(network_t *net){
	int k,j,i;
	
	printf("\n\n----Basic shape of network----\n\n");
	for(i=0; i<net->n_layers; i++){
		if(i!=0) printf("-");
		printf("%d", net->neurons_per_layer[i]);
	}
	
	printf("\n\n----Weights----\n\n");
	for(i=0; i<net->n_layers-1; i++){
		printf("\nLink #%d\n", i+1);
		for(j=0; j<net->neurons_per_layer[i+1]; j++){
			for(k=0; k<net->neurons_per_layer[i]; k++){
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

	printf("\n\n----Activations----\n\n");
	for(i=0; i<net->n_layers; i++){
		printf("\nLayer #%d\n", i+1);
		for(j=0; j<net->neurons_per_layer[i]; j++){
			printf("%.2f,", net->activations[i][j]);
		}
	}
	printf("\n\n");
	return;
}